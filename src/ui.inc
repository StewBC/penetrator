;-----------------------------------------------------------------------------
; ui.inc
; Part of penetrator, the zx spectrum game, made for commander x16
;
; Stefan Wessels, 2019
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "CODE"


;-----------------------------------------------------------------------------
.proc uiTitleScreen 

    lda #VSCALE_UI                              ; make the screen taller (fit more text and font looks nicer)
    sta VERA::DISP::VSCALE

    lda #0
    sta NDX                                     ; flush the keyboard buffer before uiWriteName
    sta lastInput

    lda #UI_PALETTE
    ldy #8
    jsr drawSetPalette

    jsr drawClearScreen
    jsr uiWriteName                             ; also looks for a key press

    jsr uiShowHighScores

    print textPhilip   , #(2*05), #(8*21), #$FF
    print textCopyright, #(2*04), #(8*22), #$FF
    print textCommander, #(2*08), #(8*24), #$AA
    print textStefan   , #(2*08), #(8*25), #$55
    print textSource   , #(2*12), #(8*27), #$AA
    print textGitHub   , #(2*02), #(8*28), #$55

    jsr drawPresent

    lda #0                                      ; set all keys to down for joystick
    sta NDX
    sta lastInput                               ; debounce the last key if it was a joy button
:
    jsr inputCheckForInput                      ; wait for user interaction
    beq :-

    rts

.endproc 

;-----------------------------------------------------------------------------
.proc uiShowHighScores

    zaStrL     = zTemp1
    zaStrH     = zTemp2
    zaForce    = zTemp3
    zaFontMask = zTemp3
    textX = tempBlock + 0
    textY = tempBlock + 1
    scorePtrL   = tempBlock + 4                 ; 2 + 3 used by textOut
    scorePtrH   = tempBlock + 5
    scoreIdx    = tempBlock + 6
    scoreShown  = tempBlock + 7

    lda #<highScores                            ; set up a pointer to the scores
    sta scorePtrL
    lda #>highScores
    sta scorePtrH
    lda #0                                      ; and init two counters
    sta scoreIdx                                ; which high-score is being processed
    sta scoreShown                              ; were any high-scores printed

loop: 
    ldy #3                                      ; 3 bytes to a score
    ldx #0                                      ; don't force a number
    lda scorePtrL                               ; get the score to convert
    sta zaStrL
    lda scorePtrH
    sta zaStrH
    jsr textBCDtoSZ                             ; convert it
    dex                                         ; step back from the null-terminator
    lda textNumber, x                           ; get the last character out
    cmp #' '                                    ; was it a space
    bne show                                    ; no - there was a score so show it
    beq heading                                 ; as soon as there's no score there won't be any more

next:
    inc scoreIdx                                ; go to next score
    lda scoreIdx
    cmp #5                                      ; all 5 scores shown?
    bcc cont                                    ; if not, carry on processing

heading: 
    lda scoreShown                              ; were any score printed
    beq done                                    ; if not, nothing more
    print textHighScores, #(2*15), #(8*0), #$ff ; Show the scores' heading

done:
    rts 

cont:
    lda scorePtrL                               ; advance the score ptr to the next 3 bytes
    adc #3
    sta scorePtrL
    bcc loop 
    inc scorePtrH
    bne loop                                    ; JuMP

show:                                           ; a high-score was set, so show it
    inc scoreShown
    inx                                         ; back to the null terminator
    lda #'0'                                    ; Show score as 10x the actual score
    sta textNumber, x                           ; append the 0 to the buffer
    ldx scoreIdx                                ; get the index of which score
    lda #<textNumber                            ; print the converted score text
    sta zaStrL
    lda #>textNumber
    sta zaStrH 
    lda #$ff
    sta zaFontMask
    lda scorePosX, x                            ; get the X position of where
    sta textX
    lda scoreTextPosY, x                        ; and the Y position
    sta textY
    jsr textOut                                 ; now render the text

    ldx scoreIdx                                ; get the score index again
    lda scoreTextOffset, x                      ; and figure out the start of the name text for this score
    clc 
    adc #<textHS                                ; offset from where the names are stored
    sta zaStrL
    lda #0
    adc #>textHS
    sta zaStrH
    lda #$ff                                    ; render in all 1's font
    sta zaFontMask
    lda scoreTextPosX, x                        ; get the x position
    sta textX 
    lda scoreTextPosY, x                        ; and the y position
    sta textY 
    jsr textOut                                 ; and render the text

    jmp next                                    ; and go to the next score

.endproc

