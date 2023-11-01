;-----------------------------------------------------------------------------
; draw.inc
; Part of penetrator, the zx spectrum game, made for commander x16
;
; Stefan Wessels, 2019
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
    beq :+

    lda VERA::DISP::VIDEO
    and #%11001111                              ; both latyers off
    ora #%00010000                              ; turn layer 0 on
    sta VERA::DISP::VIDEO

    lda #>ram_layer1
    sta zVramH
    rts 

:
    lda VERA::DISP::VIDEO
    and #%11001111                              ; both latyers off
    ora #%00100000                              ; turn layer 1 on
    sta VERA::DISP::VIDEO

    lda #>ram_layer0
    sta zVramH
    rts 

.endproc 

;-----------------------------------------------------------------------------
; Clears some (or all) rows of a layer
; x - layer, y - start row in layer, a - no of rows to clear
.proc drawClearRows

    pha 
    clc 
    lda rowL, y                                 ; strictly also adc layersL, x but always 256-byte aligned
    sta VERA::ADDR                              ;LO
    lda rowH, y
    adc layersH, x
    sta VERA::ADDR + 1                          ;MID
    lda #$10                                    ; 1 byte step size and 0 for top address
    sta VERA::ADDR + 2                          ;HI
    pla                                         ; put the # of rows in Y
    tay 
    lda #$00
row:
    ldx #XSIZE                                  ; and all columns
:
    sta VERA::DATA0                             ; set to 0
    dex 
    bne :-
    dey 
    bne row
    rts 

.endproc

;-----------------------------------------------------------------------------
.proc drawClearScreen

    ldx backLayer                               ; layer
    ldy #0                                      ; start row
    lda #YSIZE                                  ; end row (+1)
    jsr drawClearRows                           ; clear the whole layer

    jsr drawPresent

    ldx backLayer
    ldy #0
    lda #YSIZE
    jmp drawClearRows

.endproc 

;-----------------------------------------------------------------------------
; Install a palette from gamePalette
; a - the stage number (really the palette index)
; y - the length of palette
.proc drawSetPalette

    asl                                         ; mult the palette index by 8
    asl 
    asl 
    tax                                         ; use as offset into palette table
    
    lda #$11                                    ; set vera for palette entry
    sta VERA::ADDR + 2                          ; HI
    lda #>$FA00
    sta VERA::ADDR + 1                          ; MID
    lda #<$FA00
    sta VERA::ADDR                              ; LO

:
    lda gamePalette, x                          ; store the palette into vera
    sta VERA::DATA0
    inx 
    dey 
    bne :-

    lda #$00                                    ; restore the HI addr to 0 (is assumed elsewhere)
    sta VERA::ADDR + 2                          ; HI

    rts 

.endproc 

;-----------------------------------------------------------------------------
; Plot a square pixel
; Coords in x and y registers
; width and height in 1's but min "pixel" plot size is 4x4 pixels
; the byte mask to write in plotCol
.proc drawPlotXY

    width   = tempBlock + 14                    ; Param (local variables come after uiWriteName locals)
    height  = tempBlock + 15                    ; Param
    plotCol = tempBlock + 16                    ; Param
    rows    = tempBlock + 17                    ; internal
    x0      = tempBlock + 18                    ; internal

    stx x0                                      ; save the x

    tya                                         ; y * 4 since min width is 4 pixels wide, height must be min 4 as well
    asl 
    asl 
    tay                                         ; put the draw height in Y

    lda height                                  ; Adjust the height up by 4x as well
    asl 
    asl 
    sta rows                                    ; save as count for how many rows

    lda #$10                                    ; to be sure, set the stride to 1
    sta VERA::ADDR + 2                          ; HI

loop:
    lda rowL, y 
    adc x0                                      ; get the x y address
    sta VERA::ADDR                              ; LO
    lda rowH, y 
    adc zVramH 
    sta VERA::ADDR + 1                          ; MID
    lda plotCol                                 ; get the plot color
    ldx width                                   ; get how wide to go
:
    sta VERA::DATA0                             ; write one row of pixels
    dex 
    bne :-
    iny                                         ; keep doing till
    dec rows                                    ; all rows were written
    bne loop 

    rts 

.endproc 

