;-----------------------------------------------------------------------------
; file.inc
; Part of penetrator, the zx spectrum game, made for Commodore Plus4
;
; Stefan Wessels, 2019, 2023
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "DATA"

;-----------------------------------------------------------------------------
.segment "CODE"

;-----------------------------------------------------------------------------
.proc saveFile

    pha
    txa
    pha

    clc
    lda DOSF1L
    ldx #<PNBUFR
    ldy #>PNBUFR
    jsr SETNAM
    lda #$00                                    ; logical number
    ldx #$08                                    ; device 8
    ldy #$FF                                    ; secondary address
    jsr SETLFS

    pla
    tay
    pla
    tax

    lda #<fileStartL                           ; start address storage location
    jmp SAVESP                                    ; call save to save the world

.endproc

;-----------------------------------------------------------------------------
.proc loadFile

    pha
    tax
    pha

    lda DOSF1L
    ldx #<PNBUFR
    ldy #>PNBUFR
    jsr SETNAM

    lda #$00                                    ; logical number
    ldx #$08                                    ; device 8
    ldy #$01                                    ; secondary address
    jsr SETLFS 

    pla
    tay
    pla
    tax

    lda #$00                                    ; $00 is load ($01 is verify I think)
    jsr LOADSP                                  ; call load to load the world
    rts

.endproc

;-----------------------------------------------------------------------------
.proc saveWorld

    lda #<worldDataStart                                         ; set the size
    sta fileStartL
    lda #>worldDataStart
    sta fileStartH

    lda #<worldDataEnd                                                        ; set the location
    ldx #>worldDataEnd

    jmp saveFile                                ; save

.endproc

;-----------------------------------------------------------------------------
.proc loadWorld

    lda #<worldDataStart
    ldx #>worldDataStart
    jmp loadFile                                ; load

.endproc

;-----------------------------------------------------------------------------
.proc saveHighScores

    jsr setHighScoreFileNames                   ; set the name

    lda #<scoresTable                                                           ; set the location
    sta fileStartL
    lda #>scoresTable
    sta fileStartH

    lda #<scoresTableEnd
    ldx #>scoresTableEnd

    jmp saveFile                                ; save

.endproc

;-----------------------------------------------------------------------------
.proc loadHighScores

    jsr setHighScoreFileNames                   ; set the name
    lda #<scoresTable
    ldx #>scoresTable
    jmp loadFile                                ; load

.endproc

;-----------------------------------------------------------------------------
.proc setHighScoreFileNames

    ldy #0                                      ; from the 1st char pf the name
:
    lda hihgScoreFileName, y                    ; copy name to path
    sta PNBUFR, y
    beq :+
    iny
    bne :-
:   sty DOSF1L

    rts

.endproc

;-----------------------------------------------------------------------------
.proc setWorldFileName

    zaEntryL = zWorldPtr                        ; internal - ptr to a string being entered (abusing world ptr)

    sty DOSF1L
:   lda (zaEntryL), y                           ; copy the file name to the end of the path
    sta PNBUFR, y
    dey
    bpl :-

    rts

.endproc