;-----------------------------------------------------------------------------
; Uses line drawing to spell out the Penetrator logo
.proc uiWriteName

    x0      = tempBlock + 0                     ; local variables
    x1      = tempBlock + 1
    y0      = tempBlock + 2
    y1      = tempBlock + 3
    dx      = tempBlock + 4
    dy      = tempBlock + 5
    sx      = tempBlock + 6
    sy      = tempBlock + 7
    dyNeg   = tempBlock + 8
    err     = tempBlock + 9
    err2    = tempBlock + 10
    index   = tempBlock + 11
    remain  = tempBlock + 12
    skip    = tempBlock + 13
    width   = tempBlock + 14
    height  = tempBlock + 15
    plotCol = tempBlock + 16

    lda #((dataLogoLinesEnd - dataLogoLines) / 4)
    sta remain
    
    ldx #0
    stx index                                   ; current line
    stx skip                                    ; impatient user

    lda #1                                      ; set up the plot
    sta width

    lda #1
    sta height

    lda #$ff                                    ; draw in the 4th color
    sta plotCol

loop:
    dec remain                                  ; iterate over all lines
    bpl :+
    rts
: 
    ldx index 
	
	lda dataLogoLines,x                         ; Load x0,y0 x1,y1 into variables
	sta x0
	inx 
	lda dataLogoLines,x
	sta y0
	inx 
	lda dataLogoLines,x
	sta x1
	inx 
	lda dataLogoLines,x
	sta y1
	inx 
	
	stx index                                   ; update the index to next line params

	
	ldy #2                                      ; dx = abs(x1-x0) - sx=2
	lda x1 
	sec 
	sbc x0 
	bcs :+                                      ; x1 >= x0
	eor #$ff                                    ; abs
	adc #1
	ldy #0                                      ;sx=0

:
	sta dx 
	dey                                         ;sx=-1|1
	sty sx 

	
	ldy #2                                      ; dy = abs(y1-y0) - sy=2
	lda y1 
	sec 
	sbc y0 
	bcs :+                                      ; y1 >= y0
	eor #$ff                                    ; abs
	adc #1
	ldy #0                                      ;sy=0
 	sec 
:
	sta dy 
 	lda #0
 	sbc dy 
 	sta dyNeg                                  ; = -dy
	dey                                         ; sy=-1|1
	sty sy 

	
	lda dx                                      ; err = dx-dy
	sec 
	sbc dy 
	sta err 

plot:
    ldx x0
    ldy y0 
	jsr drawPlotXY                              ; plot a "pixel" at x y

    jsr drawPresent                             ; present this plot

    ldx x0                                      ; do for the 2nd buffer the same
    ldy y0 
	jsr drawPlotXY 

    lda skip                                    ; if key/button pressed - fast draw logo
    bne :+
    jsr inputCheckForInput                      ; check for user interaction
    sta skip 
    bne :+
    wait #$02

:
	lda x0                                      ; if(x0=x1 && y0=y1) done
	cmp x1 
	bne :+ 
	lda y0 
	cmp y1 
	bne :+ 
	jmp loop 

:
	lda err                                     ; e2 = err << 1
	asl 
	sta err2 

	
	lda dyNeg                                   ; if(e2 > -dy)
	sec 
	sbc err2 
	bpl :+ 

	
 	lda err                                    ; err = err - dy
	sec 
	sbc dy 
	sta err 
	
	lda x0                                      ; x0 = x0 + sx
	clc 
	adc sx 
	sta x0 

:
	lda dx                                      ; if(e2 <  dx)
 	sec 
 	sbc err2 
 	bpl :+ 
 	jmp plot 

:
	lda err                                     ; err = err + dx
	clc 
	adc dx 
	sta err 
	
	lda y0                                      ; y0 = y0 + sy
	clc 
	adc sy 
	sta y0 
	jmp plot 

.endproc 

;-----------------------------------------------------------------------------
; Shows the main menu and waits for user choice
.proc uiMainMenu

    timeout = tempBlock + 0

    jsr drawClearScreen

    lda #VSCALE_UI                              ; make the screen bigger for UI - the font looks better
    sta VERA::DISP::VSCALE

    print textInstructions, #(2*14), #(8*04), #$FF
    print textPress       , #(2*17), #(8*08), #$FF
    print textUnderline   , #(2*17), #(8*09), #$FF
    print textOneTwo      , #(2*04), #(8*11), #$FF
    print textTrain       , #(2*04), #(8*12), #$FF
    print textEdit        , #(2*06), #(8*13), #$FF
    print textLoad        , #(2*05), #(8*14), #$FF
    print textSirens      , #(2*09), #(8*15), #$55

    print textJoyhead     , #(2*14), #(8*19), #$FF
    print textJoyheadLine , #(2*14), #(8*20), #$FF
    print textJoy1        , #(2*08), #(8*22), #$FF
    print textJoy2        , #(2*13), #(8*23), #$FF
    print textJoy3        , #(2*11), #(8*24), #$FF

    print textNotDone     , #(2*12), #(8*28), #$55

    jsr drawPresent

    lda #GAME_MODE_PLAY                         ; assume the player will play (play is 0)
    sta gameMode 
    sta stage                                   ; and set the stage to 0
    sta lastInput

loop:
    lda #$07
    sta timeout
    lda #(optionsEnd-options)                   ; how many options on this menu
    ldx #<options                               ; x - lo options "string"
    ldy #>options                               ; y - hi options "string"
    jsr uiHandleOptions                         ; on return, x is the option selected (0 based)

    cpx #(optionsEnd-options) + 1
    bne :+
    rts 

