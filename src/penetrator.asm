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
.include "cx16.inc"                             ; cc65 VERA etc defenitions
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
    ora VERA::CTRL

    lda #0                                      ; put ram bank 0 in memory
    sta VIA1::PRA

    rts 

.endproc 

;-----------------------------------------------------------------------------
.proc mainIntro

    jsr drawClearScreen

    lda #HSCALE + 1                             ; Adjusted this and HSTOP so I don't have to re-encode the
    sta VERA::DISP::HSCALE                      ; logo for the changes from R34 to R37

    jsr uiShowLogoGraphic

    lda #%00000010
    sta VERA::CTRL                              ; Map border controls in
    lda #20                                     ; now set the borders (h/4 and v/2)
    sta VERA::DISP::HSTART
    lda #138
    sta VERA::DISP::HSTOP
    lda #(20/2)
    sta VERA::DISP::VSTART
    lda #((480-15)/2)
    sta VERA::DISP::VSTOP
    lda #%00000000
    sta VERA::CTRL

    lda #0
    sta NDX                                     ; flush the keyboard buffer (before the load display)
    sta lastInput                               ; and make sure keys don't "seep" in from before

    jsr uiSimulateLoad
:
    jsr inputCheckForInput                      ; wait for user interaction
    beq :-

    lda #%00000010
    sta VERA::CTRL

    lda #0
    sta VERA::DISP::HSTART
    lda #640/4
    sta VERA::DISP::HSTOP
    lda #0
    sta VERA::DISP::VSTART
    lda #480/2
    sta VERA::DISP::VSTOP

    lda #%00000000
    sta VERA::CTRL

    rts 

.endproc 

;-----------------------------------------------------------------------------
.proc mainGameSetup

    lda #0                                      ; Set channel and address lo
    sta VERA::CTRL                              ; all functions leave with low active (convention)

    lda #VSCALE_UI                              ; this is adjusted in the flow
    sta VERA::DISP::VSCALE                      ; reset because in dev I skip mainIntro
    lda #HSCALE
    sta VERA::DISP::HSCALE


    lda #(ram_layer0 >> 9)                      ; layer0 mem at ram_layer0
    sta VERA::L0::TILE_BASE

    lda #(ram_layer1 >> 9)                      ; layer1 mem at ram_layer1
    sta VERA::L1::TILE_BASE

    lda #0                                      ; mark a layer as inactive
    sta backLayer

    lda VERA::DISP::VIDEO
    and #%11001111                              ; both latyers off
    sta VERA::DISP::VIDEO

    lda #%00000101                              ; set bitmap mode and 2bpp
    sta VERA::L0::CONFIG
    sta VERA::L1::CONFIG

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
