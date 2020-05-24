;-----------------------------------------------------------------------------
; text.inc
; Part of penetrator, the zx spectrum game, made for commander x16
;
; Stefan Wessels, 2019
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "RODATA"

.feature        string_escapes

; In game text
textTopLine:      .asciiz "Stage  . Player - - Score       0"
textDanger:       .asciiz "Danger"
textShips:        .asciiz "Ships"
textTrainer:      .asciiz "Trainer"
textPlayer:       .asciiz "P L A Y E R  "

; title screen
textHighScores:   .asciiz "High  Scores"
textPhilip:       .asciiz "Written by - Philip Mitchell -"
textCopyright:    .asciiz "** Copyright  \"Beam Software\" **"
textSource:       .asciiz "Source on GitHub:"
textGitHub:       .asciiz "https://github.com/StewBC/penetrator"
textGameOver:     .asciiz "************** GAME  OVER **************"
textCommander:    .asciiz "Commander X16 version by"
textStefan:       .asciiz "Stefan Wessels, Nov 2019"

; main menu
textInstructions: .asciiz "INSTRUCTIONS"
textPress:        .asciiz "PRESS"
textUnderline:    .asciiz "-----"
textOneTwo:       .asciiz "\"1\" OR \"2\" FOR NUMBER OF PLAYERS"
textTrain:        .asciiz "\"T\"  FOR TRAINING CONTROL CENTER"
textEdit:         .asciiz "\"E\" FOR THE LANDSCAPE EDITOR"
textLoad:         .asciiz "\"L\"  TO LOAD ANOTHER LANDSCAPE"
textSirens:       .asciiz "\"S\" TO DISABLE SIRENS"
textJoyhead:      .asciiz "JOY Buttons"
textJoyheadLine:  .asciiz "-----------"
textJoy1:         .asciiz "RIGHT/LEFT - 1/2 player"
textJoy2:         .asciiz "DOWN/UP - T/E"
textJoy3:         .asciiz "START/SELECT - L/S"
textNotDone:      .asciiz "Not implemented"

; training mode menu
textTrainingMode: .asciiz "TRAINING MODE"
textPressStage:   .asciiz "PRESS NUMBER OF DESIRED STAGE"
textOneToFour:    .asciiz "(1 - 4) TO START."
textBackup:       .asciiz "BACKSPACE to back up or exit mode"

; edit mode screen
textEditStage:    .asciiz "STAGE"
textEditHelp:     .byte   "PRESS 'C' FOR  ",$86," COMMAND SUMMARY", $00
textEditBrush:    .asciiz "BRUSH: "
textEditTerrain:  .asciiz "TERRAIN"
textEditEnemies:  .asciiz "ENEMIES"
textEditDnArrow:  .byte   $85, $00

; edit help screen
textEdtHlp01:      .asciiz "LANDSCAPE EDITOR COMMANDS"
textEdtHlp02:      .asciiz "--------- ------ --------"
textEdtHlp03:      .asciiz "DIRECTION - MOVE THE CURSOR"
textEdtHlp04:      .asciiz "START     - TOGGLE BETWEEN TERRAIN"
textEdtHlp05:      .asciiz " (ENTER)    AND ENEMY BRUSHES"
textEdtHlp06:      .asciiz "SELECT    - CONTINIOUS MOVEMENT"
textEdtHlp07:      .asciiz " (SPACE)"
textEdtHlp08:      .asciiz "A         - SET TERRAIN TOP"
textEdtHlp09:      .asciiz " (CTRL)     OR PLACE A MISSILE"
textEdtHlp10:      .asciiz "B         - SET TERRAIN BOTTOM OR"
textEdtHlp11:      .asciiz " (ALT)      PLACE A RADAR"
textEdtHlp12:      .asciiz "1 - 5     - SKIP TO STAGE"
textEdtHlp13:      .asciiz "S         - SAVE THIS WORLD"
textEdtHlp14:      .asciiz "L         - LOAD A WORLD"
textEdtHlp15:      .asciiz "ERASE ENEMIES USING A/B WITH THE"
textEdtHlp16:      .asciiz "ENEMIES BRUSH"
textEdtHlp17:      .asciiz "BACKSPACE - END THE EDIT SESSION"