:
    cpx #2                                      ; 0 & 1 for 1/2 player game
    bcs train                                   ; greater means another option

    stx numPlayers                              ; x happens to be the value for numPlayers
    jmp gamePlay                                ; go gameplay and return to title screen

train:
    bne edit                                    ; still on the cpx #2 here
    jmp uiTrainerMode                           ; 2 means train, and then return to title screen

edit:
    cpx #3
    bne load
    jsr editLoop                                ; 3 means edit
    jmp uiMainMenu                              ; and go to main menu, not title

load:
    cpx #4
    bne sirens
    lda #1                                      ; 1 means load
    jsr uiFileLoadSave                          ; call the code to do file name and load
    jmp uiMainMenu

sirens:
    jmp loop                                    ; siren code instead of this


options: .byte "12tels"
optionsEnd:

.endproc

;-----------------------------------------------------------------------------
; Shows the trainer menu asking for a stage to train (1-4).  Allows
; backspace to go back to main menu
.proc uiTrainerMode

    timeout = tempBlock + 0

    jsr drawClearScreen

    print textTrainingMode, #(2*15), #(8*04), #$FF
    print textPressStage  , #(2*06), #(8*12), #$FF
    print textOneToFour   , #(2*12), #(8*13), #$FF
    print textBackup      , #(2*04), #(8*23), #$FF

    jsr drawPresent

    lda #GAME_MODE_TRAIN
    sta gameMode

    lda #$07
    sta timeout
    lda #(optionsEnd-options)
    ldx #<options 
    ldy #>options 
    jsr uiHandleOptions

    cpx #4                                      ; backspace option, or timeout
    bcc stageSel
    cpx #(optionsEnd-options)+1                 ; time out goes to title, not main menu like backup
    bne :+
    rts 
:
    jmp uiMainMenu                              ; on backspace go back to main menu

stageSel:
    stx stage
    jmp gamePlay
    rts 

options: .byte  "1234", $14                     ; $14 is Backspace
optionsEnd:

.endproc 

;-----------------------------------------------------------------------------
; Take the number of options in accumulator
; Take a pointer to a number of options in x (lo) y (hi)
; returns when an option was selected, the index of the selected option in x
.proc uiHandleOptions

    timeout = tempBlock + 0

    sta len + 1                                 ; set the length for the number of options to look at
    stx option + 1                              ; set address of the options "string"
    sty option + 2

    lda #0
    sta NDX                                     ; flush the keyboard buffer
    sta lastInput
    sta TIME_1
    
loop:
    lda timeout                                 ; how long before this menu times out
    beq :+                                      ; 0 means never
    cmp TIME_1                                  ; how many seconds have elapsed (time_1 moves at approx. 4s intervals at 16ms)
    bne :+
    ldx len + 1                                 ; a timeout returns num options + 1 (maybe should be -1?)
    inx 
    rts 
:
    jsr inputCheckForInput                      ; get the input
    beq loop                                    ; no input keep looping
    cmp len + 1                                 ; if a >= num options
    bcs len                                     ; then it's a keyboard menu
    tax                                         ; it's a joystick selection
    dex                                         ; so 0 based, x-1 is the chosen option
    rts                                         ; done

len:
    ldx #0                                      ; placeholder 0

option:
    cmp uiHandleOptions,x                       ; placeholder address
    beq done                                    ; compare the keyboard to the options
    dex 
    bpl option                                  ; check all options
    bmi loop                                    ; when x is -1 it was an invalid entry so loop back

done:
    rts                                         ; x contains the number of the chosen option

.endproc 

;-----------------------------------------------------------------------------
.proc uiShowEditHelp

    lda #0                                      ; clear the keyboard buffer
    sta NDX
    sta lastInput

    jsr drawClearScreen                         ; clear the screen

    lda #VSCALE_UI                              ; UI scale for nice font
    sta VERA::DISP::VSCALE

    print textEdtHlp01, #(2*08), #(8*00), #$ff  ; show all the help text
    print textEdtHlp02, #(2*08), #(8*01), #$ff
    print textEdtHlp03, #(2*01), #(8*03), #$ff
    print textEdtHlp04, #(2*01), #(8*05), #$ff
    print textEdtHlp05, #(2*01), #(8*06), #$ff
    print textEdtHlp06, #(2*01), #(8*08), #$ff
    print textEdtHlp07, #(2*01), #(8*09), #$ff
    print textEdtHlp08, #(2*01), #(8*11), #$ff
    print textEdtHlp09, #(2*01), #(8*12), #$ff
    print textEdtHlp10, #(2*01), #(8*14), #$ff
    print textEdtHlp11, #(2*01), #(8*15), #$ff
    print textEdtHlp12, #(2*01), #(8*17), #$ff
    print textEdtHlp13, #(2*01), #(8*18), #$ff
    print textEdtHlp14, #(2*01), #(8*19), #$ff
    print textEdtHlp15, #(2*01), #(8*21), #$ff
    print textEdtHlp16, #(2*02), #(8*22), #$ff
    print textEdtHlp17, #(2*01), #(8*24), #$ff
    
    jsr drawPresent 

