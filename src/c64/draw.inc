;-----------------------------------------------------------------------------
; draw.inc
; Part of penetrator, the zx spectrum game, made for Commodore C64
;
; Stefan Wessels, 2019, 2023
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "CODE"

;-----------------------------------------------------------------------------
; turns layers on and off so that the backLayer is hidden and the other
; layer is visible to the user
.proc drawPresent


    lda backLayer
    eor #1
    sta backLayer
    tax

    lda layersH,x
    sta zVramH

    lda colorLayersH,x
    sta zColorH

    lda CIA2_PRA
    eor #<((VicBase0 ^ VicBase1) >> $0e)
    sta CIA2_PRA

    rts

.endproc

;-----------------------------------------------------------------------------
; Clears the world area
.proc drawClearRows

    lda #$00
    ldx #127

    ldy backLayer
    beq layer0
    jmp layer1

layer0:
    .repeat $16, Row
        sta ram_layer0 + XINSET * 8 + (Row+1) * 320,x
        sta ram_layer0 + XINSET * 8 + (Row+1) * 320 + 128,x
    .endrepeat
    dex
    bmi :+
    jmp layer0
:   rts

layer1:
    .repeat $16, Row
        sta ram_layer1 + XINSET * 8 + (Row+1) * 320,x
        sta ram_layer1 + XINSET * 8 + (Row+1) * 320 + 128,x
    .endrepeat
    dex
    bmi :+
    jmp layer1
:   rts

.endproc

;-----------------------------------------------------------------------------
.proc drawClearScreen

    lda VIC_CTRL1                             ; Blank the screen
    and #%11101111
    sta VIC_CTRL1

    lda #0
    sta VIC_BORDERCOLOR
    tax
:
    .repeat $20, B
        sta ram_layer0+(B*256), x
        sta ram_layer1+(B*256), x
    .endrep
    dex
    beq color
    jmp :-
color:
    lda #BCOLOR_BLACK | BCOLOR_WHITE << 4
:    .repeat 4, B
        sta color_layer0+(B*256),x
        sta color_layer1+(B*256),x
    .endrep
    dex
    bne :-
done:
    lda VIC_CTRL1                             ; Un-blank the screen
    ora #%00010000
    sta VIC_CTRL1

    rts

.endproc

;-----------------------------------------------------------------------------
.proc drawSetStageColor
    tay
    ldx #0
    lda stageColor,y
    sta VIC_BORDERCOLOR
:    .repeat 4, B
        sta color_layer0+(B*256),x
        sta color_layer1+(B*256),x
    .endrep
    dex
    bne :-
    lda stageTextColor,y
    ldx #39
:   sta color_layer0,x
    sta color_layer1,x
    sta color_layer0+23*40,x
    sta color_layer1+23*40,x
    dex
    bne :-
    rts
.endproc

;-----------------------------------------------------------------------------
.proc drawSetColor
    ldx #0
:    .repeat 4, B
        sta color_layer0+(B*256),x
        sta color_layer1+(B*256),x
    .endrep
    dex
    bne :-
    rts
.endproc

;-----------------------------------------------------------------------------
; Just do some color increments
.proc drawInvertVisibleScreen

    lda color_layer0
    clc
    adc #$10
    jmp drawSetColor
.endproc

;-----------------------------------------------------------------------------
; Plot a square pixel
; Coords in x and y registers
; width and height in 1's but min "pixel" plot size is 4x4 pixels
.proc drawPlotXY

    width             = tempBlock + 14          ; Param (local variables come after uiWriteName locals)
    height            = tempBlock + 15          ; Param
    iSide             = tempBlock + 16          ; internal
    iX0               = tempBlock + 17          ; internal
    iX1               = tempBlock + 18          ; internal
    iY                = tempBlock + 19          ; internal
    iWidth            = tempBlock + 20          ; internal
    iHeight           = tempBlock + 21          ; internal
    iPixels           = tempBlock + 22          ; internal
    scrnPtrL          = tempBlock + 23          ; internal
    scrnPtrH          = tempBlock + 24          ; internal

    txa
    sta iX0
    lsr                                         ; put odd / even in carry
    lda #0
    rol
    sta iSide                                   ; and save as side
    tya                                         ; Y * 4
    asl
    asl
    sta iY
    lda height
    sta iHeight

loop:
    ldx iSide
    lda plotPix,x                               ; get 0b11110000 or 0b00001111 based on side (odd/even)
    sta iPixels

    lda iX0                                     ; start from X0
    sta iX1

    lda width
    sta iWidth