; win screen
textBonus:        .asciiz "BONUS"
textPoints:       .asciiz "POINTS"
text1000:         .asciiz "1000"
textWow:          .asciiz "WOW"
textHome:         .asciiz "HOME"

; high score name entry
textCongrats:     .asciiz "*****   CONGRATULATIONS    *****"
textHSPlayer:     .asciiz "PLAYER -- "
textTop5:         .asciiz "Your score is in the top 5"
textTypeName:     .asciiz "Please type in your name"

; file name entry
textFileLoad:     .asciiz "FILE LOAD"
textFileSave:     .asciiz "FILE SAVE"
textFileLines:    .asciiz "---------"
textFileInfoL:    .asciiz "Load"
textFileInfoS:    .asciiz "Save"
textFileInfo:     .asciiz "world data"
textFileEnter:    .asciiz "Please enter a file name"
textFileSuccess:  .asciiz "SUCCESS."
textFileThe:      .asciiz "The"
textFileFailed:   .asciiz "Failed.  Error Code"

;-----------------------------------------------------------------------------
.segment "DATA"

textHS:
textHighScore1:   .asciiz "123456"
textHighScore2:   .asciiz "123456"
textHighScore3:   .asciiz "123456"
textHighScore4:   .asciiz "123456"
textHighScore5:   .asciiz "123456"
textHSEnd:

textStage:        .asciiz "1"
textPlayerNum:    .asciiz "1"
textNumber:       .asciiz "1234567"             ; score display 10x score - extra digit needed
textDangerBar:    .asciiz "123"
textEnd:

textFileName:     .asciiz "pen wrld 01"         ; default file name
textFilePad:      .asciiz ""                    ; This makes the null terminator on textFileName viable and a 12 char filename
textFileNameEnd:
szHex:            .asciiz "  "


;-----------------------------------------------------------------------------
.segment "CODE"

;-----------------------------------------------------------------------------
; Use the print macro to call this code
; Writes a null-terminated string to the back buffer
; temp1/2 Ptr to the string
; temp3 a color mask ($55, $aa or $ff) - 2bpp can mask out a column
; textX - the string draw X position (in col coords)
; textY - the string draw Y position
.proc textOut

    textX = tempBlock + 0
    textY = tempBlock + 1
    xPos  = tempBlock + 2
    yPos  = tempBlock + 3

    zaStrL = zTemp1                             ; parameter - string lo
    zaStrH = zTemp2                             ; parameter - string hi
    zaFontMask = zTemp3                         ; color mask
    zaFontL = zTemp4                            ; internal - point at the character memory Lo
    zaFontH = zTemp5                            ; internal - point at the character memory Hi
    zaFontOffset = zTemp6                       ; 0-15 - index from zaFont
 
    lda #$10                                    ; stride of 1
    sta VERA::ADDR + 2                          ; HI

loop:
    ldy #0
    lda (zaStrL), y                             ; get the character in the string
    bne :+                                      ; if non-null process it
    rts                                         ; exit on 0 terminator

:
    jsr setFont
    lda textY                                   ; get the screen Y for text
    sta yPos                                    ; init the row working buffer
    ldx backLayer                               ; write to back layer

plotLoop:
    ldy yPos                                    ; at the working row offset
    lda rowL, y                                 ; get the memory address
    adc textX                                   ; add in column (x pos of text)
    sta VERA::ADDR                              ; point vera at memory
    lda rowH, y
    adc layersH, x
    sta VERA::ADDR + 1                          ; MID

    ldy zaFontOffset                            ; get the offset into the font
    lda (zaFontL), y                            ; get the actual left character byte
    and zaFontMask                              ; mask for color
    sta VERA::DATA0                             ; plot the left hand side
    iny                                         ; go to next byte (right hand side of character)
    lda (zaFontL), y 
    and zaFontMask
    sta VERA::DATA0
    cpy #15                                     ; characters are 16 bytes long
    bcs nextChar                                ; if 16 then done with this character
    inc zaFontOffset                            ; move 2 bytes for last row plotted
    inc zaFontOffset
    inc yPos                                    ; move down a row on screen
    
    bne plotLoop                                ; always take this branch