:
    jsr inputCheckForInput                      ; wait for the user to dismiss the help
    beq :-

    jsr drawClearScreen                         ; clear the screen

    lda #VSCALE_GAME                            ; back to game scale
    sta VERA::DISP::VSCALE

    lda #2                                      ; and force a
    sta updateHUD                               ; HUD update

    rts 

.endproc 


;-----------------------------------------------------------------------------
.proc uiWinScreen

    cntrl   = tempBlock + 4                     ; some delay counters, past the text* temporary vars
    cntrh   = tempBlock + 5
    palette = tempBlock + 6                     ; active palette

    jsr drawClearScreen

    lda #VSCALE_UI                              ; Get the taller screen
    sta VERA::DISP::VSCALE

    lda #8                                      ; init the counters - value
    sta cntrh                                   ; not important what these are init with
    sta cntrl
    sta palette                                 ; init the palette
    tay                                         ; need 4 colors so 8 bytes installed
    jsr drawSetPalette

    jsr drawPresent

; show the win screen text
    print textBonus    , #(2*17), #(8*00), #$FF

    printBig textPoints, #$10, #$04, #$01, #$01, #$FF
    printBig text1000  , #$07, #$0D, #$02, #$02, #$FF

    lda stage                                   ; last word changes for home vs victory
    beq :+
    printBig textWow   , #$03, #$1B, #$03, #$04, #$FF
    jmp present
:
    printBig textHome  , #$08, #$1B, #$02, #$04, #$FF

present:
    jsr drawPresent 

    lda #0
    sta NDX                                     ; flush the keyboard buffer
    sta lastInput
    sta TIME_1                                  ; set the lower 2 time bytes to zero
    sta TIME_2                                  ; in order to time the screen duration

loop:
    dec cntrl
    bne :+
    dec cntrh 
    bne :+
    ldy #8
    sty cntrl 
    sty cntrh 
    lda palette
    eor #%00001101                              ; eor 13 to flip between 5 and 8
    sta palette                                 ; 8 is the inverse of 5 for these purposes
    jsr drawSetPalette
:
    jsr inputCheckForInput 
    bne done                                    ; early exit on a key / button
    lda TIME_1
    cmp #$01                                    ; or exit when enough time has passed
    bcc loop

done:
    lda #VSCALE_UI                              ; Back to the shorter screen
    sta VERA::DISP::VSCALE

    rts

.endproc 

;-----------------------------------------------------------------------------
; Show the portions of the HUD that don't change between runs
.proc uiShowGameLabels

    lda #2                                      ; mark the HUD as needing update
    sta updateHUD

loop:

    print textTopLine  , #(2*04), #(8*00), #HUD_TEXT_MASK
    print textPlayerNum, #(2*21), #(8*00), #HUD_TEXT_MASK
    print textDanger   , #(2*04), #(8*23), #HUD_TEXT_MASK
    lda gameMode
    bne :+

    print textShips    , #(2*27), #(8*23), #HUD_TEXT_MASK
    beq show                                    ; JuMP to show - print always leaves with Z flag set

:
    print textTrainer  , #(2*28), #(8*23), #HUD_TEXT_MASK

show:
    jsr uiUpdateGameHud
    jsr drawPresent

    lda updateHUD
    beq done 
    jmp loop

done:
    rts 

.endproc 

;-----------------------------------------------------------------------------
; show the HUD variables that change over time
.proc uiUpdateGameHud

    clc                                         ; prep the HUD text for the stage
    lda stage 
    adc #'1'                                    ; zero based but HUD display 1-5 not 0-4
    sta textStage

    print textStage    , #(2*10), #(8*00), #HUD_TEXT_MASK
    print textDangerBar, #(2*10), #(8*23), #HUD_TEXT_MASK

    printBCD score     , #3, #0, #(2*30), #(8*00), #HUD_TEXT_MASK
 
    lda gameMode
    bne :+

    printBCD lives     , #1, #1, #(2*34), #(8*23), #HUD_TEXT_MASK

:
    dec updateHUD                               ; dec "show" counter

    rts 

.endproc

;-----------------------------------------------------------------------------
; Show the portions of the HUD that don't change between runs
.proc uiShowEditLabels

    brushType = tempBlock + 6

    lda #2                                      ; mark the HUD as needing update
    sta updateHUD

    clc                                         ; prep the HUD text for the stage
    lda stage 
    adc #'1'                                    ; zero based but HUD display 1-5 not 0-4
    sta textStage

loop:

    print textEditStage  , #(2*09), #(8*00), #HUD_TEXT_MASK
    print textStage      , #(2*16), #(8*00), #HUD_TEXT_MASK
    print textEditHelp   , #(2*05), #(8*23), #HUD_TEXT_MASK
    print textEditBrush  , #(2*23), #(9*00), #HUD_TEXT_MASK
    lda brushType 
    bne modeEnemy
    
    print textEditTerrain, #(2*30), #(9*00), #HUD_TEXT_MASK
    jmp :+