:   jsr doPlot4x4                               ;(using iX1, iY & iPixels)
    dec iWidth                                  ; do width times 4x pixels
    beq :+
    lda iPixels                                 ; swap sides
    and #1
    eor #1
    tax
    lda plotPix,x
    sta iPixels
    inc iX1
    bne :-

:   dec iHeight                                 ; do height times 4x pixels
    beq :+                                      ; done
    inc iY
    inc iY
    inc iY
    inc iY
    bne loop
:   rts

doPlot4x4:
    sei
    lda #RAMONLY
    sta R6510
    ldy iY
    lda iX1
    lsr                                         ; x / 2 for char columns
    tax
    clc
    lda rowL,y                                  ; get vram address
    adc times8L,x
    sta scrnPtrL
    lda rowH,y
    adc times8H,x
    adc zVramH
    sta scrnPtrH
    ldy #0                                      ; and plot iPixels in 4 in rows
    lda iPixels
    ora (scrnPtrL),y
    sta (scrnPtrL),y
    iny
    lda iPixels
    ora (scrnPtrL),y
    sta (scrnPtrL),y
    iny
    lda iPixels
    ora (scrnPtrL),y
    sta (scrnPtrL),y
    iny
    lda iPixels
    ora (scrnPtrL),y
    sta (scrnPtrL),y
    lda #$36
    sta R6510
    cli
    rts

.endproc

;-----------------------------------------------------------------------------
; Generic routine to draw a sprite rect to the screen.  Sets zCollision <> 0
; when the pixels from this sprite overlapped with pixels already drawn
; Parameters - see zaDraw* below
.proc drawSprite

    zaDrawWorldHeight    = tempBlock + 2        ; parameter - where on screen
    zaDrawSprWidth       = tempBlock + 3        ; parameter - # of columns in sprite
    zaDrawSprHeight      = tempBlock + 5        ; parameter - # of rows in sprite
    zaDrawByte           = tempBlock + 6
    zaCurCharTop         = tempBlock + 12
    zaActiveCharTop      = tempBlock + 13
    zaCurCharOffset      = tempBlock + 14
    zaActiveCharOffset   = tempBlock + 15
    zaLocalDrawWidth     = tempBlock + 16

    lda zaDrawWorldHeight                       ; out, off the top of the paly area?
    cmp #WORLD_START
    bcs draw
    rts

draw:
    tay
    and #%11111000
    sta zaCurCharTop                            ; char-row-top
    tya
    and #%00000111
    sta zaCurCharOffset                         ; how far into the char-row past the top

    lda zaDrawSprWidth
    sta zaLocalDrawWidth

    lda zScreenCol
    lsr                                         ; 64 to 32, really
    tay
    lda times8L,y
    sta zScreenColL                             ; get the column X offset into screen
    lda times8H,y
    sta zScreenColH

    sei
    lda #RAMONLY
    sta R6510

col:
    ldx zaDrawSprHeight                         ; how many rows to draw
    dex                                         ; zero based for writing (in X)
    lda zaCurCharOffset
    sta zaActiveCharOffset                      ; init a per-char-row row counter
    ldy zaCurCharTop
    sty zaActiveCharTop                         ; and make a copy of the char-row-top

row:
    clc                                         ; calculate the vram address
    lda rowL,y
    adc zScreenColL
    sta write+1
    sta write+4
    lda rowH,y
    adc zScreenColH
    adc zVramH
    sta write+2
    sta write+5

    ldy zaActiveCharOffset                      ; y is the per-char-row row counter

offset:
    lda PLACEHOLDER,x                           ; this address is modified by the caller (sprite data)
    sta zaDrawByte                              ; save the byte

write:
    eor PLACEHOLDER,y                           ; get what's on screen xor'd with what's being added
    sta PLACEHOLDER,y                           ; save that to the screen
    and zaDrawByte                              ; mask off any bits that the sprite isn't setting
    cmp zaDrawByte                              ; see if the sprite overlapped something there already
    clc                                         ; cmp can set carry.  keep it clear
    beq :+                                      ; if 0 then no overlap / collision
    inc zCollision                              ; there's a collision, count it
:
    dex                                         ; one row done
    bmi next_col                                ; if x < 0 all rows, this sprite column, done
    dey                                         ; go up one row in this character row
    bpl offset                                  ; 0+ still this character row
    lda #7                                      ; stepped up one char-row so 8 new pixel rows to do
    sta zaActiveCharOffset
    sec
    lda zaActiveCharTop                         ; move the char-row to up to next char-row (8 pixel rows)
    sbc #8
    cmp #WORLD_START                            ; if out of play area, done this sprite column
    bcc next_col
    sta zaActiveCharTop
    tay                                         ; keep the per-char-row counter in Y
    bne row                                     ; BRA BRanch Always