;-----------------------------------------------------------------------------
; Generic routine to draw a sprite rect to the screen.  Sets zCollision <> 0
; when the pixels from this sprite overlapped with pixels already drawn
; Parameters - see zaDraw* below
.proc drawSprite

    zaDrawWorldHeight = zTemp2                  ; parameter - where on screen
    zaDrawSprHeight   = zTemp5                  ; parameter - # of rows in sprite
    zaDrawSprWidth    = zTemp3                  ; parameter - # of columns in sprite
    zaScreenColLocal  = zTemp4                  ; not a parameter - internal for drawing
    zaDrawByte        = zTemp6                  ; not a parameter - internal for collisions

    lda zScreenCol                              ; make a copy since it needs to be modified
    sta zaScreenColLocal

column:
    ldy zaDrawWorldHeight
    cpy #WORLD_START
    bcc done
    clc 
    ldx zaDrawSprHeight
    dex                                         ; 0 based index so adjust height index

rows:
    lda rowL, y                                 ; get the screen row start address, low byte
    adc zaScreenColLocal                        ; add the column to the address
    sta VERA::ADDR                              ; set vera low address
    lda rowH, y                                 ; get the high byte of the screen row start
    adc zVramH                                  ; add the VRAM high byte (for which layer)
    sta VERA::ADDR + 1                          ; set the Vera MID (high is already = 0)
offset:
    lda spriteData, x                           ; this address is modified by the caller
    sta zaDrawByte                              ; save the byte
    eor VERA::DATA0                             ; get what's on screen xor'd with what's being added
    sta VERA::DATA0                             ; save that to the screen
    and zaDrawByte                              ; mask off any bits that the sprite isn't setting
    cmp zaDrawByte                              ; see if the sprite overlapped something there already
    clc                                         ; cmp can set carry.  keep it clear
    beq :+                                      ; if 0 then no overlap / collision
    inc zCollision                              ; there's a collision, count it
:
    dey                                         ; go up a row on screen
    cpy #WORLD_START 
    bcc done
    clc                                         ; make sure carry stays clear on exit from drawSprite
    dex                                         ; go to the previous byte of the sprite also
    bpl rows                                    ; keep going till all rows of this column are done

    inc zaScreenColLocal                        ; go over to the next column
    dec zaDrawSprWidth                          ; mark that one column of the width of the sprite is done
    beq done                                    ; if all columns done, end

    lda zaDrawSprHeight                         ; step the data pointer by the # of bytes
    adc offset + 1                              ; that has been drawn
    sta offset + 1
    bcc column
    inc offset + 2
    clc 
    bcc column                                  ; always = jmp, do the next column

done:
    rts 

.endproc

;-----------------------------------------------------------------------------
; Draws the player's ship using drawSprite
; Takes no parameters
.proc drawPlayer

    explFrame = tempBlock + 1                   ; Persistent across a death animation - explosion explFrame

    zaDrawWorldHeight = zTemp2
    zaDrawSprHeight   = zTemp5
    zaDrawSprWidth    = zTemp3

    lda playerShipX                             ; mark where on screen to draw
    sta zScreenCol
    clc 
    adc bufferDraw                              ; make enemyBuffer relative to screen col 0
    sta zEnemyCol                               ; mark where enemies would start that intersect with the ship

    lda playerShipY
    sta zaDrawWorldHeight

    lda #SHIP_WIDTH                             ; set the dimensions of the ship
    sta zaDrawSprWidth
    lda #SHIP_HEIGHT
    sta zaDrawSprHeight

    lda playerDead                              ; if playerDead <> 0 then the player
    bne explode                                 ; is dead and should explode

    lda #<ship                                  ; point at the ship sprite data
    sta drawSprite::offset + 1
    lda #>ship
    sta drawSprite::offset + 2

    jsr drawSprite                              ; draw the sprite
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
    tax                                         ; and see if it is >= 4
    cpx #4 
    bcc :+
    ldx #0                                      ; if so, wrap back to zero
    stx explFrame

:
    lda explosionColL,x                         ; point at the explosion sprite data
    sta drawSprite::offset + 1
    lda explosionColH,x
    sta drawSprite::offset + 2

    jmp drawSprite                              ; draw the explosion sprite instead of the ship

.endproc

