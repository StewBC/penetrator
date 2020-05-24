;-----------------------------------------------------------------------------
; input.inc
; Part of penetrator, the zx spectrum game, made for commander x16
;
; Stefan Wessels, 2019
; This is free and unencumbered software released into the public domain.
;-----------------------------------------------------------------------------
.segment "CODE"

;-----------------------------------------------------------------------------
; Reads the joystick and moves the player.
; It's a little odd because it mimics what the original game seems to do
; It splits the vertical movement over 2 frames, but moves horizontal
; every second frame - to match the rate the world moves
.proc inputGame

    zaRawInput = zTemp1
    zaRawEor   = zTemp2

    lda pause                                   ; see if the game is paused
    beq noPause                                 ; if not - process joystick
    jmp chkPause                                ; when paused - only process the pause key

noPause:
    jsr JOYGET
	sta zaRawInput                              ; save the input
    eor #$ff                                    ; invert the bits
    sta zaRawEor                                ; save this state too

    lda moveVert                                ; see if a vertical move is in progress
    bne preLeft                                 ; if yes, don't look for vertical input
    
    lda zaRawInput                              ; no vertical move so process vertical joystick

up:
    bit Bit4Mask                                ; set when moving up
    bne down
    lda #%00000010                              ; put 2 into the moveVert variable
    sta moveVert                                ; if wanting to move vertically
    bne preLeft

down:
    bit Bit3Mask                                ; ser for joystick down
    bne preLeft
    lda #%10000010                              ; set 2 and also set the high bit, in the moveVert variable
    sta moveVert

preLeft:
    lda moveHorz                                ; if horizontal movement is in progress
    bne vMove                                   ; ignore the joystick inputs
    
    lda zaRawInput                              ; no horizontal movement so process horiz joystick

left:
	bit Bit2Mask                                ; left sets this bit
    bne right                                   ; not set see if right is set
    ldx playerShipX                             ; the ship should move left
    dex                                         ; move left one column
    bmi vMove                                   ; if off-screen to the left, ignore
    stx playerShipX                             ; save the movement
    lda #%00000010                              ; set 2 in the horizontal movement
    sta moveHorz
    bne vMove                                   ; JuMP over right

right:
    bit Bit1Mask                                ; bit set when right joystick active
    bne vMove                                   ; if nothing, go process player movement

    ldx playerShipX                             ; get the ship position
    inx                                         ; move one column to the right
    cpx #(((XSIZE/3)*2) - SHIP_WIDTH - 1)       ; limit to two-thirds toward the right
    bcs vMove                                   ; if over limit, ignore
    stx playerShipX                             ; save movement
    lda #%10000010                              ; mark as right (high bit) and value of 2
    sta moveHorz                                ; save in moveHorz

vMove:
    lda moveVert                                ; see if the player ship needs to move vertically
    beq preBomb                                 ; if not, check horizontal
    bit Bit8Mask                                ; if bit 8 set movement is down
    bne moveDown
    dec moveVert                                ; up movement - dec the vert variable
    lda playerShipY                             ; and move the ship up 2 rows
    sec 
    sbc #2
    cmp #(SHIP_HEIGHT+WORLD_START)              ; limit at the top
    bcc preBomb                                 ; if too high, just ignore saving the move
    sta playerShipY                             ; save the new position
    bcs preBomb                                 ; up, so skip down and check horizontal

moveDown:
    and #%00000011                              ; mask off the high bit
    sec                                         ; and decrement
    sbc #1
    beq :+                                      ; if zero then done
    ora #%10000000                              ; not zero so remember this was down
:
    sta moveVert                                ; save the vertical counter
    lda playerShipY                             ; move the ship 2 rows down
    clc 
    adc #2
    cmp #(WORLD_END+1)                          ; limit at the bottom
    bcs preBomb                                 ; skip saving the new position if too low
    sta playerShipY                             ; new position okay so save it

preBomb:
    lda zaRawInput

bomb:
	bit Bit8Mask                                ; Button_A = bomb
    bne fire
    lda lastInput                               ; debounce the key for single shot
    and zaRawEor 
    and Bit8Mask
    beq nobomb                                  ; bomb key not down
    lda playerShipY                             ; bomb requested but can't
    cmp #(WORLD_END-BOMB_HEIGHT)                ; drop it when there's no room
    bcs nobomb                                  ; before the world end (else it draws out of bounds)
    ldx #NUM_BOMBS-1                            ; iterate over all bombs
:
    lda bombY, x
    beq drop                                    ; find one that's available
    dex 
    bpl :-
    bmi nobomb                                  ; none available
drop:
    lda playerShipX                             ; bomb is relative to player
    clc 
    adc #2
    sta bombX, x
    lda playerShipY
    adc #6
    sta bombY, x
    lda #BOMB_FRWRD_FRMS                        ; set it to fly forward
    sta bombDir, x
nobomb:
    lda zaRawInput