next_col:
    dec zaLocalDrawWidth                        ; one less sprite column to do
    bmi cli_done                                ; if < 0 then sprite draw done
    clc
    lda offset+1                                ; move along the sprite data to the next column start
    adc zaDrawSprHeight
    sta offset+1
    bcc :+
    inc offset+2
    clc
:   lda zScreenColL                             ; move X along by 8 bytes, to X+1 in screen char-columns
    adc #8
    sta zScreenColL
    bcc col
    inc zScreenColH
    bne col                                     ; BRA

cli_done:
    lda #$36
    sta R6510
    cli

done:
    rts

.endproc

;-----------------------------------------------------------------------------
.proc drawSpriteColor
    zaDrawWorldHeight    = tempBlock + 2        ; parameter - where on screen
    zaDrawSprWidth       = tempBlock + 3        ; parameter - # of columns in sprite
    zaDrawSprHeight      = tempBlock + 5        ; parameter - # of rows in sprite
    zaCurCharRow         = tempBlock + 12       ;
    zaCharColHeight      = tempBlock + 13       ;
    zaCurCharOffset      = tempBlock + 14       ; parameter - Filled in by drawSprite

    ldy #0                                      ; start with drawing no vertical bars
    clc
    lda zaDrawWorldHeight
    adc #1
    and #7
    beq :+
    cmp zaDrawSprHeight                         ; if over >= spr.draw.heigt then fits in 1 (bomb)
    bcs smallFits
    iny                                         ; if ((spr.draw.heigt +1)&7) then 1 vert bar
smallFits:
    clc
:   sty zaCharColHeight
    lda zaDrawSprHeight
    adc #7
    lsr
    lsr
    lsr
    clc
    adc zaCharColHeight                         ; vert.bar += ((spr.height+7)&7)
    sta zaCharColHeight
    lda zaDrawWorldHeight                       ; vert.col.start = spr.draw.height / 8
    lsr
    lsr
    lsr
    tay
row:
    sty zaCurCharRow
    lda zScreenCol                              ; scrncol / 2 = X
    lsr
    clc
    adc colRowL,y                               ; make pointer
    sta zScreenColL
    lda colRowH,y
    adc zColorH
    sta zScreenColH
    ldy zaDrawSprWidth                          ; do width columns horizontal
    lda zSpriteColor
:   sta (zScreenColL),y                         ; put the color in
    dey
    bpl :-
    dec zaCharColHeight                         ; over CharColHeight vertical bars
    beq :+
    ldy zaCurCharRow                            ; go up a row - drawing is bottom up on screen
    dey
    bpl row
:   rts

.endproc

;-----------------------------------------------------------------------------
; Draws the player's ship using drawSprite
; Takes no parameters
.proc drawPlayer

    zaDrawWorldHeight = tempBlock + 2
    zaDrawSprHeight   = tempBlock + 5
    zaDrawSprWidth    = tempBlock + 3
    explFrame         = tempBlock + 9           ; Persistent across a death animation - explosion explFrame

    lda playerShipY
    sta zaDrawWorldHeight

    lda #SHIP_HEIGHT
    sta zaDrawSprHeight

    lda playerShipX                             ; mark where on screen to draw
    sta zScreenCol
    clc
    adc bufferDraw                              ; make enemyBuffer relative to screen col 0
    sta zEnemyCol                               ; mark where enemies would start that intersect with the ship

    lda playerDead                              ; if playerDead <> 0 then the player
    bne explode                                 ; is dead and should explode

    lda #2                                      ; set the dimensions of the ship (draw with is this +1)
    sta zaDrawSprWidth

    ldy stage
    lda playerColor,y
    sta zSpriteColor

    lda zScreenCol
    and #1
    beq evenScreen

oddScreen:
    lda #<shipU                                 ; point at the ship sprite data
    sta drawSprite::offset + 1
    lda #>shipU
    sta drawSprite::offset + 2
    bne draw

evenScreen:
    lda #<shipA                                 ; point at the ship sprite data
    sta drawSprite::offset + 1
    lda #>shipA
    sta drawSprite::offset + 2

draw:
    jsr drawSprite                              ; draw the sprite
    jsr drawSpriteColor
    lda zCollision                              ; if there's a collision, kill the player
    beq done

    ldx zEnemyCol                               ; player collided - see if it was with an enemy
    ldy #SHIP_WIDTH