;-----------------------------------------------------------------------------
; Draws a single column of a radar sprite (because of clipping)
; Takes the enemy flags as a parameter
.proc drawRadar

    zaEnemyType       = zTemp1                  ; parameter, see below
    zaFrame           = zTemp6                  ; internal
    zaDrawWorldHeight = zTemp2                  ; setup for drawSprite
    zaDrawSprHeight   = zTemp5
    zaDrawSprWidth    = zTemp3

    and #%01111100
    lsr 
    lsr 
    sta zaEnemyType
    and #%00000011
    sta zaFrame 
    lda zaEnemyType
    and #%00011100
    adc zaFrame
    tay 

    lda radarColL, y                            ; point at the sprite data for this strip (column)
    sta drawSprite::offset + 1
    lda radarColH, y
    sta drawSprite::offset + 2
    
    lda #1                                      ; set up to call drawSprite - 1 column only
    sta zaDrawSprWidth
    lda #RADAR_HEIGHT
    sta zaDrawSprHeight
    lda enemyHgtBuffer, x                       ; get the height - 1 pixel above the terrain
    sta zaDrawWorldHeight

    jmp drawSprite

.endproc 

;-----------------------------------------------------------------------------
; Draws a missile on-screen
; Takes the flags as a parameter
.proc drawMissile

    zaEnemyType       = zTemp1                  ; parameter - see below
    zaFrame           = zTemp6                  ; Internal
    zaDrawWorldHeight = zTemp2                  ; for drawSprite
    zaDrawSprHeight   = zTemp5
    zaDrawSprWidth    = zTemp3

    and #%11001100                              ; mask launch, anim and columns (bit 7 for anim slow blink)
    lsr                                         ; move the column to 0 or 1 value bits
    lsr 
    sta zaEnemyType                             ; save this "mask"
    and #%00000011                              ; extract just the column
    sta zaFrame                                 ; save as the frame (missile is 2 wide)
    lda zaEnemyType                             ; load the launched/frame/column again
    bit Bit6Mask                                ; see if this rocket has launched
    beq :+                                      ; if not, animate away
    lda #2                                      ; has launched - force flame on
    bne air
:
    lsr                                         ; and shift to the frame
    lsr 
    lsr 
air:
    adc zaFrame                                 ; and add the column counter
    tay                                         ; to look up which frame to draw

    lda missileColL, y                          ; point at the sprite data for this column
    sta drawSprite::offset+1
    lda missileColH, y
    sta drawSprite::offset+2

    lda #1                                      ; setup drawSprite to draw one column of missile
    sta zaDrawSprWidth
    lda #MISSILE_HEIGHT
    sta zaDrawSprHeight
    lda enemyHgtBuffer, x                       ; get the height of the missile (can fly) but usually
    sta zaDrawWorldHeight                       ; 1 pixel above the terrain (when not flying)

    jmp drawSprite

.endproc 

;-----------------------------------------------------------------------------
; Draws a nuke on-screen
; Takes the flags as a parameter
.proc drawNuke

    zaEnemyType       = zTemp1                  ; parameter - see below
    zaFrame           = zTemp6                  ; Internal
    zaDrawWorldHeight = zTemp2                  ; for drawSprite
    zaDrawSprHeight   = zTemp5
    zaDrawSprWidth    = zTemp3

    and #%00001100                              ; extract the column
    lsr                                         ; move the column to 0 or 1 value bits
    lsr 
    tay                                         ; to look up which frame to draw

    lda nukeColL, y                             ; point at the sprite data for this column
    sta drawSprite::offset + 1
    lda nukeColH, y
    sta drawSprite::offset + 2

    lda #1                                      ; setup drawSprite to draw one column of nuke
    sta zaDrawSprWidth
    lda #NUKE_HEIGHT
    sta zaDrawSprHeight
    lda enemyHgtBuffer, x                       ; get the height of the nuke
    sta zaDrawWorldHeight

    jmp drawSprite

.endproc 

;-----------------------------------------------------------------------------
; Takes the flags as a parameter
.proc drawMonster

    zaEnemyType       = zTemp1                  ; parameter - see below
    zaFrame           = zTemp6                  ; Internal
    zaDrawWorldHeight = zTemp2                  ; for drawSprite
    zaDrawSprHeight   = zTemp5
    zaDrawSprWidth    = zTemp3

    and #%00001100
    lsr                                         ; move the column to 0 or 1 value bits
    lsr 
    tay                                         ; to look up which frame to draw

    lda monsterColL, y                          ; point at the sprite data for this column
    sta drawSprite::offset+1
    lda monsterColH, y
    sta drawSprite::offset+2

    lda #1                                      ; setup drawSprite to draw one column of monster
    sta zaDrawSprWidth
    lda #MONSTER_HEIGHT
    sta zaDrawSprHeight
    lda enemyHgtBuffer, x                       ; get the height of the monster
    sta zaDrawWorldHeight

    jmp drawSprite

