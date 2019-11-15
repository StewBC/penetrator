;-----------------------------------------------------------------------------
; zpvars.inc
; Part of penetrator, the zx spectrum game, made for commander x16
;
; Stefan Wessels, 2019
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "ZEROPAGE"

;-----------------------------------------------------------------------------
; zero page variables
zWorldPtr:              .res 2                  ; where data is next read from the world stream
zVramH:                 .res 1                  ; for VERA writes, points at the Hi of the back bank RAM
zScreenCol:             .res 1                  ; used for drawing - the column to draw
zEnemyCol:              .res 1                  ; used for enemies - the column to process
zCollision:             .res 1                  ; drawSprite will put a 1 in when there's a write collision
zTemp1:                 .res 1                  ; temporary zero page storage used for all sorts of things
zTemp2:                 .res 1
zTemp3:                 .res 1
zTemp4:                 .res 1
zTemp5:                 .res 1
zTemp6:                 .res 1