colLoop:
    lda playerShipY                             ; if p ship top < enemy.bot then no collision
    sec
    sbc #SHIP_HEIGHT
    cmp enemyHgtBuffer, x
    bcs notHit
    sec
    lda enemyHgtBuffer, x                       ; if enemy top < p ship bot then no collision
    sbc #RADAR_HEIGHT
    cmp playerShipY
    bcs notHit

    lda #1                                      ; they intersect so kill the enemy (assume just 1 enemy hit)
    sta zaDrawSprWidth
    jsr gameKillEnemy                           ; kill the enemy that collided with the player
    jmp gamePlayerCollision                     ; and kill the player if it collided with an enemy

notHit:
    inc zEnemyCol                               ; advance the column where the enemy may be that collided with the player
    inx
    dey                                         ; check all columns for the player ship
    bne colLoop
    jmp gamePlayerCollision                     ; and if no enemy collision, just kill the player

done:
    rts

explode:
    inc explFrame                               ; advance the local explFrame counter
    lda explFrame
    lsr                                         ; Slow it down
    tax                                         ; and see if it is .ge. 4
    cpx #4
    bcc :+
    ldx #0                                      ; if so, wrap back to zero
    stx explFrame
:
    stx audioExplFrame
    lda audioFrame
    and #<~(AUDIO_MOTOR_FWD | AUDIO_MOTOR_REW | AUDIO_MOTOR_PLAY)
    ora #AUDIO_EXPLOSION
    sta audioFrame

    lda #3                                      ; set the dimensions of the explosion
    sta zaDrawSprWidth

    lda explosionAL,x                           ; point at the explosion sprite data
    sta drawSprite::offset + 1
    lda explosionAH,x
    sta drawSprite::offset + 2

    jmp drawSprite                              ; draw the explosion sprite instead of the ship

.endproc

;-----------------------------------------------------------------------------
; Draws a single column of a radar sprite (because of clipping)
; Takes the enemy flags as a parameter
; Radar is either 2 byte AB (A being col 0 & 1 and B being 2 & 3) or
; 3 byte CDE where C is blank & 0, D is 1 & 2 and E is 3 and blank)
; On odd, the column can only be 00 because odd 1 is drawn by even A,
; odd 2 is drawn by even 1 (D) and odd 3 is drawn by even B.
; Even can be 0 (A), 1(D), 2(B) or 3(E)
.proc drawRadar

    zaFrame           = tempBlock + 6           ; internal
    zaDrawWorldHeight = tempBlock + 2           ; setup for drawSprite
    zaDrawSprHeight   = tempBlock + 5
    zaDrawSprWidth    = tempBlock + 3
    zaSkipLength      = tempBlock + 7

    and #%01111100                              ; frame and column
    lsr                                         ; column to 1s
    lsr
    sta zaFrame                                 ; save

    lda enemyHgtBuffer, x                       ; get the height - 1 pixel above the terrain
    sta zaDrawWorldHeight

    lda #RADAR_HEIGHT
    sta zaDrawSprHeight

    ldy stage
    lda radarColor,y
    sta zSpriteColor

    lda zScreenCol                              ; see if it's an even or odd screen sub-column
    and #$01
    beq evenScreen

oddScreen:

    lda #(PENXSIZE-1)                           ; check the right edge
    sec                                         ; for clipping
    sbc zScreenCol
    lsr
    cmp #3
    bcc :+
    lda #2                                      ; maximum 3 (0-2) bytes to write
:
    sta zaDrawSprWidth

    lda zaFrame                                 ; ignore column - will/must be 00
    lsr
    lsr
    tax
    lda radarUL, x                              ; get the frame
    sta drawSprite::offset + 1
    lda radarUH, x
    sta drawSprite::offset + 2
    lda #4                                      ; and set the step size
    sta zaSkipLength
    bne draw

evenScreen:
    ldx zaFrame                                 ; frame + col is offset in table
    lda radarAL, x                              ; point at data in table index x
    sta drawSprite::offset + 1
    lda radarAH, x
    sta drawSprite::offset + 2
    txa
    and #%00000011                              ; extract just the column
    tax
    lda radarAS, x                              ; and see how many bytes to skip based on column
    sta zaSkipLength
    lda radarAR, x                              ; see how many bytes to render
    sta zaDrawSprWidth

    lda zScreenCol
    cmp #(PENXSIZE - 2)                         ; last column only draw 1 byte
    bcc draw
    lda #0
    sta zaDrawSprWidth                          ; save as draw width

draw:
    jsr drawSprite
    jmp drawSpriteColor

.endproc