.endproc 

;-----------------------------------------------------------------------------
; Draws all the bombs on-screen
; Takes no parameters
.proc drawBombs 

    zaBombIndex       = zTemp1                  ; internal - which of the bombs
    zaDrawWorldHeight = zTemp2                  ; for drawSprite
    zaDrawSprHeight   = zTemp5
    zaDrawSprWidth    = zTemp3

    ldx #NUM_BOMBS - 1                          ; 0 based index

loop:
    lda bombY, x                                ; get the height of the bomb
    beq nextBomb                                ; if 0, it's not active

    stx zaBombIndex

    sta zaDrawWorldHeight                       ; save the height
    
    lda #BOMB_WIDTH                             ; set up for drawSprite
    sta zaDrawSprWidth

    lda #BOMB_HEIGHT
    sta zaDrawSprHeight

    lda bombX, x
    sta zScreenCol

    lda bombDir, x                              ; select the sprite based on the state
    beq :+

    lda #<bomb1                                 ; forward travelling bomb
    sta drawSprite::offset + 1
    lda #>bomb1
    sta drawSprite::offset + 2
    bne draw                                    ; always JuMP (always <> 0)

:
    lda #<bomb2                                 ; bomb falling straight down
    sta drawSprite::offset + 1
    lda #>bomb2
    sta drawSprite::offset + 2

draw:
    jsr drawSprite

    lda zCollision
    beq nextBombX

    lda zScreenCol 
    clc 
    adc bufferDraw                              ; make enemyBuffer relative to screen col 0
    tax 
    lda enemyHgtBuffer, x                       ; is there an enemy in this row?
    bne checkCol                                ; yes - go check it for collision
    inx                                         ; bomb spans 2 cols - check next column
    lda enemyHgtBuffer, x
    beq bombDies                                ; nothing here either - just kill the bomb

checkCol:
    sec 
    sbc #RADAR_HEIGHT                           ; assume tallest enemy (favors the player)
    cmp zaDrawWorldHeight                       ; compare to bombY
    bcs bombDies                                ; E top <= b bot (carry clear) is maybe collision
    lda zaDrawWorldHeight                       ; get the bombY
    sec 
    sbc #BOMB_HEIGHT                            ; calc bomb top
    cmp enemyHgtBuffer, x                       ; B top <= E bot (carry clear) is a collision
    bcs bombDies

    lda #BOMB_WIDTH 
    sta zaDrawSprWidth
    stx zEnemyCol                               ; may be a collision with enemy
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

nextBomb:
    dex 
    bpl loop

    clc 
    rts 

.endproc


;-----------------------------------------------------------------------------
; Draw all the bullets on-screen
; takes no parameters
.proc drawBullets 

    zaDrawSprWidth = zTemp3 
    zaEnd = zTemp1 
    zaBulletCol = zTemp5 

    lda #0
    sta zScreenCol

    ldx bufferDraw                              ; make enemyBuffer relative to screen col 0
    stx zEnemyCol

    ldx bulletIndex

    txa 
    clc 
    adc #XSIZE
    sta zaEnd

loop:
    lda bulletsBuffer, x                        ; load (height) from the buffer
    beq next                                    ; if = 0 then no bullet in this column

bullet:
    tay                                         ; save the height
    lda zScreenCol                              ; prep the column for screen math

    clc                                         ; put the bullet at height y col x on screen
    adc rowL, y
    sta VERA::ADDR
    lda rowH, y
    adc zVramH
    sta VERA::ADDR + 1                          ; MID
    lda #$ff                                    ; bullet is a solid line
    eor VERA::DATA0
    sta VERA::DATA0
    cmp #$ff                                    ; see if it hit something
    beq next                                    ; no collision, next (prev) column/bullet

    ldy zEnemyCol
    lda enemyHgtBuffer, y                       ; maybe hit an enemy?
    beq nokill
    sec 
    sbc bulletsBuffer, x                        ; see where it hit relative to enemy
    bcc nokill                                  ; bullet hit lower
    cmp #RADAR_HEIGHT                           ; since it hit anyway, use tallest enemy
    bpl nokill                                  ; it hit higher
    stx zaBulletCol                             ; hit an enemy so kill it
    lda #1                                      ; hit an enemy so kill it - bullets kill 1 wide
    sta zaDrawSprWidth                          ; gameKillEnemy looks at this to see how wide to look for a kill
    jsr gameKillEnemy
    lda enemyHitType                            ; figure out if there's score
    bmi :+
    jsr gameAddScore