fire:
	bit Bit7Mask                                ; Button_B = fire
    bne hMove
    lda moveHorz                                ; see if the player is moving right
    bit Bit8Mask                                ; bit 8 set when moving right
    bne hMove                                   ; if moving, then can't fire
    lda lastInput                               ; debounce the key for single shot
    and zaRawEor 
    and Bit7Mask
    beq hMove
    lda playerShipX                             ; bullets start relative to ship
    clc 
    adc #4
    adc bulletIndex
    tax 
    lda playerShipY
    sec 
    sbc #4
    sta bulletsBuffer, x                        ; put height into 3 columns
    inx 
    sta bulletsBuffer, x

hMove:
    lda moveHorz                                ; do after fire so the flag doesn't clear a frame too soon
    beq joyDone
    bit Bit8Mask
    bne mright
    dec moveHorz
    bpl joyDone                                 ; JuMP

mright:
    and #%00000011
    sec 
    sbc #1
    beq :+
    ora #%10000000
:
    sta moveHorz

joyDone:
    lda zaRawInput                              ; remember the key-state for next time
    sta lastInput                               ; so that fire and bombs can be debounced

chkPause:
    jsr GETIN                                   ; check for a key
    cmp #'p'                                    ; check for the pause key
    bne :+
    lda pause                                   ; toggle the pause state
    eor #1
    sta pause

:
    clc                                         ; keep carry clear between routines
    rts 

.endproc

;-----------------------------------------------------------------------------
.proc inputEdit

    rawInput  = tempBlock + 4
    rawEor    = tempBlock + 5
    brushType = tempBlock + 6

    lda #0                                      ; Only first Joystick
    jsr JOYGET
    sta rawInput                                ; save the input state
    eor #$ff                                    ; invert the bits so 1 means button down
    sta rawEor                                  ; save the inverted bits
    bit Bit6Mask                                ; see if select button is held
    bne Button_B                                ; if it is down, key processing done
    and lastInput                               ; otherwise debounce the keys
    sta rawEor                                  ; and save this state as the key state

 Button_B:
 	bit Bit7Mask                               ; Button_B
    beq Button_A
    lda brushType
    bne radar
    ora #1                                      ; when pressed, move right as well
    sta rawEor
    jsr editSetTerrainBottom
    jmp :+

radar:
    jsr editSetRadar
:
    lda rawEor                                  ; no horizontal movement so process horiz joystick

Button_A:
	bit Bit8Mask                                ; Button_A
    beq up
    lda brushType
    bne missile
    ora #1
    sta rawEor
    jsr editSetTerrainTop
    jmp :+

missile:
    jsr editSetMissile
:
    lda rawEor                                  ; no horizontal movement so process horiz joystick

up:
    bit Bit4Mask                                ; set when moving up
    beq down
    ldx playerShipY 
    cpx #9
    bcc :+
    dex 
    stx playerShipY 
:
    lda rawEor                                  ; no horizontal movement so process horiz joystick

down:
    bit Bit3Mask                                ; ser for joystick down
    beq left
    ldx playerShipY 
    cpx #WORLD_END
    bcs :+
    inx 
    stx playerShipY 
:
    lda rawEor                                  ; no horizontal movement so process horiz joystick

left:
	bit Bit2Mask                                ; left sets this bit
    beq right                                   ; not set see if right is set
    jsr editGameWorldLeft
    lda rawEor                                  ; no horizontal movement so process horiz joystick

right:
    bit Bit1Mask                                ; bit set when right joystick active
    beq Button_Start
    jsr editGameWorldRight
    lda rawEor                                  ; no horizontal movement so process horiz joystick

Button_Start:
    lda rawInput                                ; This is a toggle so never auto-repeat
    eor #$ff                                    ; start from source
    and lastInput                               ; and debounce
    bit Bit5Mask                                ; test if Start button down
    beq joyDone
    lda brushType                               ; if down, toggle the brush type between terrain and enemies
    eor #1
    sta brushType 
    jsr uiShowEditLabels                        ; update the HUD

joyDone:
    lda rawInput                                ; preserve this input for next frame as last input
    sta lastInput                               ; so that fire and bombs can be debounced

    jsr GETIN
    clc                                         ; keep carry clear between routines
    rts 

.endproc

;-----------------------------------------------------------------------------
; Checks for a user input on keyboard or joystick
; upon exit - acc 0 means nothing, <> 0 means user input detected
.proc inputCheckForInput

    rawInput = zTemp1                           ; internal

    jsr GETIN                                   ; read the keyboard
    bne done                                    ; if there's a key then done here
    jsr JOYGET                                  ; check the joystick
    sta rawInput                                ; keep the raw bits
    eor #$ff                                    ; invert
    and lastInput                               ; debounce
    pha                                         ; save this
    lda rawInput                                ; back up the raw to the last
    sta lastInput
    pla                                         ; and get back the debounced bits
    beq done
    ldx #1
:
    lsr 
    bcs :+
    inx 
    bne :-
:
    txa 
done:
    rts                                         ; upon return 0 means no interaction, anything else is a user input

.endproc