modeEnemy:
    print textEditEnemies, #(2*30), #(9*00), #HUD_TEXT_MASK

:
    jsr drawPresent
    dec updateHUD                               ; dec "show" counter
    beq done 
    jmp loop

done:
    rts 

.endproc 

;-----------------------------------------------------------------------------
.proc uiCheckHighScore

    scoreIdx    = tempBlock + 6

    clc 
    lda score                                   ; make sure one of the score components is non-zero
    adc score + 1                               ; because a zero score is not high-score eligible
    adc score + 2
    bne didScore
    rts 

didScore:
    lda #((highScoresEnd-highScores) / 3)       ; score insert point (1 past end of 0 based table)
    sta scoreIdx                                ; save the index
    ldx #((highScoresEnd-highScores) - 1)       ; point x at the high byte of the last score

nextScore:
    ldy #2                                      ; point y at the high byte of the current score
nextByte:
    lda score, y                                ; get the score byte
    cmp highScores, x                           ; compare to the high score byte
    bcc lt                                      ; if it's smaller, then this high-score is bigger than the score
    beq eq
:                                               ; score > highscore so ignore remaining bytes in this comparison
    dex 
    dey 
    bpl:-
    bmi gt                                      ; step over this smaller highscore
eq:
    dex                                         ; go to the next bytes
    dey 
    bpl nextByte                                ; look at the whole score
gt:
    dec scoreIdx                                ; the score is bigger than this high score so move "up" one
    bne nextScore                               ; compare against all high-scores in the table

lt:
    ldx #((highScoresEnd-highScores) / 3)       ; get the index past end
    cpx scoreIdx                                ; see if the scoreIdx still matches
    bne newHS                                   ; if not, then a new table entry needs to be made
    rts 

newHS:
    dex                                         ; x now points at last table entry (zero based)
    cpx scoreIdx                                ; see if the score overwrites the last table entry
    beq copyScore                               ; if yes, just copy score over last table entry

    jsr uiInsertHighScoreRow                    ; otherwise scores need to be moved so the score inserts

copyScore:
    lda scoreIdx                                ; calc the offset of the last byte of the score being replaced
    asl                                         ; start with index * 2 (and clears carry)
    adc scoreIdx                                ; + index (* 3 now sice 3 bytes / score)
    adc #2                                      ; and add 2 to point at the last byte
    tax                                         ; save this offset in x
    ldy #2                                      ; last byte of the score
: 
    lda score, y                                ; copy the score
    sta highScores, x                           ; over the high-score
    dex                                         ; for all 3 bytes
    dey 
    bpl :-

    jmp uiGetHighScoreName                      ; now get the new name

.endproc

;-----------------------------------------------------------------------------
; move the score and the name in the highscore table "down" a row
; so the new entry can go into the "space"
; scoreIdx is the number of the row that will move down
.proc uiInsertHighScoreRow

    bytes     = tempBlock + 5
    scoreIdx  = tempBlock + 6
    rows      = tempBlock + 7

    lda #(((highScoresEnd-highScores) / 3) - 1) ; Get the length of the table 0 based
    sec 
    sbc scoreIdx                                ; subtract the insert row
    sta rows                                    ; number of rows to move
    asl                                         ; mult by 3
    adc rows
    sta bytes                                   ; that's how many bytes to move
:beq:-
    ldy #((highScoresEnd-highScores)-4)         ; point at the second last row, last byte
    ldx #((highScoresEnd-highScores)-1)         ; point at the last row, last byte

scoreLoop:
    lda highScores, y                           ; copy the bytes
    sta highScores, x 
    dex 
    dey 
    dec bytes 
    bne scoreLoop                               ; till all bytes copied

    lda rows                                    ; prep to copy name rows
    asl                                         ; * 8 - 1 is * 7 (7 bytes/name - incl null terminator)
    asl 
    asl 
    sec 
    sbc rows 
    sta bytes                                   ; set the number of bytes to copy

    ldy #((textHSEnd-textHS)-8)                 ; point at the second last row, last byte
    ldx #((textHSEnd-textHS)-1)                 ; point at the last row, last byte

nameLoop:
    lda textHS, y                               ; copy the bytes
    sta textHS, x 
    dex 
    dey 
    dec bytes 
    bne nameLoop                                ; till all bytes copied

    rts 

.endproc 

