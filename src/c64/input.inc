;-----------------------------------------------------------------------------
; input.inc
; Part of penetrator, the zx spectrum game, made for Commodore C64
;
; Stefan Wessels, 2019, 2023
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "CODE"

;-----------------------------------------------------------------------------
.proc inputReadJoystick

    lda #%11100000                              ; Set all bits but fire and direction
    ora CIA1_PRA                                ; read the stick
    bit Bit5Mask                                ; check for fire
    bne :+                                      ; not fire - go on
    ora #%00010000                              ; Turn fire off
    and #%00111111                              ; turn both game fire and bomb on
    sta rawInput                                ; save the input
:   sta rawInput                                ; save the input

    rts

.endproc

;-----------------------------------------------------------------------------
.proc inputReadGameKeys

    key     = tempBlock + 22

    lda #$A1
    sta CIA1_PRA
    lda #$FF
    sta CIA1_PRB
    lda CIA1_PRB

    sta key
    and #$2C                                    ; 4680 home   ADGJ;    SFHK=
    cmp #$2C
    beq :+
    lda rawInput
    and #<(~KEY_UP)
    sta rawInput
:   lda key
    and #$91                                    ; [3579£   ZCBM rshift   lshift XVN/
    cmp #$91
    beq :+
    lda rawInput
    and  #<(~KEY_DOWN)
    sta rawInput
:   lda key
    bit Bit2Mask                                ; WRYI*
    bne :+
    lda rawInput
    and #<(~KEY_RIGHT)
    sta rawInput
    lda key
:   bit Bit7Mask                                ; ETUO^
    bne :+
    lda rawInput
    and #<(~KEY_LEFT)
    sta rawInput
    lda key

:   lda #$DF                                    ; second scan
    sta CIA1_PRA
    lda #$FF
    sta CIA1_PRB
    lda CIA1_PRB
    
    sta key
    and #$91                                    ; +.,
    cmp #$91
    beq :+
    lda rawInput
    and #<(~KEY_DOWN)
    sta rawInput
:   lda key
    and #$0A                                    ; p-
    cmp #$0A
    beq :+
    lda rawInput
    and #<(~KEY_RIGHT)
    sta rawInput
:   lda key
    and #$24                                    ; l:
    cmp #$24
    beq :+
    lda rawInput
    and #<(~KEY_UP)
    sta rawInput
:   lda key
    bit Bit7Mask                                ; @
    bne :+
    lda rawInput
    and #<(~KEY_FIRE)
    sta rawInput

:   lda #$7F                                    ; second scan
    sta CIA1_PRA
    lda #$FF
    sta CIA1_PRB
    lda CIA1_PRB
    sta key

    bit Bit2Mask
    bit Bit3Mask                                ; CONTROL
    bne :+
    lda rawInput
    and #<(~KEY_FIRE)
    sta rawInput
    lda key
:   bit Bit5Mask                                ; SPACE
    bne :+
    lda rawInput
    and #<(~KEY_BOMB)
    sta rawInput
    lda key
:   bit Bit6Mask                                ; COMMODORE
    bne :+
    lda rawInput
    and #<(~KEY_START)
    sta rawInput
    lda key
:   bit Bit7Mask                                ; Q
    bne :+
    lda rawInput
    and #<(~KEY_LEFT)
    sta rawInput
    lda key
:   bit Bit8Mask                                ; RUN/STOP
    bne :+
    lda rawInput
    and #<(~KEY_SELECT)
    sta rawInput

:   lda #$FE                                    ; third scan
    sta CIA1_PRA
    lda #$FF
    sta CIA1_PRB
    lda CIA1_PRB
    sta key
    bit Bit2Mask                                ; RETURN
    bne :+
    lda rawInput
    and #<(~KEY_START)
    sta rawInput

:   lda rawInput
    rts

.endproc

;-----------------------------------------------------------------------------
; Reads the joystick and moves the player.
.proc inputGame

    lda fireCoolDown
    beq :+
    dec fireCoolDown
:
    jsr inputReadJoystick
    jsr inputReadGameKeys

    eor #$ff                                    ; invert the bits
    sta rawEOR                                  ; save this state too

    lda rawInput                                ; no vertical move so process vertical joystick

up:
    bit Bit1Mask                                ; set when moving up
    bne down
    lda playerShipY                             ; and move the ship up 3 rows
    sec
    sbc #3
    cmp #(SHIP_HEIGHT+WORLD_START)              ; limit at the top
    bcc preLeft                                 ; if too high, just ignore saving the move
    sta playerShipY                             ; save the new position
    bcs preLeft                                 ; up, so skip down and check horizontal

down:
    bit Bit2Mask                                ; ser for joystick down
    bne left
    lda playerShipY                             ; move the ship 3 rows down
    clc
    adc #3
    cmp #(WORLD_END+1)                          ; limit at the bottom
    bcs preBomb                                 ; skip saving the new position if too low
    sta playerShipY                             ; new position okay so save it

preLeft:
    lda rawInput                                ; no horizontal movement so process horiz joystick

left:
    bit Bit3Mask                                ; left sets this bit
    bne right                                   ; not set see if right is set
    ldx playerShipX                             ; the ship should move left
    dex                                         ; move left one column
    bmi preBomb                                 ; if off-screen to the left, ignore
    stx playerShipX                             ; save the movement
    lda audioFrame
    ora #AUDIO_MOTOR_REW
    sta audioFrame
    bne preBomb

right:
    bit Bit4Mask                                ; bit set when right joystick active
    bne bomb                                    ; if nothing, go process player movement

    ldx playerShipX                             ; get the ship position
    inx                                         ; move one column to the right
    cpx #(((PENXSIZE/3)*2) - SHIP_WIDTH - 1)    ; limit to two-thirds toward the right
    bcs preBomb                                 ; if over limit, ignore
    stx playerShipX                             ; save movement
    lda audioFrame
    ora #AUDIO_MOTOR_FWD
    sta audioFrame