nextChar:
    inc textX                                   ; 2 columns per character
    inc textX 
    inc zaStrL                                  ; next character in string
    bne loop 
    inc zaStrH 
    bne loop                                    ; always branch back

.endproc

;-----------------------------------------------------------------------------
; Like textOut but uses drawPoltXY to plot each pixel in the text
; so you can write big strings using width and height.
; a setting of width and height both 1 results in a character that's
; 32x32 on-screen
.proc textBigPrint

    zaStrL       = zTemp1                       ; parameter - string lo
    zaStrH       = zTemp2                       ; parameter - string hi
    zaBitCnt     = zTemp3                       ; internal - how many bits to process for a byte to write
    zaFontL      = zTemp4                       ; internal - point at the character memory Lo
    zaFontH      = zTemp5                       ; internal - point at the character memory Hi
    zaFontOffset = zTemp6                       ; internal - 0-15 - index from zaFont
 
    width        = tempBlock + 14               ; shared with drawPlotXY
    height       = tempBlock + 15
    plotCol      = tempBlock + 16

    textX        = tempBlock + 0
    textY        = tempBlock + 1
    xPos         = tempBlock + 2
    yPos         = tempBlock + 3

loop:
    ldy #0
    lda (zaStrL), y                             ; get the character in the string
    bne :+                                      ; if non-null process it
    rts                                         ; exit on 0 terminator

:
    jsr setFont 

    lda textY                                   ; get the screen Y for text
    sta yPos 

plotLoop:

    lda textX
    sta xPos 

    ldx #4                                      ; each font character byte has 4 pixels (the font
    stx zaBitCnt                                ; has each column doubled up for 2bpp)

    ldy zaFontOffset                            ; get the offset into the font
    lda (zaFontL), y                            ; get the actual left character byte
    jsr drawBits                                ; draw the character

    ldx #3                                      ; the last column is blank in the font (for my purposes)
    stx zaBitCnt

    inc zaFontOffset                            ; go to the right half of the character
    ldy zaFontOffset
    lda (zaFontL), y 
    jsr drawBits 

    inc zaFontOffset                            ; go to the next line, left side
    ldy zaFontOffset

    cpy #16                                     ; characters are 16 bytes long
    bcs nextChar                                ; if 16 then done with this character
    lda yPos                                    ; adjust the "plot" down a line
    clc 
    adc height
    sta yPos

    bne plotLoop                                ; always take this branch

nextChar:
    lda width                                   ; move along in X to the next character
    asl                                         ; which is 8x the width wide
    asl 
    asl 
    adc textX                                   ; add to current "plot" position
    sta textX 
    inc zaStrL                                  ; next character in string
    bne loop 
    inc zaStrH 
    bne loop                                    ; always branch back

drawBits:
    asl                                         ; shift 2x because the font is 16 pixels wide
    asl                                         ; so only ever 2nd bit (pixel) matters
    pha                                         ; save the shifted byte
    bcc :+                                      ; if carry is set, need to plot a pixel
    clc 
    ldx xPos                                    ; get the x and y of where to plot
    ldy yPos
    jsr drawPlotXY                              ; draw the pixel
:
    lda xPos                                    ; move along one "pixel"
    clc 
    adc width
    sta xPos
    pla                                         ; restore the shifted character
    dec zaBitCnt                                ; see if all bytes were handled
    ldx zaBitCnt
    bne drawBits
    rts 

.endproc 