:
    ldx zaBulletCol
    
nokill:
    lda #0                                      ; height of 0 is no-bullet
    dex                                         ; kill in front and behind this bullet (x always at least 1 here)
    sta bulletsBuffer, x                        ; could kill 1/2 another bullet if side by side, not serious
    inx 
    sta bulletsBuffer, x
    inx 
    sta bulletsBuffer, x
    dex                                         ; restore the x value

next:
    inc zScreenCol
    inc zEnemyCol
    inx 
    cpx zaEnd 
    bne loop 

    lda #0                                      ; stomp the next 2 slots
    sta bulletsBuffer, x                        ; so that when this moves there
    inx                                         ; are no "accidental" bullets from the wrap-around
    sta bulletsBuffer, x
    clc 
    rts 

.endproc

;-----------------------------------------------------------------------------
.proc drawExplosions

    zaExplosionType   = zTemp1
    zaDrawWorldHeight = zTemp2                  ; for drawSprite
    zaDrawSprWidth    = zTemp3
    zaDrawSprHeight   = zTemp5

    lda #0
    sta zScreenCol

    ldx bufferDraw                              ; make enemyBuffer relative to screen col 0

loop:
    lda explosionBuffer, x 
    beq next
    stx zEnemyCol

    sta zaExplosionType
    and #%11111000                              ; mask out bottom bits (frame counter)
    sta zaDrawWorldHeight

    lda #EXPLOSION_HEIGHT
    sta zaDrawSprHeight

    sec                                         ; clip for the far right
    lda #XSIZE                                  ; start with the edge that's always bigger
    sbc zScreenCol                              ; take away the column
    sbc #EXPLOSION_WIDTH                        ; carry still set, take away the sprite width
    bcs :+                                      ; if carry still set, the sprite fits
    adc #EXPLOSION_WIDTH                        ; Needs clip, add sprite to negative to get clipped length
    .byte $2c                                   ; skip reloading the width using bit $nnnn
:
    lda #EXPLOSION_WIDTH                        ; load the width that fits
    sta zaDrawSprWidth                          ; save as the render width
    clc 
    lda zaExplosionType
    and #%00000011                              ; up to 4 frames (0-3)
    tax 

    lda explosionColL, x
    sta drawSprite::offset + 1
    lda explosionColH, x 
    sta drawSprite::offset + 2

    jsr drawSprite
    ldx zEnemyCol

next:
    inx 
    cpx bufferInsert
    clc 
    beq done 
    inc zScreenCol
    bne loop

done:
    lda #0                                      ; collisions on explosions ignored
    sta zCollision                              ; but it must be left clean
    rts 

.endproc

;-----------------------------------------------------------------------------
; Iterate over the enemies on screen and get them drawn to the back buffer
; Parameter - zCollision must be = 0 when called
.proc drawEnemies

    zaEnemyType    = zTemp1                     ; parameter to the specific enemy draw call
    zaDrawSprWidth = zTemp3

    lda terrainOrigin                           ; will always be 0 since this isn't called till screen fully scrolled in
    sta zScreenCol                              ; start drawing here on-screen

    ldx bufferDraw                              ; make enemyBuffer relative to screen col 0
    stx zEnemyCol                               ; start here processing enemies

loop:
    lda enemyBuffer, x                          ; check this column for a (partial) enemy (just a strip)
    beq continue                                ; skip non-enemy columns

    sta zaEnemyType                             ; save the flags
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
    beq continue
    lda zCollision                              ; see if this enemy is in collision (for missiles with terrain)
    beq continue
    lda #1
    sta zaDrawSprWidth
    jsr gameKillEnemy

continue:
    ldx zEnemyCol 
    cpx bufferInsert 
    beq done
    inx 
    stx zEnemyCol 
    inc zScreenCol
    bne loop

done:
    rts 

.endproc