;-----------------------------------------------------------------------------
; Draws a missile on-screen
; Takes the flags as a parameter
.proc drawMissile

    zaFrame           = tempBlock + 6           ; internal
    zaDrawWorldHeight = tempBlock + 2           ; setup for drawSprite
    zaDrawSprHeight   = tempBlock + 5
    zaDrawSprWidth    = tempBlock + 3
    zaSkipLength      = tempBlock + 7

    tay

    lda enemyHgtBuffer, x                       ; get the height - 1 pixel above the terrain
    sta zaDrawWorldHeight                       ; while x is still good

    tya
    and #%11000100                              ; launch mask, frame and column
    lsr                                         ; column to 2s
    bit Bit76Mask                               ; check if in the air
    beq :+
    ora #%00000001                              ; yes - force frame 1
:
    and #%00000011
    tax

    lda #MISSILE_HEIGHT
    sta zaDrawSprHeight

    ldy stage
    lda missileColor,y
    sta zSpriteColor

    lda zScreenCol                              ; see if it's an even or odd screen sub-column
    and #$01
    beq evenScreen

oddScreen:

    lda zScreenCol
    cmp #(PENXSIZE-1)
    bne :+
    lda #0
    beq :++
:
    lda #1
:
    sta zaDrawSprWidth

    lda missileUL, x                            ; point at data in table index x
    sta drawSprite::offset + 1
    lda missileUH, x
    sta drawSprite::offset + 2
    lda #2
    sta zaSkipLength
    bne draw

evenScreen:
    lda missileAL, x                            ; point at data in table index x
    sta drawSprite::offset + 1
    lda missileAH, x
    sta drawSprite::offset + 2

    lda #1                                      ; and see how many bytes to skip based on column
    sta zaSkipLength
    lda #0
    sta zaDrawSprWidth                          ; save as draw width

draw:
    jsr drawSprite
    jmp drawSpriteColor

.endproc

;-----------------------------------------------------------------------------
; Draws a nuke on-screen
; Takes the flags as a parameter
.proc drawNuke

    zaEnemyType       = tempBlock + 1
    zaFrame           = tempBlock + 6           ; internal
    zaDrawWorldHeight = tempBlock + 2           ; setup for drawSprite
    zaDrawSprHeight   = tempBlock + 5
    zaDrawSprWidth    = tempBlock + 3
    zaSkipLength      = tempBlock + 7

    lda enemyHgtBuffer, x                       ; get the height - 1 pixel above the terrain
    sta zaDrawWorldHeight                       ; while x is still good

    lda nukeColor
    sta zSpriteColor

    lda zaEnemyType
    ldx #0
    bit Bit3Mask
    beq :+
    inx

:
    lda #NUKE_HEIGHT
    sta zaDrawSprHeight

    lda zScreenCol                              ; see if it's an even or odd screen sub-column
    and #$01
    beq evenScreen

oddScreen:
    lda zScreenCol                              ; see if clipping to right hand side is needed
    cmp #(PENXSIZE-1)
    bne :+
    lda #0
    beq :++
:
    lda #1
:
    sta zaDrawSprWidth                          ; save how many bytes to render

    lda nukeUL, x                               ; point at data in table index x
    sta drawSprite::offset + 1
    lda nukeUH, x
    sta drawSprite::offset + 2

    lda #2                                      ; odd screen nuke is 2 bytes (col can't be 1)
    sta zaSkipLength
    bne draw

evenScreen:
    lda #0
    sta zaDrawSprWidth                          ; save as draw width

    lda nukeAL, x                               ; point at data in table index x
    sta drawSprite::offset + 1
    lda nukeAH, x
    sta drawSprite::offset + 2

    lda #1                                      ; even screen nuke is 1 byte (col 0 or 1)
    sta zaSkipLength

draw:
    jsr drawSprite
    jsr drawSpriteColor
    lda #0
    sta zCollision
    rts

.endproc

;-----------------------------------------------------------------------------
; Takes the flags as a parameter
.proc drawMonster

    zaFrame           = tempBlock + 6           ; internal
    zaDrawWorldHeight = tempBlock + 2           ; setup for drawSprite
    zaDrawSprHeight   = tempBlock + 5
    zaDrawSprWidth    = tempBlock + 3
    zaSkipLength      = tempBlock + 7

    tay

    lda enemyHgtBuffer, x                       ; get the height - 1 pixel above the terrain
    sta zaDrawWorldHeight                       ; while x is still good

    ldx stage
    lda monsterColor,x
    sta zSpriteColor

    lda #MONSTER_HEIGHT                         ; monster is always 2 bytes
    sta zaDrawSprHeight

    tya
    lsr
    lsr
    and #%00000011
    tax

    lda zScreenCol                              ; see if it's an even or odd screen sub-column
    lsr
    bcc evenScreen