;-----------------------------------------------------------------------------
; Point zaFont(H|L) at the character definition for the character in the accumulator
; y register must be 0 when calling this routine
.proc setFont

    zaFontL      = zTemp4                       ; internal - point at the character memory Lo
    zaFontH      = zTemp5                       ; internal - point at the character memory Hi
    zaFontOffset = zTemp6                       ; internal - 0-15 - index from zaFont

    sty zaFontOffset                            ; start at 0th byte in font
    sty zaFontH 
    sty zaFontL 

	cmp #$C0                                    ; Uppercase characters are stored above $C0 internally
	bcc :+ 
    sbc #$60                                    ; adjust uppercase down to above pound for font
:
    sec                                         ; subtract 32 as font starts at char 32 (space)
    sbc #$20
    asl                                         ; mult 16 as that's how many bytes per char
    rol zaFontH 
    asl 
    rol zaFontH 
    asl 
    rol zaFontH 
    asl 
    rol zaFontH 
    adc #<font                                  ; add in the memory location
    sta zaFontL 
    lda #>font 
    adc zaFontH 
    sta zaFontH                                 ; now font points at the character data

    rts 

.endproc 

;-----------------------------------------------------------------------------
; Turns a BCD number into a text string at textNumber.
; zaStr is a ptr to the number in BCD
; y reg is the number of bytes to convert
; x reg <> 0 means print at least one digit, even if 0
.proc textBCDtoSZ 

    zaStrL     = zTemp1
    zaStrH     = zTemp2
    zaForce    = zTemp3

    stx zaForce 
    dey                                         ; zero based so -1
    ldx #0

leading:                                        ; skip leading 0's with spaces
    lda #' '                                    ; prep buffer with two spaces
    sta textNumber, x                           ; if the byte to output is $00
    sta textNumber + 1, x                       ; so leading 0's are skipped
    lda (zaStrL), y                             ; get the high byte
    bit Bit8765Mask                             ; check 1st digit
    bne loop1                                   ; if not zero - start printing
    inx                                         ; skip the zero by accepting the space
    and #$0f                                    ; check the 2nd digit
    beq :+                                      ; go skip if zero
    jsr digit                                   ; print the digit
    bne loop2                                   ; and join the main print loop
:
    inx                                         ; skip the next char in the output string
    dey                                         ; go to next byte in the BCD number
    bpl leading                                 ; keep going till all bytes done
    ldy zaForce                                 ; nothing printed - see if at least 1 digit
    beq done                                    ; needs to be printed and if no - then done
    dex                                         ; step back one digit in the string
    lda #'0'                                    ; get a zero
    sta textNumber, x                           ; put it in the string
    inx 
    bne done                                    ; JuMP to done

loop:                                           ; main loop once a digit is found
    lda (zaStrL), y                             ; get the 2 decimal digits
loop1:
    jsr both                                    ; print them both starting with left
loop2:
    dey                                         ; next score part
    bpl loop                                    ; keep going while there are score parts

done:
    lda #0                                      ; load a null-terminator
    sta textNumber, x                           ; store it in the output string
    rts 

both:
    pha                                         ; save the 2 digits
    lsr                                         ; shift right down
    lsr 
    lsr 
    lsr 
    jsr digit                                   ; go print it
    pla                                         ; restore both
    and #$0f                                    ; mask off the right leaving left
digit:                                          ; print the digit
    ora #$30                                    ; add "0" to the decimal
    sta textNumber, x                           ; put it in the string
    inx                                         ; advance the string pointer
    rts 

.endproc

;-----------------------------------------------------------------------------
; Prints the accumulator to the szHez text as 2 hex bytes
.proc toHex

    ldx #0                                      ; offset into the szHex buffer
    pha                                         ; save a for lower 4 bits
    lsr                                         ; move upper 4 bits to lo
    lsr 
    lsr 
    lsr 
    jsr :+                                      ; process upper 4 bits
    pla                                         ; restore a to process lower 4 bits
:
    and #$0f                                    ; mask to only the 4 bits now in lo
    cmp #10                                     ; see if it's > 9
    bcc :+
    adc #6                                      ; move from 10+ to a+
   :
    adc #$30                                    ; and move to '0' and beyond
    sta szHex, x                                ; save this in the buffer
    inx                                         ; go to next buffer location
    rts                                         ; and return to self or caller

.endproc
