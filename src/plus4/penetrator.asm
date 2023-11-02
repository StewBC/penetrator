;-----------------------------------------------------------------------------
; penetrator, the zx spectrum game, made for Commodore Plus4
;
; Stefan Wessels, 2019, 2023
; This is free and unencumbered software released into the public domain.
;
; Use the ca65 assembler and make to build

;-----------------------------------------------------------------------------
; assembler directives
.debuginfo on
.listbytes unlimited
.import __TITLEGFX_LOAD__, __TITLEGFX_SIZE__
.import __TITLELUM_LOAD__, __TITLELUM_SIZE__
.import __TITLECOL_LOAD__, __TITLECOL_SIZE__

;-----------------------------------------------------------------------------
.segment "CODE"

;-----------------------------------------------------------------------------
jmp main                                        ; This ends up at $080d (sys 2061's target)

;-----------------------------------------------------------------------------
.include "plus4.inc"                            ; Commodore Plus4 locations from cc65
.include "defs.inc"                             ; constants
.include "macros.inc"                           ; vpoke, vpeek, print* & wait.
.include "zpvars.inc"                           ; Zero Page usage (variables)
.include "audio.inc"                            ; Play notes fro audio events
.include "input.inc"                            ; Keyboard/Joystick routines
.include "ui.inc"                               ; The front-end code
.include "edit.inc"                             ; In-game editor
.include "game.inc"                             ; All gameplay code
.include "terrain.inc"                          ; Code that writes the terrain to HRG
.include "draw.inc"                             ; Code that writes to HRG
.include "text.inc"                             ; The text and text printing code
.include "file.inc"                             ; LOAD / SAVE routine
.include "decomp.inc"
.include "variables.inc"                        ; Game Variables (DATA segment)
.include "trndata.inc"                          ; Terrain triplets
.include "fontdata.inc"                         ; The ZA Spectrum font as 2bpp, 2 bytes/char
.include "logodata.inc"                         ; Lines to spell Penetrator and intro graphic
.include "rodata.inc"                           ; Read Only (RODATA segment sprites, etc)
.include "logo.inc"                             ; The include to include the HGR image

;-----------------------------------------------------------------------------
.segment "CODE"

;-----------------------------------------------------------------------------
.proc main

    jsr mainGameSetup
:
    jsr inputCheckForInput                      ; wait for user interaction
    beq :-                                      ; to clear title screen

    jsr drawClearScreen
    jsr drawPresent
:
    jsr uiTitleScreen
    jsr uiMainMenu
    jmp :-

.endproc

;-----------------------------------------------------------------------------
.proc mainIRQ
    jsr audioService
next:
    jmp PLACEHOLDER
.endproc

;-----------------------------------------------------------------------------
.proc mainGameSetup

    lda #$8F                                    ; Sound and both voices off
    sta TED_snd_ctrl

    lda TED_vscroll
    and #%11101111
    ora #%00100000                              ; Enter bitmap (bit 5) mode & blank (bit 4)
    sta TED_vscroll

    lda TED_misc
    and #%11000000                              ; also clear audio bits
    ora #(ram_layer1 >> 10)
    sta TED_misc
    lda #<(luma_layer1 >> 8)
    sta TED_video_addr

    lda #BCOLOR_BLUE | CATTR_LUMA0
    sta TED_bordercolor

    sei                                         ; decompress title screen to display
    sta TED_enable_ram

    lda #<__TITLECOL_LOAD__
    sta LZSA_SRC+1
    lda #>__TITLECOL_LOAD__
    sta LZSA_SRC+2
    lda #<color_layer0
    sta LZSA_DST+1
    lda #>color_layer0
    sta LZSA_DST+2
    jsr DECOMPRESS_LZSA2

    lda #<__TITLELUM_LOAD__
    sta LZSA_SRC+1
    lda #>__TITLELUM_LOAD__
    sta LZSA_SRC+2
    lda #<luma_layer0
    sta LZSA_DST+1
    lda #>luma_layer0
    sta LZSA_DST+2
    jsr DECOMPRESS_LZSA2

    lda #<__TITLEGFX_LOAD__
    sta LZSA_SRC+1
    lda #>__TITLEGFX_LOAD__
    sta LZSA_SRC+2
    lda #<ram_layer0
    sta LZSA_DST+1
    lda #>ram_layer0
    sta LZSA_DST+2
    jsr DECOMPRESS_LZSA2

    sta TED_enable_rom
    cli
    lda #$0
    sta backLayer                               ; set back layer to 0
    sta audioFrame                              ; set all audio channels to off (0)
    sta numPlayers                              ; Init initially to 0 (not set for training)
    sta lastInput                               ; Used for key debounce - init to 0
    sta TED_snd1_freq_lo                        ; Clear all sound frequencies
    sta TED_snd2_freq_lo
    sta TED_snd2_freq_hi
    sta audioChannel1                           ; Clear how long a freq is held
    sta audioChannel2

    jsr drawPresent

    lda #$0F                                    ; Sound on, but both voices still off
    sta TED_snd_ctrl

    lda TED_vscroll
    ora #%00010000                              ; un-blank the screen (bit 4
    sta TED_vscroll

    jsr loadHighScores                          ; load high scores from disc
    bcc cont                                    ; on success, skip the init

    ldx #((textHSEnd-textHS) - 1)               ; empty the high score names to spaces
store:
    lda textHS, x
    beq :+                                      ; skip the null terminators
    lda #$20                                    ; load the space (" ") character
    sta textHS, x                               ; write it to the text areas
:
    dex
    bpl store

    lda #$0
    ldx #((highScoresEnd-highScores) - 1)       ; set high score table scores to 0
:
    sta highScores, x
    dex
    bpl :-

cont:
    lda #(AUDIO_EXPLOSION | AUDIO_BOMB_DROP | AUDIO_FIRE | AUDIO_UI_TICK)
    sta audioMask                               ; set the mask for default ON channels

    ldx #((BitMasksEnd - BitMasks) - 1)         ; Install bit masks in zero page
:
    lda BitMasks, x
    sta Bit1Mask, x
    dex
    bpl :-

    sei                                         ; Install an IRQ handler to handle audio
    lda $0314
    sta mainIRQ::next+1
    lda $0315
    sta mainIRQ::next+2
    lda #<mainIRQ
    sta $314
    lda #>mainIRQ
    sta $315
    cli

    rts

.endproc

;-----------------------------------------------------------------------------
; Space for luma and color layers 1.  Unfortunately goes into the file
.segment "COLLYR1"
    .res 2048                               ; Reserver 2048 bytes