oddScreen:
    lda zScreenCol                              ; see if clipping to right hand side is needed
    cmp #(PENXSIZE-1)
    bne :+
    lda #0
    beq :++
:
    lda #1
:
    sta zaDrawSprWidth                          ; save how many bytes to render

    lda #<monsterU                              ; point at data in table index x
    sta drawSprite::offset + 1
    lda #>monsterU
    sta drawSprite::offset + 2

    lda #3                                      ; odd screen monster is 2 bytes (col can't be 1)
    sta zaSkipLength
    bne draw

evenScreen:
    lda monsterAR, x
    sta zaDrawSprWidth                          ; save as draw width

    lda monsterAL, x                            ; point at data in table index x
    sta drawSprite::offset + 1
    lda monsterAH, x
    sta drawSprite::offset + 2

    lda monsterAS, x                            ; even screen monster is 1 byte (col 0 or 1)
    sta zaSkipLength

draw:
    jsr drawSprite
    jmp drawSpriteColor

.endproc

;-----------------------------------------------------------------------------
; Draws all the bombs on-screen
; Takes no parameters
.proc drawBombs

    zaBombIndex       = tempBlock + 1           ; internal - which of the bombs
    zaDrawWorldHeight = tempBlock + 2           ; for drawSprite
    zaDrawSprHeight   = tempBlock + 5
    zaDrawSprWidth    = tempBlock + 3

    ldx #NUM_BOMBS - 1                          ; 0 based index

loop:
    lda bombY, x                                ; get the height of the bomb
    bne doBomb                                  ; 0 is not active, otherwise height

nextBomb:
    dex
    bpl loop
    clc
    rts

doBomb:
    stx zaBombIndex
    sta zaDrawWorldHeight                       ; save the height

    ldy stage
    lda bombColor,y
    sta zSpriteColor

    lda bombX, x
    sta zScreenCol
    and #$01
    beq evenScreen

oddScreen:
    lda #1
    sta zaDrawSprWidth                          ; save as draw width

    lda bombDir, x                              ; select the sprite based on the state
    tax
    beq :+                                      ; if .gt. 0 then it's bomb 1
    ldx #1
:
    lda bombUL, x                               ; forward travelling bomb
    sta drawSprite::offset + 1
    lda bombUH, x
    sta drawSprite::offset + 2
    lda bombH, x
    sta zaDrawSprHeight
    bne draw

evenScreen:
    lda #0
    sta zaDrawSprWidth                          ; save as draw width

    lda bombDir, x                              ; select the sprite based on the state
    tax
    beq :+
    ldx #1
:
    lda bombAL, x                               ; forward travelling bomb
    sta drawSprite::offset + 1
    lda bombAH, x
    sta drawSprite::offset + 2
    lda bombH, x
    sta zaDrawSprHeight

draw:
    jsr drawSprite
    jsr drawSpriteColor

    lda zCollision
    beq nextBombX

    lda zScreenCol
    clc
    adc bufferDraw                              ; make enemyBuffer relative to screen col 0
    tax
    ldy #2

tryEnemy:
    stx zEnemyCol                               ; may be a collision with enemy
    lda enemyHgtBuffer, x                       ; is there an enemy in this row?
    beq noBombHit                               ; no - maybe next column?

checkCol:
    sec
    sbc #RADAR_HEIGHT                           ; assume tallest enemy (favors the player)
    cmp zaDrawWorldHeight                       ; compare to bombY
    bcs noBombHit                               ; E top .le. b bot (carry clear) is maybe collision
    lda zaDrawWorldHeight                       ; get the bombY
    sec
    sbc #BOMB_HEIGHT                            ; calc bomb top
    cmp enemyHgtBuffer, x                       ; B top .le. E bot (carry clear) is a collision
    bcc bombHit

noBombHit:
    inx                                         ; maybe bomb spans 2 cols - check next column
    dey                                         ; see if bomb is over 2 cols
    beq bombDies                                ; if 0 done all columns
    bne tryEnemy                                ; JuMP

bombHit:
    lda #1                                      ; enemy is in this 1 column
    sta zaDrawSprWidth

    jsr gameKillEnemy                           ; see if the bomb killed an enemy
    lda enemyHitType                            ; figure out if there's score
    bmi bombDies
    jsr gameAddScore

bombDies:
    ldx zaBombIndex
    lda #0                                      ; now kill the bomb itself
    sta bombY, x                                ; by setting its height to 0
    sta zCollision

