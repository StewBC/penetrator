;-----------------------------------------------------------------------------
; file.inc
; Part of penetrator, the zx spectrum game, made for commander x16
;
; Stefan Wessels, 2019
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "CODE"

;-----------------------------------------------------------------------------
.proc fileSave

    zaFileSizeL = zTemp1
    zaFileSizeH = zTemp2

    lda #textFileNameEnd-textFileName
    ldx #<textFileName
    ldy #>textFileName
    jsr SETNAM
    lda #$00                                    ; logical number
    ldx #$01                                    ; device 1
    ldy #$01                                    ; secondary address
    jsr SETLFS

    lda #<worldDataStart
    sta zaFileSizeL
    lda #>worldDataStart
    sta zaFileSizeH

    ldx #<worldDataEnd
    ldy #>worldDataEnd
    lda #<zaFileSizeL                           ; start address storage location
    jsr SAVE                                    ; call save to save the world
    rts 

.endproc

;-----------------------------------------------------------------------------
.proc fileLoad

    lda #textFileNameEnd-textFileName
    ldx #<textFileName
    ldy #>textFileName
    jsr SETNAM
    lda #$00                                    ; logical number
    ldx #$01                                    ; device 1
    ldy #$01                                    ; secondary address
    jsr SETLFS 
    ldx #<worldDataStart
    ldy #>worldDataStart
    lda #$00                                    ; $00 is load ($01 is verify I think)
    jsr LOAD                                    ; call load to load the world
    rts 

.endproc