;-----------------------------------------------------------------------------
; Let the player enter a name for the high score table
; the table entry (0 based) is in scoreIdx when called
.proc uiGetHighScoreName

    zaStrL   = zTemp1                           ; ptr to a string to print
    zaStrH   = zTemp2
    zaEntryL = zWorldPtr                        ; ptr to a string being entered (abusing world ptr)
    zaEntryH = zWorldPtr + 1
    scoreIdx = tempBlock + 6                    ; 0 based index into score table
    entryLen = tempBlock + 11                   ; how many characters the player has entered - shared with uiGetUserText
    textLen  = tempBlock + 12                   ; how many characters the player may enter with uiGetUserText

    jsr drawClearScreen
    lda #VSCALE_UI                              ; set the screen to the nicer font size
    sta VERA::DISP::VSCALE

    ldy #8                                      ; UI palette is 8 bytes long
    lda #UI_PALETTE
    jsr drawSetPalette                          ; set up the UI palette

    clc 
    ldx scoreIdx                                ; get the index into the score table
    lda #<textHS                                ; and zaEntry with the start of the
    adc scoreTextOffset, x                      ; 1st byte of where the text must go
    sta zaEntryL
    lda #0
    adc #>textHS
    sta zaEntryH

    lda #95                                     ; the "_" character so stomp the current entry with underscores
    ldx #((textHighScore2-textHighScore1)-1)    ; all scores have the same length
    stx textLen                                 ; save how long the name may be
    ldy #0                                      ; start at character 0
:
    sta (zaEntryL), y                           ; write the underscores (also restores the original length)
    iny                                         ; by overwriting terminators of old entered text
    dex 
    bne :-
    stx entryLen                                ; save 0 to the length of the new name

showName:
    print textCongrats , #(2*04), #(8*05), #$ff ; show the screen
    print textHSPlayer , #(2*14), #(8*06), #$ff
    print textPlayerNum, #(2*24), #(8*06), #$ff
    print textHSPlayer , #(2*14), #(8*06), #$ff
    print textTop5     , #(2*07), #(8*08), #$ff
    print textTypeName , #(2*08), #(8*09), #$ff

    lda zaEntryL                                ; prep the print string
    sta zaStrL                                  ; by using the entry string location
    lda zaEntryH                                ; zaStrL is modified through printing
    sta zaStrH                                  ; but the entry copy is stable

    printZAStr #(2*17), #(8*11), #$ff           ; print the name
    jsr drawPresent

    jsr uiGetUserText                           ; Get a character
    bcc enter                                   ; on carry clear enter was pressed
    jmp showName                                ; show the updated name

enter:
    ldy entryLen                                ; get how many characters entered
    lda #0                                      ; load a null terminator
    sta (zaEntryL), y                           ; terminate the string

done:
    jsr drawClearScreen

    lda #VSCALE_GAME                            ; set the screen back to in-game size for 2 player games
    sta VERA::DISP::VSCALE

    rts 

.endproc

;-----------------------------------------------------------------------------
; Show a UI screen asking for a file name to load or save
; Parameter in acc. 0 is save and 1 is load
.proc uiFileLoadSave

    zaStrL   = zTemp1                           ; internal - ptr to a string to print
    zaStrH   = zTemp2                           ; internal
    zaEntryL = zWorldPtr                        ; internal - ptr to a string being entered (abusing world ptr)
    zaEntryH = zWorldPtr + 1                    ; internal
    entryLen = tempBlock + 11                   ; internal - how many characters the player has entered
    textLen  = tempBlock + 12                   ; internal - how many characters the player may enter
    forLoad  = tempBlock + 13                   ; Parameter - 0 means save, 1 means load
    allOver  = tempBlock + 14                   ; internal - on enter, redraw the screen 1 more time
    scale    = tempBlock + 15                   ; internal - the DC_VSCALE when called

    sta forLoad
    jsr drawClearScreen

    lda VERA::DISP::VSCALE                      ; see what scale is in effect and save it
    sta scale
    lda #VSCALE_UI                              ; set the screen to the nicer font size
    sta VERA::DISP::VSCALE

    ldy #8                                      ; UI palette is 8 bytes long
    lda #UI_PALETTE
    jsr drawSetPalette                          ; set up the UI palette

    lda #<textFileName                          ; point at the file name
    sta zaEntryL
    lda #>textFileName
    sta zaEntryH
    lda #((textFileNameEnd - textFileName) - 1) ; get how long the name may be
    sta textLen

    ldy #0 
    sty NDX                                     ; clear the keyboard buffer
    sty lastInput                               ; and the last key
    sty allOver                                 ; 1 when the name has been entered - for redraw
:                                               ; get the length of the file name there already
    lda (zaEntryL), y                           ; get the first letter
    beq :+                                      ; if trailing zero then name is known
    iny 
    bne :-
:
    sty entryLen                                ; save the length of the name

    lda #95                                     ; the "_" character so stomp the remaining name with underscores
:
    cpy textLen 
    bcs showName
    sta (zaEntryL), y                           ; write the underscores (also restores the original length)
    iny                                         ; by overwriting terminators of old entered text
    bne :-

showName:
    lda forLoad
    beq :+
    print textFileLoad   , #(2*16), #(8*02), #$ff
    print textFileInfoL  , #(2*13), #(8*08), #$ff
    jmp cont
:
    print textFileSave   , #(2*16), #(8*02), #$ff
    print textFileInfoS  , #(2*13), #(8*08), #$ff

