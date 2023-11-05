;-----------------------------------------------------------------------------
; penetrator, the zx spectrum game, made for Commodore C64
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
.import __TITLECOL_LOAD__, __TITLECOL_SIZE__

;-----------------------------------------------------------------------------
.segment "CODE"

;-----------------------------------------------------------------------------
jmp main                                        ; This ends up at $080d (sys 2061)

;-----------------------------------------------------------------------------
.include "c64.inc"                              ; Commodore C64 locations from cc65
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
:   jsr inputCheckForInput                      ; wait for user interaction
    beq :-                                      ; to clear title screen

    jsr drawClearScreen
    jsr drawPresent

:   jsr uiTitleScreen
    jsr uiMainMenu
    jmp :-

.endproc

;-----------------------------------------------------------------------------
.proc mainGameSetup

    lda VIC_CTRL1
    and #%11101111
    ora #%00100000                              ; Enter bitmap (bit 5) mode & blank (bit 4)
    sta VIC_CTRL1

    lda CIA2_PRA
    and #%11111100                              ; also clear audio bits
    ora #(3 ^ (VicBase1 >> $0e))
    sta CIA2_PRA

    lda VIC_VIDEO_ADR
    and #%00000111
    ora #%00001000
    ora #<(color_layer1 >> 6)
    sta VIC_VIDEO_ADR

    lda #BCOLOR_BLUE
    sta VIC_BORDERCOLOR

    sei
    lda #RAMONLY                                ; No kernal
    sta R6510

    lda #%11111111                              ; port A = outputs 
    sta CIA1_DDRA             

    lda #%00000000                              ; port B = inputs
    sta CIA1_DDRB             

    lda #<__TITLECOL_LOAD__                     ; decompress title screen to display
    sta LZSA_SRC+1
    lda #>__TITLECOL_LOAD__
    sta LZSA_SRC+2
    lda #<color_layer0
    sta LZSA_DST+1
    lda #>color_layer0
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

    lda #$36                                    ; Kernal back in
    sta R6510
    cli

    lda #$0
    sta backLayer                               ; set back layer to 0
    sta audioFrame                              ; set all audio channels to off (0)
    sta numPlayers                              ; Init initially to 0 (not set for training)
    sta lastInput                               ; Used for key debounce - init to 0
    sta audioChannel1                           ; Clear how long a freq is held
    sta audioChannel2
    sta audioChannel3

    ldx #$18                                    ; Clear the SID
:   sta SID,x
    dex
    bpl :-

    lda #%00001000                              ; Kill all audio
    sta SID_Ctl1
    sta SID_Ctl2
    sta SID_Ctl3
    lda #$09                                    ; Set some defaults for all 3 audio channels
    sta SID_AD1
    sta SID_AD2
    sta SID_AD3
    lda #$0f
    sta SID_S3Lo                                ; Set a default noise frequency
    sta SID_S3Hi
    sta SID_Amp                                 ; set volume 15
    
    jsr drawPresent

    lda VIC_CTRL1
    ora #%00010000                              ; un-blank the screen
    sta VIC_CTRL1

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
    sta audioService::dn+1
    lda $0315
    sta audioService::dn+2
    lda #<audioService
    sta $314
    lda #>audioService
    sta $315
    cli

    rts

.endproc