nextBombX:
    ldx zaBombIndex
    jmp nextBomb

.endproc


;-----------------------------------------------------------------------------
.proc drawBullets

    zaOffset          = tempBlock + 1
    zaDrawSprWidth    = tempBlock + 3
    zaBulletCol       = tempBlock + 5
    zaMask            = tempBlock + 6
    zaSecond          = tempBlock + 7

    lda #0                                      ; work by screen columns
    sta zScreenCol                              ; starting at 0

    ldx bulletIndex                             ; x is the index for the bullet in the buffer

loop:
    lda bulletsBuffer, x                        ; get the column
    bne bullet                                  ; and if non-zero, there's a bullet in this column

next:
    inx                                         ; next x
    inc zScreenCol                              ; and next screen column
    lda zScreenCol                              ; see if the screen column is
    cmp #PENXSIZE                               ; past the end of the screen
    bcc loop                                    ; if not, keep going
finally:
    lda #0
    sta bulletsBuffer, x                        ; Kill any overflow bullets
    inx
    sta bulletsBuffer, x                        ; Kill any overflow bullets
    clc                                         ; done - clear carry and end
    rts

bullet:
    tay                                         ; put height of bullet in Y
    stx zaBulletCol                             ; save x buffer position
    lda zScreenCol                              ; see where on screen
    lsr                                         ; make screen char column
    tax                                         ; save that in x
    bcs odd                                     ; if carry, off column
    lda #%11110000                              ; even draw 11111111 & 11110000
    sta zaSecond
    lda #%11111111
    bne loc
odd:
    lda #%11111111                              ; odd draw 00001111 & 11111111
    sta zaSecond
    lda #%00001111
loc:
    sta zaMask                                  ; put what to draw in the mask
    clc                                         ; get a vram address
    lda rowL,y
    adc times8L,x
    sta zScreenColL
    lda rowH,y
    adc times8H,x
    adc zVramH
    sta zScreenColH
    ldy #0                                      ; at offset zero
    sei
    lda #RAMONLY
    sta R6510
    lda zaMask                                  ; get the mask to write
    eor (zScreenColL),y
    sta (zScreenColL),y
    ldx #$36
    stx R6510
    cli
    and zaMask
    cmp zaMask
    bne collision

    lda zScreenCol                              ; see if the next col is off-screen
    cmp #PENXSIZE-2
    bcc :+
    ldx zaBulletCol
    jmp next
:
    ldy #8                                      ; next col is 8 bytes to the right
    sei
    lda #RAMONLY
    sta R6510
    lda zaSecond                                ; get the byte
    sta zaMask
    eor (zScreenColL),y
    sta (zScreenColL),y
    ldx #$36
    stx R6510
    cli
    and zaMask
    cmp zaMask
    bne collision
    ldx zaBulletCol                             ; go back to the loop using the next
    inx                                         ; buffer and screen column
    inc zScreenCol
    jmp next

collision:
    lda #2                                      ; a bullet is 3 columns wide
    sta zaOffset
    lda zScreenCol                              ; index into screen
    clc
    adc bufferDraw                              ; and make relative to enemy buffer
    tay
:
    lda enemyHgtBuffer, y                       ; see if there's an enemy
    bne hasEnemy
    iny
    dec zaOffset
    bpl :-
    bmi endBullet

hasEnemy:
    ldx zaBulletCol                             ; load the bullet index in x
    sec
    sbc bulletsBuffer, x                        ; see where it hit relative to enemy
    bcc endBullet                               ; bullet hit lower
    cmp #RADAR_HEIGHT                           ; since it hit anyway, use tallest enemy
    bcs endBullet                               ; it hit higher

    lda #1
    sta zaDrawSprWidth                          ; gameKillEnemy looks at this to see how wide to look for a kill
    sty zEnemyCol
    jsr gameKillEnemy
    lda enemyHitType                            ; figure out if there's score
    bmi endBullet
    jsr gameAddScore

endBullet:
    ldx zaBulletCol                             ; load the bullet index in x
    lda #0
    sta bulletsBuffer, x
    jmp next                                    ; JuMP

.endproc

;-----------------------------------------------------------------------------
.proc drawExplosions

    zaFrame           = tempBlock + 6           ; internal
    zaDrawWorldHeight = tempBlock + 2           ; setup for drawSprite
    zaDrawSprHeight   = tempBlock + 5
    zaDrawSprWidth    = tempBlock + 3
    zaExplodeCol      = tempBlock + 10

    lda #0                                      ; work by screen columns
    sta zScreenCol                              ; starting at 0

    ldx bufferDraw                              ; x is the index for the bullet