cont:
    print textFileLines  , #(2*16), #(8*03), #$ff
    print textFileInfo   , #(2*18), #(8*08), #$ff
    print textFileEnter  , #(2*09), #(8*10), #$ff

    lda zaEntryL                                ; prep the print string
    sta zaStrL                                  ; by using the entry string location
    lda zaEntryH                                ; zaStrL is modified through printing
    sta zaStrH                                  ; but the entry copy is stable

    printZAStr             #(2*15), #(8*14), #$ff

    lda allOver                                 ; is this the last redraw before going to disc
    bne disc                                    ; if <> 0 then time to go to disc

    jsr drawPresent                             ; show the screen with changes to file name

    jsr uiGetUserText                           ; Get a character
    bcc enter                                   ; on carry clear enter was pressed
    jmp showName                                ; show the updated name

enter:
    ldy entryLen                                ; get how many characters entered
    lda #0                                      ; and null terminate the string
    sta (zaEntryL), y

    lda #1                                      ; enter has been pressed - it's all over
    sta allOver                                 ; time to attempt a disc action, but just redraw once more
    jmp showName 

disc:
    lda forLoad                                 ; load or save
    beq save
    
    jsr fileLoad                                ; load the file by the name
    bcs fail                                    ; if carry set then there's an error
    jmp success                                 ; no error - all good

save:
    jsr fileSave                                ; save the file
    bcs fail                                    ; if carry set then there's an error

success:
    print textFileSuccess, #(2*17), #(8*18), #$ff
    jmp show

fail:                                           ; there was an error saving the file
    pha                                         ; error code in the accumulator, so save it
    print textFileThe    , #(2*05), #(8*18), #$aa
    print textFileFailed , #(2*14), #(8*18), #$aa

    lda forLoad                                 ; message for load/save differ
    beq :+

    print textFileInfoL  , #(2*09), #(8*18), #$aa
    jmp errcde

:
    print textFileInfoS  , #(2*09), #(8*18), #$aa

errcde:
    pla                                         ; get the saved error code
    jsr toHex                                   ; print it as human readable hex and show it to the user
    print szHex          , #(2*34), #(8*18), #$aa

show:
    jsr drawPresent                             ; finally show the whole screen

getkey:
    jsr inputCheckForInput                      ; wait for the user to acknowledge
    beq getkey

    jsr drawClearScreen

    lda scale                                   ; restore the screen v scale
    sta VERA::DISP::VSCALE

    rts 

.endproc

;-----------------------------------------------------------------------------
; Called with zaEntry pointing at a location to receive some text
; and entryLen should be 0 and is used internally to track where the current
; edit location in the string is.
; returns with partial string when carry set
; User pressed enter and accepted the string when carry clear on return
.proc uiGetUserText

    zaEntryL = zWorldPtr                        ; ptr to a string being entered (abusing world ptr)
    entryLen = tempBlock + 11                   ; Parameter/Internal - how many characters the player has entered
    textLen  = tempBlock + 12                   ; how many characters the player may enter

    lda #0
    sta NDX                                     ; flush the keyboard buffer
    
loop:
    jsr GETIN                                   ; wait for a key
    beq loop
    cmp #13                                     ; enter key then done
    beq enter 
    cmp #$14                                    ; backspace key is handled
    beq erase 
    cmp #32
    beq accept                                  ; space is okay
    cmp #'0'
    bcc loop                                    ; ignore below '0'
    cmp #('9'+1)
    bcc accept                                  ; 0-9 okay
    cmp #('A')
    bcs upper
    cmp #'a'
    bcc loop                                    ; less than 'a' rejected
    cmp #('z'+1)
    bcs loop                                    ; reject between z and A
upper:
    cmp #('Z'+1)                                ; lowercase accepted falls through here also
    bcs loop                                    ; ignore past 'Z'

accept:
    ldy entryLen                                ; how many characters already entered
    cpy textLen                                 ; vs how many can be entered
    bcs loop                                    ; already full, don't accept
    sta (zaEntryL), y                           ; and write this character there
    inc entryLen                                ; and increase the length entered
goShow:
    sec                                         ; on carry set, not done
    rts 

erase:
    ldy entryLen                                ; get how many characters have been entered
    beq loop                                    ; if none then ignore the backspace key
    dec entryLen                                ; 1 less character entered
    dey 
    lda #95                                     ; load the underscore
    sta (zaEntryL), y                           ; stomp the last character with the underscore
    bne goShow                                  ; redraw the screen

enter:
    clc 
    rts 

.endproc 

