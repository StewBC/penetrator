;-----------------------------------------------------------------------------
; macros.inc
; Part of penetrator, the zx spectrum game, made for commander x16
;
; Stefan Wessels, 2019
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.macro vpokex  argx, argy

    .if .paramcount <> 2
    .error "Parameters issue for macro vpokex"
    .endif

    lda VERA_ADDR_HI
    and $f0
    ora #(argx)
    sta VERA_ADDR_HI
    lda #>(argy)
    sta VERA_ADDR_MID
    lda #<(argy)
    sta VERA_ADDR_LO
    stx VERA_DATA0

.endmacro

;-----------------------------------------------------------------------------
.macro vpoke  argx, argy, argz

    .if .paramcount <> 3
    .error "Parameters issue for macro vpoke"
    .endif

    ldx #(argz) 
    vpokex (argx), (argy)

.endmacro

;-----------------------------------------------------------------------------
.macro vpeek  argx, argy

    .if .paramcount <> 2
    .error "Parameters issue for macro vpeek"
    .endif

    lda VERA_ADDR_HI
    and $f0
    ora #(argx)
    sta VERA_ADDR_HI
    lda #>(argy)
    sta VERA_ADDR_MID
    lda #<(argy)
    sta VERA_ADDR_LO
    lda VERA_DATA0

.endmacro

;-----------------------------------------------------------------------------
.macro printZAStr sx, sy, mask

    .if .paramcount <> 3
    .error "Parameters issue for macro printZAStr"
    .endif

    .local zaFontMask, textX, textY 
    
    zaFontMask = zTemp3
    textX = tempBlock + 0
    textY = tempBlock + 1

    lda mask
    sta zaFontMask
    lda sx
    sta textX
    lda sy
    sta textY
    jsr textOut

.endmacro 

;-----------------------------------------------------------------------------
.macro print szText, sx, sy, mask

    .if .paramcount <> 4
    .error "Parameters issue for macro print"
    .endif

    .local zaStrL, zaStrH, zaFontMask, textX, textY 
    
    zaStrL     = zTemp1
    zaStrH     = zTemp2

    lda #<szText
    sta zaStrL
    lda #>szText
    sta zaStrH 

    printZAStr sx, sy, mask 

.endmacro

;-----------------------------------------------------------------------------
.macro printBCD number, digits, force, sx, sy, mask 

    .if .paramcount <> 6
    .error "Parameters issue for macro printBCD"
    .endif

    .local zaStrL, zaStrH, zaFontMask
    
    zaStrL     = zTemp1
    zaStrH     = zTemp2

    lda #<number
    sta zaStrL
    lda #>number
    sta zaStrH 
    ldy digits 
    ldx force
    jsr textBCDtoSZ

    print textNumber, sx, sy, mask

.endmacro 

;-----------------------------------------------------------------------------
.macro printBig szText, sx, sy, wx, hy, pc 

    .if .paramcount <> 6
    .error "Parameters issue for macro printBig"
    .endif

    .local zaStrL, zaStrH, width, textX, textY, height, plotCol
    
    zaStrL  = zTemp1
    zaStrH  = zTemp2
    textX = tempBlock + 0
    textY = tempBlock + 1
    width   = tempBlock + 14                    ; shared with drawPlotXY
    height  = tempBlock + 15
    plotCol = tempBlock + 16


    lda #<szText
    sta zaStrL
    lda #>szText
    sta zaStrH 
    lda sx 
    sta textX
    lda sy 
    sta textY
    lda wx 
    sta width 
    lda hy 
    sta height
    lda pc 
    sta plotCol
    jsr textBigPrint

.endmacro

;-----------------------------------------------------------------------------
.macro wait time

    .if .paramcount <> 1
    .error "Parameters issue for macro wait"
    .endif

    .local loop

    lda #0
    sta TIME_2
loop:
    lda TIME_2
    cmp time
    bcc loop
    clc 

.endmacro 
