;-----------------------------------------------------------------------------
; file.inc
; Part of penetrator, the zx spectrum game, made for Commodore C64
;
; Stefan Wessels, 2019, 2023
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "DATA"

;-----------------------------------------------------------------------------
.segment "CODE"

;-----------------------------------------------------------------------------
; Adress of where to start save in AX
.proc saveFile

    pha                                         ; Push AX (address of where to save ends)
    txa
    pha

    clc
    lda FNLEN
    ldx #<PNBUFR
    ldy #>PNBUFR
    jsr SETNAM
    lda #$00                                    ; logical number
    ldx #$08                                    ; device 8
    ldy #$FF                                    ; secondary address
    jsr SETLFS

    pla                                         ; Put save end address in XY
    tay
    pla
    tax

    lda #<fileStartL                            ; start address storage location
    jmp SAVESP                                  ; call save to save the world

.endproc

;-----------------------------------------------------------------------------
; Adress of where to load file in AX
.proc loadFile

    pha                                         ; Push the address of where to load (AX)
    txa
    pha

    lda FNLEN
    ldx #<PNBUFR
    ldy #>PNBUFR
    jsr SETNAM

    lda #$00                                    ; logical number
    ldx #$08                                    ; device 8
    ldy #$00                                    ; secondary address (relocate)
    jsr SETLFS 

    pla                                         ; put load to address in XY
    tay
    pla
    tax

    lda #$00                                    ; $00 is load ($01 is verify)
    jmp LOADSP                                  ; call load to load the world

.endproc

;-----------------------------------------------------------------------------
.proc saveWorld

    lda #<worldDataStart                        ; set the size
    sta fileStartL
    lda #>worldDataStart
    sta fileStartH

    lda #<worldDataEnd                          ; set the location
    ldx #>worldDataEnd

    jmp saveFile                                ; save

.endproc

;-----------------------------------------------------------------------------
.proc loadWorld

    lda #<worldDataStart                        ; Where to load in AX
    ldx #>worldDataStart
    jmp loadFile                                ; load

.endproc

;-----------------------------------------------------------------------------
.proc saveHighScores

:jmp:-
    jsr setHighScoreFileNames                   ; set the name

    lda #<scoresTable                           ; set the location
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
:   sty FNLEN

    rts

.endproc

;-----------------------------------------------------------------------------
.proc setWorldFileName

    zaEntryL = zWorldPtr                        ; internal - ptr to a string being entered (abusing world ptr)

    sty FNLEN
:   lda (zaEntryL), y                           ; copy the file name to the end of the path
    sta PNBUFR, y
    dey
    bpl :-

    rts

.endproc