;-----------------------------------------------------------------------------
.proc uiShowLogoGraphic

    zaLogoDataL = zTemp3
    zaLogoDataH = zTemp4

    ROW_LEN = 120

    lda #0                                      ; Set channel and address lo
    sta VERA::CTRL                              ; all functions leave with low active (convention)

    lda #VSCALE_GFX
    sta VERA::DISP::VSCALE

    lda #(gfx_layer1 >> 9)                      ; layer1 mem at gfx_layer1
    sta VERA::L0::TILE_BASE

    lda VERA::DISP::VIDEO
    and #%11001111                              ; both latyers off
    sta VERA::DISP::VIDEO

    lda #%00000110                              ; set bitmap mode and 4bpp
    sta VERA::L0::CONFIG

    lda #<((logoEnd-logoStart)/3)               ; length of all encoded bytes / 3
    sta zTemp1                                  ; is the length to process
    lda #>((logoEnd-logoStart)/3)
    sta zTemp2

    lda #<logoStart                             ; start of encoded bytes in ram
    sta zaLogoDataL
    lda #>logoStart
    sta zaLogoDataH

    ldy #14                                     ; install a palette
    lda #6
    jsr drawSetPalette

    lda #$10                                    ; stride 1 starting at 0,0
    sta VERA::ADDR + 2                          ; HI
    lda #>gfx_layer1
    sta hi + 1                                  ; not needed but allows code
    sta VERA::ADDR + 1                          ; MID
    lda #<gfx_layer1
    sta lo + 1                                  ; to run a 2nd time (after CTRL-R in emulator, for example)
    sta VERA::ADDR                              ; LO

    lda #ROW_LEN                                ; the encoded data needs to be
    sta zTemp5                                  ; broken to a NL every 120 bytes

loop:                                           ; the decode loop
    ldy #0
    lda (zaLogoDataL), y                        ; get the lengths (hi lo)
    pha                                         ; save
    lsr                                         ; get hi to lo
    lsr 
    lsr 
    lsr 
    jsr store                                   ; go plot
    pla                                         ; get the lengths again
    and #$0f                                    ; now get lo
    jsr store                                   ; go plot
    lda zaLogoDataL                             ; advance the data ptr by 3
    clc 
    adc #3
    sta zaLogoDataL 
    bcc :+
    inc zaLogoDataH 
:
    lda zTemp1                                  ; see if length lo = 0
    bne :+                                      ; if not skip dec hi
    dec zTemp2                                  ; dec length hi
:
    dec zTemp1                                  ; dec length lo
    lda zTemp2                                  ; get the hi
    bpl loop                                    ; if not underflow more to decompress

    lda VERA::DISP::VIDEO
    and #%11001111                              ; both latyers off
    ora #%00010000                              ; turn layer 0 on (show the 4bpp image)
    sta VERA::DISP::VIDEO

    lda #$00                                    ; restore the HI addr to 0 (is assumed elsewhere)
    sta VERA::ADDR+2                            ; HI

    rts                                         ; all done

store:
    tax                                         ; bytes to write in x
    iny                                         ; get the byte to write
    lda (zaLogoDataL), y 
:
    sta VERA::DATA0                             ; store to vera
    dec zTemp5                                  ; end of a row?
    beq nextRow
cont:
    dex                                         ; do for all bytes in this run
    bne :-
    rts 

nextRow:                                        ; reached row end, move vera to start of next row
    pha                                         ; save a
    lda lo + 1                                  ; move vera on to next row (160 bytes)
    clc 
    adc #$A0
    sta lo + 1
    bcc hi
    inc hi +  1

hi:
    lda #>gfx_layer1                            ; update vera
    sta VERA::ADDR + 1                          ; MID

lo:
    lda #<gfx_layer1
    sta VERA::ADDR                              ; LO

    lda #ROW_LEN                                ; reset the row counter
    sta zTemp5
    pla                                         ; restore the value in the run to a

    jmp cont

.endproc 

;-----------------------------------------------------------------------------
; All this does is make a border and flash it yellow/blue.  An iteration
; of bigger bars, for short, then short (fast) bars for longer
; Looks like an old-school tape fast load
.proc uiSimulateLoad 

    color    = tempBlock                        ; color of border
    delay    = tempBlock + 1                    ; how long a "bar" holds
    duration = tempBlock + 2                    ; how long a "pattern" of bars hold
    cyclel   = tempBlock + 3                    ; how many bars to make lo byte
    cycleh   = tempBlock + 4                    ; how many bars to make hi byte
    iter     = tempBlock + 5                    ; how many iterations of patterns there are

    lda #6
    sta color                                   ; 6 is blue and xor 1 = 7, yellow
    sta duration

    lda #$0
    sta cyclel

    lda #3
    sta delay

    lda #2
    sta iter

loopo:
    lda duration
    sta cycleh

loop:
    lda color                                   ; flip the color
    eor #1
    sta color
; tax
    sta VERA::DISP::FRAME                       ; set the border color
    ldx #$00                                    ; set up for a delay
    ldy delay
:
    dex 
    bne :-                                      ; 256 on x
    dey 
    bne :-                                      ; "delay" on why
    dec cyclel                                  ; 256 on cyclel
    bne loop
    dec cycleh                                  ; duration on cycleh
    bne loop
    lda #%00000010                              ; flip delay between 3 and 1
    eor delay
    sta delay
    lda #%00100010                              ; flip duration between 6 and 36
    eor duration
    sta duration
    dec iter                                    ; complete one iteration
    bne loopo

    rts 

.endproc 
