;-----------------------------------------------------------------------------
; variables.inc
; Part of penetrator, the zx spectrum game, made for commander x16
;
; Stefan Wessels, 2019
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "DATA"

;-----------------------------------------------------------------------------
; Game variables
numPlayers:         .res 1                      ; [0|1] where 0 is a 1 player game, 1 = 2 player game
activePlayer:       .res 1                      ; 0 for player 1, 1 for player 2
gameMode:           .res 1                      ; 0 for gameplay, 1 for trainer, 2 for edit

; Player specific variables
rsStart:                                        ; runtime stats "struct".  lives MUST be 1st
lives:              .res 1                      ; Chances the player gets (decimal mode), indexed by activePlayer
score:              .res 3                      ; activePlayer's score is copied here for gameplay
stage:              .res 1                      ; offset to stages in worldDataStart - needed for reset
direction:          .res 1                      ; 0 = right, 1 = left (fly reverse through level)
makeMonster:        .res NUM_STAGES             ; 1 in stage offset lookup turns missiles into monsters
rsEnd:

playerStats:        .res ((rsEnd-rsStart) * 2)  ; 2 copies of stats, for p1 and p2 is 2p game

highScores:
highScore1:         .res 3
highScore2:         .res 3
highScore3:         .res 3
highScore4:         .res 3
highScore5:         .res 3
highScoresEnd:

; per "run" variables
playerShipX:        .res 1                      ; x position in columns
playerShipY:        .res 1                      ; y position in rows
terrainOrigin:      .res 1                      ; from 0 to XSize - where to start world draw on screen
stopScrolling:      .res 1                      ; 1 - world will not move (for death)
playerDead:         .res 1                      ; 0 - gamePlay flow, > 0 players dead
monsterCnt:         .res 1                      ; skip # missiles before turning one into a monster
inFlight:           .res 2                      ; count launched missiles for launch control
victory:            .res 1                      ; 0 = not done, 1 = hit the nuke so done with run
nextStage:          .res 1                      ; -1 nothing, 0 at next stage, >0 count down
bufferInsert:       .res 1                      ; index where data gets added to buffers (right hand of screen)
bufferDraw:         .res 1                      ; index that corresponds to draw start (usually col 0 of screen)
bulletIndex:        .res 1                      ; like bufferDraw but bullets "travel" in opposite direction
dangerTickCount:    .res 1                      ; how often a dot is added to the danger line, when the world moves
dangerTickidx:      .res 1                      ; the index into the text that holds the danger line of dots
moveHorz:           .res 1                      ; keeps track of horizontal movement - only moves every 2nd frame
moveVert:           .res 1                      ; keeps track of vertical movement - moves 4 rows but over 2 frames

; per "run" buffers
bombX:              .res NUM_BOMBS              ; 2 bombs allowed, their x values
bombY:              .res NUM_BOMBS              ; Y values for 2 bombs (0=available)
bombDir:            .res NUM_BOMBS              ; direction of travel (and thus sprite)
worldTBuffer:       .res BUFLENGTH              ; holds the world bottom height
worldBBuffer:       .res BUFLENGTH              ; holds the world top height
enemyBuffer:        .res BUFLENGTH              ; holds enemy sprite draw data
enemyHgtBuffer:     .res BUFLENGTH              ; holds enemy sprite draw height data
bulletsBuffer:      .res BUFLENGTH              ; holds the bullet heights (0=no bullet)
explosionBuffer:    .res BUFLENGTH              ; holds the explosion heights (0=no explosion)

; helper variables
updateHUD:          .res 1                      ; 0 - don't draw, 1+ - clean and redraw
flipFlop:           .res 1                      ; counter to advance explosion frames
backLayer:          .res 1                      ; [0|1] - Layer not shown to user *=(to be drawn to)
enemyHit:           .res 1                      ; the flags of the enemy destroyed in gameKillEnemy
enemyHitType:       .res 1                      ; 0 = nuke, 1 = missile, 2 = monster, 3 = radar, $ff - nothing
lastInput:          .res 1                      ; holds the value of the prev joystick frame
pause:              .res 1                      ; <> 0 when the game is paused

; shared temporary variables
tempBlock:          .res 19                     ; used by different routines that need local storage