loop:
    lda explosionBuffer, x                      ; get the column
    bne explode                                 ; and if non-zero, there's a bullet in this column

next:
    inx                                         ; next x
    inc zScreenCol                              ; and next screen column
    lda zScreenCol                              ; see if the screen column is
    cmp #PENXSIZE                               ; past the end of the screen
    bcc loop                                    ; if not, keep going
    lda #0
    sta zCollision
    clc                                         ; done - clear carry and end
    rts

explode:
    stx zaExplodeCol

    pha
    and #%00000011                              ; frame
    sta zaFrame                                 ; save

    pla
    and #%11111000                              ; height
    sta zaDrawWorldHeight

    lda #EXPLOSION_HEIGHT
    sta zaDrawSprHeight

    lda zScreenCol                              ; see if it's an even or odd screen sub-column
    and #$01
    beq evenScreen

oddScreen:

    lda #(PENXSIZE-1)                           ; check the right edge
    sec                                         ; for clipping
    sbc zScreenCol
    lsr
    cmp #3
    bcc :+
    lda #2                                      ; maximum 3 (0-2) bytes to write
:
    sta zaDrawSprWidth

    ldx zaFrame                                 ; frame + col is offset in table
    lda explosionUL, x                          ; get the frame
    sta drawSprite::offset + 1
    lda explosionUH, x
    sta drawSprite::offset + 2
    bne draw

evenScreen:
    ldx zaFrame                                 ; frame + col is offset in table
    lda explosionAL, x                          ; point at data in table index x
    sta drawSprite::offset + 1
    lda explosionAH, x
    sta drawSprite::offset + 2

    lda zScreenCol
    cmp #(PENXSIZE - 2)                         ; last column only draw 1 byte
    bcc :+
    lda #0
    beq :++
:
    lda #1
:
    sta zaDrawSprWidth                          ; save as draw width

draw:
    jsr drawSprite
    ldx zaExplodeCol
    jmp next

.endproc

;-----------------------------------------------------------------------------
; Iterate over the enemies on screen and get them drawn to the back buffer
; Parameter - zCollision must be 0 when called
.proc drawEnemies

    zaEnemyType       = tempBlock + 1           ; parameter to the specific enemy draw call
    zaDrawSprWidth    = tempBlock + 3
    zaSkipLength      = tempBlock + 7

    lda terrainOrigin                           ; will always be 0 since this isn't called till screen fully scrolled in
    sta zScreenCol                              ; start drawing here on-screen

    ldx bufferDraw                              ; make enemyBuffer relative to screen col 0
    stx zEnemyCol                               ; start here processing enemies

loop:
    lda enemyBuffer, x                          ; check this column for a (partial) enemy (just a strip)
    beq continue                                ; skip non-enemy columns

    sta zaEnemyType                             ; save the flags

    bit Bit34Mask                               ; check the column
    beq evalType                                ; col0 always evaluated
    lda zScreenCol                              ; Get the column
    bit Bit1Mask                                ; see if odd or even
    bne continue                                ; if odd, ignore
    lda zaEnemyType                             ; if even, need to draw type

evalType:
    bit Bit1Mask                                ; see if this is a missile (lsb set)
    bne missileOrNuke                           ; bits match so it's a missile

    bit Bit2Mask                                ; see if it's a radar
    bne doRadar

    jsr drawMonster                             ; lower 2 bits clear is a monster
    bcc colchk                                  ; drawSprite always exits with carry clear so this is a jmp

doRadar:
    jsr drawRadar
    bcc colchk                                  ; will always be clear, so in effect jmp

missileOrNuke:
    bit Bit2Mask
    beq missile
    jsr drawNuke
    bcc colchk                                  ; JuMP

missile:
    jsr drawMissile

colchk:
    lda gameMode                                ; in the edit mode, collision detection doesn't do anything
    cmp #GAME_MODE_EDIT
    clc
    beq step
    lda zCollision                              ; see if this enemy is in collision (for missiles with terrain)
    beq step
    inc zaDrawSprWidth
    jsr gameKillEnemy

step:
    lda zaSkipLength
    adc zScreenCol
    cmp #PENXSIZE
    bcs done
    sta zScreenCol
    clc
    lda zaSkipLength
    adc zEnemyCol
    sta zEnemyCol
    tax
    jmp loop

continue:
    inc zScreenCol
    ldx zScreenCol
    cpx #PENXSIZE
    bcs done
    inc zEnemyCol
    ldx zEnemyCol
    jmp loop

done:
    rts

.endproc