preBomb:
    lda rawInput

bomb:
    bit Bit8Mask                                ; Button_A = bomb
    bne fire
    lda lastInput                               ; debounce the key for single shot
    and rawEOR
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
    lda audioFrame
    ora #AUDIO_BOMB_DROP
    sta audioFrame
nobomb:
    lda rawInput

fire:
    bit Bit7Mask                                ; Button_B = fire
    bne pauseKey
    lda fireCoolDown
    bne pauseKey
    lda lastInput                               ; debounce the key for single shot
    and rawEOR
    and Bit7Mask
    beq pauseKey
    clc
    lda playerShipX                             ; bullets start relative to ship
    adc #4                                      ; 4 columns for in front of ship
    adc bulletIndex                             ; and relative to the buffer start
    tax
    lda playerShipY
    sec
    sbc #4
    sta bulletsBuffer, x                        ; put height
    lda #4
    sta fireCoolDown
    lda audioFrame
    ora #AUDIO_FIRE
    sta audioFrame

pauseKey:
    lda lastInput
    and rawEOR
    bit Bit5Mask
    beq joyDone
    lda #1
    sta pause

joyDone:
    lda rawInput                                ; remember the key-state for next time
    sta lastInput                               ; so that fire and bombs can be debounced

    clc                                         ; keep carry clear between routines
    rts

.endproc

;-----------------------------------------------------------------------------
.proc inputEdit

    brushType = tempBlock + 18

    jsr inputReadJoystick
    jsr inputReadGameKeys

    lda rawInput
    eor #$ff                                    ; invert the bits so 1 means button down
    sta rawEOR                                  ; save the inverted bits
    bit Bit6Mask                                ; see if select button is held
    bne Button_B                                ; if it is down, key processing done
    and lastInput                               ; otherwise debounce the keys
    sta rawEOR                                  ; and save this state as the key state

 Button_B:
    bit Bit7Mask                                ; Button_B
    beq Button_A
    lda #AUDIO_UI_TICK                          ; make a sound
    sta audioFrame
    jsr audioStart
    lda brushType
    bne radar
    ora #KEY_RIGHT                              ; when pressed, move right as well
    sta rawEOR
    jsr editSetTerrainBottom
    jmp :+

radar:
    jsr editSetRadar
:
    lda rawEOR                                  ; no horizontal movement so process horiz joystick

Button_A:
    bit Bit8Mask                                ; Button_A
    beq up
    lda #AUDIO_UI_TICK                          ; make a sound
    sta audioFrame
    jsr audioStart
    lda brushType
    bne missile
    ora #KEY_RIGHT
    sta rawEOR
    jsr editSetTerrainTop
    jmp :+

missile:
    jsr editSetMissile
:
    lda rawEOR                                  ; no horizontal movement so process horiz joystick

up:
    bit Bit1Mask                                ; set when moving up
    beq down
    ldx playerShipY
    cpx #9
    bcc :+
    dex
    stx playerShipY
:
    lda rawEOR                                  ; no horizontal movement so process horiz joystick

down:
    bit Bit2Mask                                ; ser for joystick down
    beq left
    ldx playerShipY
    cpx #WORLD_END
    bcs :+
    inx
    stx playerShipY
:
    lda rawEOR                                  ; no horizontal movement so process horiz joystick

left:
    bit Bit3Mask                                ; left sets this bit
    beq right                                   ; not set see if right is set
    jsr editGameWorldLeft
    lda rawEOR                                  ; no horizontal movement so process horiz joystick

right:
    bit Bit4Mask                                ; bit set when right joystick active
    beq Button_Start
    jsr editGameWorldRight

Button_Start:
    lda rawInput                                ; This is a toggle so never auto-repeat
    eor #$ff                                    ; start from source
    and lastInput                               ; and debounce
    bit Bit5Mask                                ; test if Start button down
    beq joyDone
    lda #AUDIO_UI_TICK                          ; make a sound
    sta audioFrame
    jsr audioStart
    lda brushType                               ; if down, toggle the brush type between terrain and enemies
    eor #1
    sta brushType
    jsr uiShowEditLabels                        ; update the HUD

joyDone:
    lda rawInput                                ; preserve this input for next frame as last input
    sta lastInput                               ; so that fire and bombs can be debounced
    lda rawEOR                                  ; if there were no "Joystick" commands
    beq :+                                      ; Just check for regular keys
    rts
:
    jmp GETIN

.endproc

;-----------------------------------------------------------------------------
; Checks for a user input on keyboard or joystick
; upon exit - acc 0 means nothing, <> 0 means user input detected
.proc inputCheckForInput

    jsr GETIN
    bne key

    jsr inputReadJoystick
    eor #$ff                                    ; invert
    and lastInput                               ; debounce
    pha                                         ; save
    lda rawInput                                ; update lastinput to be this input
    sta lastInput
    pla                                         ; restore debounced in a
    beq done                                    ; nothing - then done
    bit Bit8765Mask                             ; Special keys
    beq check                                   ; no? then make direction an input index
    lda #KEY_UP                                 ; Special keys = UP = 1 = 1 Player game

check:                                          ; a is never 0 here
    ldx #1
:
    lsr
    bcs :+
    inx
    bne :-
:
    txa

key:
    pha                                         ; Save the "key"
    lda #AUDIO_UI_TICK                          ; make a sound
    sta audioFrame
    jsr audioStart
    pla                                         ; restore the "key"
done:
    rts                                         ; upon return 0 means no interaction, anything else is a user input

.endproc
