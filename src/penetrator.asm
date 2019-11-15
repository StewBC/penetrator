;-----------------------------------------------------------------------------
; penetrator, the zx spectrum game, made for commander x16
;
; Stefan Wessels, 2019
; This is free and unencumbered software released into the public domain.
;
; Use the ca65 assembler and make to build

;-----------------------------------------------------------------------------
; assembler directives
.debuginfo on
.listbytes unlimited

;-----------------------------------------------------------------------------
.segment "CODE"

;-----------------------------------------------------------------------------
jmp main                                        ; This ends up at $080d (sys 2061's target)

;-----------------------------------------------------------------------------
.include "defs.inc"                             ; constants
.include "macros.inc"                           ; vpoke, vpeek, print* & wait.
.include "zpvars.inc"                           ; Zero Page usage (variables)
.include "input.inc"                            ; Keyboard/Joystick routines
.include "ui.inc"                               ; The front-end code
.include "edit.inc"
.include "game.inc"                             ; All gameplay code
.include "terrain.inc"                          ; Code that writes the terrain to VERA
.include "draw.inc"                             ; Code that writes to VERA
.include "text.inc"                             ; The text and text printing code
.include "file.inc"
.include "variables.inc"                        ; Game Variables (DATA segment)
.include "trndata.inc"
.include "fontdata.inc"                         ; The ZA Spectrum font as 2bpp, 2 bytes/char
.include "logodata.inc"                         ; Lines to spell Penetrator and intro graphic
.include "rodata.inc"                           ; Read Only (RODATA segment sprites, etc)

;-----------------------------------------------------------------------------
.segment "CODE"
.proc main

    jsr mainVeraSetup
    jsr mainIntro
    jsr mainGameSetup
:
    jsr uiTitleScreen
    jsr uiMainMenu
    jmp :-

.endproc

;-----------------------------------------------------------------------------
.proc mainVeraSetup

    lda #%10000000                              ; Reset Vera just to be sure the game starts in a known state
    sta VERA_CTRL

    vpoke VERA_regs_hi, DC_VIDEO      , $01     ; this shouldn't be necessary surely?  VGA
    vpoke VERA_regs_hi, DC_HSTART_L   , $00     ; turn the border off - left
    vpoke VERA_regs_hi, DC_HSTOP_L    , $80     ; right
    vpoke VERA_regs_hi, DC_VSTART_L   , $00     ; top
    vpoke VERA_regs_hi, DC_VSTOP_L    , $E0     ; bottom
    vpoke VERA_regs_hi, DC_STARTSTOP_H, $28

    rts 

.endproc 

;-----------------------------------------------------------------------------
.proc mainIntro

    jsr drawClearScreen

    vpoke VERA_regs_hi, DC_HSCALE, HSCALE

    jsr uiShowLogoGraphic

    vpoke VERA_regs_hi, DC_HSTART_L, $51        ; turn the border on - left
    vpoke VERA_regs_hi, DC_HSTOP_L , $30        ; right
    vpoke VERA_regs_hi, DC_VSTART_L, $12        ; top
    vpoke VERA_regs_hi, DC_VSTOP_L , $CC        ; bottom

    lda #0
    sta NDX                                     ; flush the keyboard buffer (before the load display)
    sta lastInput                               ; and make sure keys don't "seep" in from before

    jsr uiSimulateLoad
:
    jsr inputCheckForInput                      ; wait for user interaction
    beq :-

    vpoke VERA_regs_hi, DC_HSTART_L, $00        ; turn the border off - left
    vpoke VERA_regs_hi, DC_HSTOP_L , $80        ; right
    vpoke VERA_regs_hi, DC_VSTART_L, $00        ; top
    vpoke VERA_regs_hi, DC_VSTOP_L , $E0        ; bottom

    rts 

.endproc 

;-----------------------------------------------------------------------------
.proc mainGameSetup

    lda #0                                      ; Set channel and address lo
    sta VERA_CTRL                               ; all functions leave with low active (convention)

    vpoke VERA_regs_hi, DC_VSCALE, VSCALE_UI    ; this is adjusted in the flow
    vpoke VERA_regs_hi, DC_HSCALE, HSCALE       ; reset because in dev I skip mainIntro

; layer0 mem at ram_layer0
    vpoke VERA_regs_hi, VERA_regs_layer0 + Ln_TILE_BASE_H, (ram_layer0 >> 10)
; layer1 mem at ram_layer1
    vpoke VERA_regs_hi, VERA_regs_layer1 + Ln_TILE_BASE_H, (ram_layer1 >> 10) 

    lda #0                                      ; mark a layer as inactive
    sta backLayer

; hide both layers
    vpoke VERA_regs_hi, VERA_regs_layer0 + Ln_CTRL0, $a0 
    vpoke VERA_regs_hi, VERA_regs_layer1 + Ln_CTRL0, $a0

    ldx #((textHSEnd-textHS) - 1)               ; empty the high score names to spaces
store:
    lda textHS, x
    beq :+                                      ; skip the null terminators
    lda #$20                                    ; load the space (" ") character
    sta textHS, x                               ; write it to the text areas
:
    dex 
    bpl store

    ldx #((highScoresEnd-highScores) - 1)       ; set high score table scores to 0
    lda #$0
:
    sta highScores, x
    dex 
    bpl :-

    jsr drawClearScreen
    jmp drawPresent                             ; show the appropriate buffer

.endproc
