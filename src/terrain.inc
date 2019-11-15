;-----------------------------------------------------------------------------
; terrain.inc
; Part of penetrator, the zx spectrum game, made for commander x16
;
; Stefan Wessels, 2019
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "CODE"

;-----------------------------------------------------------------------------
.proc terrainShow

    zaIndex = zTemp1
    zaWorldBot = zTemp2
    zaWorldTop = zTemp3

    ldy #WORLD_START                            ; start row
    lda #(WORLD_END - WORLD_START + 1)          ; no of rows to clear
    ldx backLayer                               ; inactive (back) layer
    jsr drawClearRows                           ; clean the part where the world must draw

    lda #$00                                    ; 0 byte step size and 0 for top address
    sta VERA_ADDR_HI

    ldy terrainOrigin                           ; set up the column to start drawing
    sty zScreenCol

    ldy bufferDraw                              ; make enemyBuffer relative to screen col 0
    dey                                         ; but back up 1 to the last drawn height

    lda worldBBuffer, y                         ; prime the drawing with these heights
    sta zaWorldBot                              ; as the last height is where the col 0
    lda worldTBuffer, y                         ; draw needs to come from
    sta zaWorldTop

    iny                                         ; get back to col 0 equivalent index
    sty zaIndex                                 ; and save this index

loop:
    lda worldBBuffer, y
    ldy zaWorldBot                              ; get the last height
    sta zaWorldBot                              ; save new bottom as last
    jsr terrainDrawAColumn 

    ldy zaIndex
    lda worldTBuffer, y 
    ldy zaWorldTop                              ; get the last height
    sta zaWorldTop                              ; save new bottom as last
    cmp #9
    bcc :+
    jsr terrainDrawAColumn

:
    ldy zaIndex 
    cpy bufferInsert
    clc 
    beq done
    iny 
    sty zaIndex
    inc zScreenCol
    bne loop

done:
    rts 

.endproc

;-----------------------------------------------------------------------------
; y = last height, a = new height
.proc terrainDrawAColumn

    zaDiff = zTemp4

    sty zaDiff
    sec 
    sbc zaDiff                                  ; get the delta (new - old)
    tax                                         ; save delta in x
    bcs eqdown                                  ; new >= old

up:                                             ; new < old so go up
    lda rowL, y
    adc zScreenCol
    sta VERA_ADDR_LO
    lda rowH, y
    adc zVramH
    sta VERA_ADDR_MID
    lda #%01010000                              ; start with a 2 pixel flat area
    sta VERA_DATA0
    dey                                         ; go 1 row up
    inx 
    beq skup                                    ; if at new height now, skip the "up line" portion
:
    lda rowL, y                                 ; draw the "up line" portion now
    adc zScreenCol
    sta VERA_ADDR_LO
    lda rowH, y
    adc zVramH
    sta VERA_ADDR_MID
    lda #%00000100                              ; write a single pixel up the rows
    sta VERA_DATA0
    dey                                         ; row up
    inx 
    bne :-                                      ; keep going till old = new

skup:
    lda rowL, y                                 ; finish off the transition
    adc zScreenCol
    sta VERA_ADDR_LO
    lda rowH, y
    adc zVramH
    sta VERA_ADDR_MID
    lda #%00000001                              ; by writing a pixel to connect to new
    sta VERA_DATA0                              ; (which will become old, in next column, to draw from)
    rts

eqdown:
    clc                                         ; carry still set from subtract
    beq eq                                      ; if new = old it's a flat line

down:                                           ; new > old so go down - see up, same but inc|dec is reversed
    lda rowL, y
    adc zScreenCol
    sta VERA_ADDR_LO
    lda rowH, y
    adc zVramH
    sta VERA_ADDR_MID
    lda #%01010000
    sta VERA_DATA0
    iny 
    dex 
    beq skdn

:
    lda rowL, y
    adc zScreenCol
    sta VERA_ADDR_LO
    lda rowH, y
    adc zVramH
    sta VERA_ADDR_MID
    lda #%00000100
    sta VERA_DATA0
    iny 
    dex 
    bne :-

skdn:
    lda rowL, y
    adc zScreenCol
    sta VERA_ADDR_LO
    lda rowH, y
    adc zVramH
    sta VERA_ADDR_MID
    lda #%00000001
    sta VERA_DATA0
    rts

eq:                                             ; flat line from old to new when equal
    lda rowL, y
    adc zScreenCol
    sta VERA_ADDR_LO
    lda rowH, y
    adc zVramH
    sta VERA_ADDR_MID
    lda #%01010101                              ; 4 pixels in a line
    sta VERA_DATA0

    rts

.endproc

