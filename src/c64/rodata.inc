;-----------------------------------------------------------------------------
; rodata.inc
; Part of penetrator, the zx spectrum game, made for Commodore C64
;
; Stefan Wessels, 2019, 2023
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "RODATA"

;-----------------------------------------------------------------------------
; the lo byte for the memory at the start of every screen row
rowL:
    .repeat $C0, Row
        .byte   <(XINSET * 8 + (Row / 8) * 320 + Row .MOD 8)
    .endrep

;-----------------------------------------------------------------------------
; the hi byte for the memory at the start of every screen row
rowH:
    .repeat $C0, Row
        .byte   >(XINSET * 8 + (Row / 8) * 320 + Row .MOD 8)
    .endrep

;-----------------------------------------------------------------------------
; the lo byte for the memory at the start of every screen column
times8L:
    .repeat $28, Col
        .byte   <(Col * 8)
    .endrep

;-----------------------------------------------------------------------------
; the hi byte for the memory at the start of every screen column
times8H:
    .repeat $28, Col
        .byte   >(Col * 8)
    .endrep

;-----------------------------------------------------------------------------
; Per row start of color ram
colRowL:
    .repeat $18, Row
        .byte <(XINSET+(Row*40))
    .endrep

colRowH:
    .repeat $18, Row
        .byte >(XINSET+(Row*40))
    .endrep

;-----------------------------------------------------------------------------
; pixels in format for drawPlotXY
plotPix: .byte %11110000, %00001111

;-----------------------------------------------------------------------------
stageColor:
    .byte BCOLOR_BLACK     | BCOLOR_YELLOW    << 4
    .byte BCOLOR_BLUE      | BCOLOR_WHITE     << 4
    .byte BCOLOR_GREEN     | BCOLOR_BLACK     << 4
    .byte BCOLOR_CYAN      | BCOLOR_BLACK     << 4
    .byte BCOLOR_RED       | BCOLOR_BLACK     << 4

stageTextColor:
    .byte BCOLOR_BLACK     | BCOLOR_WHITE     << 4
    .byte BCOLOR_BLUE      | BCOLOR_WHITE     << 4
    .byte BCOLOR_GREEN     | BCOLOR_BLACK     << 4
    .byte BCOLOR_CYAN      | BCOLOR_BLACK     << 4
    .byte BCOLOR_RED       | BCOLOR_WHITE     << 4

playerColor:
    .byte BCOLOR_BLACK     | BCOLOR_CYAN      << 4
    .byte BCOLOR_BLUE      | BCOLOR_GREEN     << 4
    .byte BCOLOR_GREEN     | BCOLOR_BLACK     << 4
    .byte BCOLOR_CYAN      | BCOLOR_RED       << 4
    .byte BCOLOR_RED       | BCOLOR_WHITE     << 4

radarColor:
    .byte BCOLOR_BLACK     | BCOLOR_PURPLE    << 4
    .byte BCOLOR_BLUE      | BCOLOR_WHITE     << 4
    .byte BCOLOR_GREEN     | BCOLOR_BLUE      << 4
    .byte BCOLOR_CYAN      | BCOLOR_BLUE      << 4
    .byte BCOLOR_RED       | BCOLOR_BLUE      << 4

missileColor:
    .byte BCOLOR_BLACK     | BCOLOR_YELLOW    << 4
    .byte BCOLOR_BLUE      | BCOLOR_YELLOW    << 4
    .byte BCOLOR_GREEN     | BCOLOR_BLACK     << 4
    .byte BCOLOR_CYAN      | BCOLOR_BLACK     << 4
    .byte BCOLOR_RED       | BCOLOR_BLACK     << 4

nukeColor:
    .byte BCOLOR_RED       | BCOLOR_WHITE     << 4

monsterColor:
    .byte BCOLOR_BLACK     | BCOLOR_RED       << 4
    .byte BCOLOR_BLUE      | BCOLOR_RED       << 4
    .byte BCOLOR_GREEN     | BCOLOR_RED       << 4
    .byte BCOLOR_CYAN      | BCOLOR_PURPLE    << 4
    .byte BCOLOR_RED       | BCOLOR_BLACK     << 4

bombColor:
    .byte BCOLOR_BLACK     | BCOLOR_YELLOW    << 4
    .byte BCOLOR_BLUE      | BCOLOR_YELLOW    << 4
    .byte BCOLOR_GREEN     | BCOLOR_WHITE     << 4
    .byte BCOLOR_CYAN      | BCOLOR_PURPLE    << 4
    .byte BCOLOR_RED       | BCOLOR_GREEN     << 4

;-----------------------------------------------------------------------------
; Audio
uiSound:        .byte $4B, $22, $04, $95, $44, $02, $00
gunSound:       .byte $10, $5A, $01, $10, $57, $02, $10, $54, $03, $10, $51, $04, $10, $4e, $05, $00
bombSound:      .byte $10, $24, $01, $10, $14, $01, $10, $0c, $02, $10, $02, $10, $00
sirenSound:     .byte $00, $00, $FF, $00
engineSoundN:   .byte $30, $02, $03, $40, $02, $03, $35, $02, $03, $00
engineSoundS:   .byte $10, $01, $03, $20, $01, $03, $15, $01, $03, $00
engineSoundF:   .byte $50, $03, $03, $60, $03, $03, $55, $03, $03, $00

;-----------------------------------------------------------------------------
; Offsets for printing the high score table on the title screen
scoreTextOffset:
.byte textHighScore1-textHS
.byte textHighScore2-textHS
.byte textHighScore3-textHS
.byte textHighScore4-textHS
.byte textHighScore5-textHS
scoreTextPosX:
.byte 10, 02, 18, 1, 19
scoreTextPosY:
.byte 8 , 16, 16, 24, 24
scorePosX:
.byte 17, 09, 25, 08, 26

;-----------------------------------------------------------------------------
radarAL:
.byte <radar0A, <(radar0U+RADAR_HEIGHT), <(radar0A+RADAR_HEIGHT), <(radar0U+2*RADAR_HEIGHT)
.byte <radar1A, <(radar1U+RADAR_HEIGHT), <(radar1A+RADAR_HEIGHT), <(radar1U+2*RADAR_HEIGHT)
.byte <radar2A, <(radar2U+RADAR_HEIGHT), <(radar2A+RADAR_HEIGHT), <(radar2U+2*RADAR_HEIGHT)
.byte <radar3A, <(radar3U+RADAR_HEIGHT), <(radar3A+RADAR_HEIGHT), <(radar3U+2*RADAR_HEIGHT)
.byte <radar4A, <(radar4U+RADAR_HEIGHT), <(radar4A+RADAR_HEIGHT), <(radar4U+2*RADAR_HEIGHT)
.byte <radar5A, <(radar5U+RADAR_HEIGHT), <(radar5A+RADAR_HEIGHT), <(radar5U+2*RADAR_HEIGHT)
.byte <radar6A, <(radar6U+RADAR_HEIGHT), <(radar6A+RADAR_HEIGHT), <(radar6U+2*RADAR_HEIGHT)
.byte <radar7A, <(radar7U+RADAR_HEIGHT), <(radar7A+RADAR_HEIGHT), <(radar7U+2*RADAR_HEIGHT)
radarAH:
.byte >radar0A, >(radar0U+RADAR_HEIGHT), >(radar0A+RADAR_HEIGHT), >(radar0U+2*RADAR_HEIGHT)
.byte >radar1A, >(radar1U+RADAR_HEIGHT), >(radar1A+RADAR_HEIGHT), >(radar1U+2*RADAR_HEIGHT)
.byte >radar2A, >(radar2U+RADAR_HEIGHT), >(radar2A+RADAR_HEIGHT), >(radar2U+2*RADAR_HEIGHT)
.byte >radar3A, >(radar3U+RADAR_HEIGHT), >(radar3A+RADAR_HEIGHT), >(radar3U+2*RADAR_HEIGHT)
.byte >radar4A, >(radar4U+RADAR_HEIGHT), >(radar4A+RADAR_HEIGHT), >(radar4U+2*RADAR_HEIGHT)
.byte >radar5A, >(radar5U+RADAR_HEIGHT), >(radar5A+RADAR_HEIGHT), >(radar5U+2*RADAR_HEIGHT)
.byte >radar6A, >(radar6U+RADAR_HEIGHT), >(radar6A+RADAR_HEIGHT), >(radar6U+2*RADAR_HEIGHT)
.byte >radar7A, >(radar7U+RADAR_HEIGHT), >(radar7A+RADAR_HEIGHT), >(radar7U+2*RADAR_HEIGHT)
radarUL:
.byte <radar0U
.byte <radar1U
.byte <radar2U
.byte <radar3U
.byte <radar4U
.byte <radar5U
.byte <radar6U
.byte <radar7U
radarUH:
.byte >radar0U
.byte >radar1U
.byte >radar2U
.byte >radar3U
.byte >radar4U
.byte >radar5U
.byte >radar6U
.byte >radar7U
radarAS:
.byte 4, 3, 2, 1
radarAR:
.byte 1, 1, 0, 0

;-----------------------------------------------------------------------------
missileAL:
.byte <missile0A, <missile1A, <(missile0U + MISSILE_HEIGHT), <(missile1U + MISSILE_HEIGHT)
missileAH:
.byte >missile0A, >missile1A, >(missile0U + MISSILE_HEIGHT), >(missile1U + MISSILE_HEIGHT)
missileUL:
.byte <missile0U, <missile1U
missileUH:
.byte >missile0U, >missile1U

;-----------------------------------------------------------------------------
bombAL:
.byte <bomb0A, <bomb1A
bombAH:
.byte >bomb0A, >bomb1A
bombUL:
.byte <bomb0U, <bomb1U
bombUH:
.byte >bomb0U, >bomb1U
bombH:
.byte 6, 5

;-----------------------------------------------------------------------------
monsterAL:
.byte <monsterA, <(monsterU + MONSTER_HEIGHT), <(monsterA+MONSTER_HEIGHT)
monsterAH:
.byte >monsterA, >(monsterU + MONSTER_HEIGHT), >(monsterA+MONSTER_HEIGHT)
monsterAS:
.byte 2, 2, 1
monsterAR:
.byte 0, 0, 0

;-----------------------------------------------------------------------------
nukeAL:
.byte <nukeA, <(nukeU + NUKE_HEIGHT)
nukeAH:
.byte >nukeA, >(nukeU + NUKE_HEIGHT)
nukeUL:
.byte <nukeU
nukeUH:
.byte >nukeU

;-----------------------------------------------------------------------------
explosionAL:
.byte <explosion0A
.byte <explosion1A
.byte <explosion2A
.byte <explosion3A
explosionAH:
.byte >explosion0A
.byte >explosion1A
.byte >explosion2A
.byte >explosion3A
explosionUL:
.byte <explosion0U
.byte <explosion1U
.byte <explosion2U
.byte <explosion3U
explosionUH:
.byte >explosion0U
.byte >explosion1U
.byte >explosion2U
.byte >explosion3U

;-----------------------------------------------------------------------------
layersH:
.byte >ram_layer0, >ram_layer1

colorLayersH:
.byte >color_layer0, >color_layer1

;-----------------------------------------------------------------------------
; nuke, missile, monster, radar
scoreTable:
.word $0100, $0001, $0002, $0010

;-----------------------------------------------------------------------------
BitMasks:
.byte %00000001
.byte %00000010
.byte %00000100
.byte %00001000
.byte %00010000
.byte %00100000
.byte %01000000
.byte %10000000
.byte %00000011
.byte %00001100
.byte %01100000
.byte %10001110
.byte %11110000
BitMasksEnd:

;-----------------------------------------------------------------------------
; Sprite Information
missile0A:
.byte $10, $10, $10, $38, $38, $7C, $44, $7C, $FE, $C6, $C6, $82, $82, $82
missile0U:
.byte $01, $01, $01, $03, $03, $07, $04, $07, $0F, $0C, $0C, $08, $08, $08
.byte $00, $00, $00, $80, $80, $C0, $40, $C0, $E0, $60, $60, $20, $20, $20
missile1A:
.byte $10, $10, $10, $38, $38, $7C, $44, $7C, $FE, $C6, $D6, $92, $BA, $AA
missile1U:
.byte $01, $01, $01, $03, $03, $07, $04, $07, $0F, $0C, $0D, $09, $0B, $0A
.byte $00, $00, $00, $80, $80, $C0, $40, $C0, $E0, $60, $60, $20, $A0, $A0
radar0A:
.byte $01, $01, $0F, $31, $41, $81, $81, $80, $40, $30, $0F, $04, $0F, $0F, $3F, $3F
.byte $80, $80, $F0, $8C, $82, $81, $81, $01, $02, $0C, $F0, $20, $F0, $F0, $FC, $FC
radar0U:
.byte $00, $00, $00, $03, $04, $08, $08, $08, $04, $03, $00, $00, $00, $00, $03, $03
.byte $18, $18, $FF, $18, $18, $18, $18, $00, $00, $00, $FF, $42, $FF, $FF, $FF, $FF
.byte $00, $00, $00, $C0, $20, $10, $10, $10, $20, $C0, $00, $00, $00, $00, $C0, $C0
radar1A:
.byte $00, $10, $19, $0E, $04, $0B, $13, $20, $21, $3F, $1F, $04, $0F, $0F, $3F, $3F
.byte $00, $60, $90, $08, $08, $18, $38, $70, $E0, $C0, $E0, $20, $F0, $F0, $FC, $FC
radar1U:
.byte $00, $01, $01, $00, $00, $00, $01, $02, $02, $03, $01, $00, $00, $00, $03, $03
.byte $00, $06, $99, $E0, $40, $B1, $33, $07, $1E, $FC, $FE, $42, $FF, $FF, $FF, $FF
.byte $00, $00, $00, $80, $80, $80, $80, $00, $00, $00, $00, $00, $00, $00, $C0, $C0
radar2A:
.byte $00, $00, $18, $0C, $06, $03, $03, $07, $3F, $1F, $0F, $04, $0F, $0F, $3F, $3F
.byte $00, $40, $60, $70, $F0, $F0, $F0, $F0, $E0, $C0, $E0, $20, $F0, $F0, $FC, $FC
radar2U:
.byte $00, $00, $01, $00, $00, $00, $00, $00, $03, $01, $00, $00, $00, $00, $03, $03
.byte $00, $04, $86, $C7, $6F, $3F, $3F, $7F, $FE, $FC, $FE, $42, $FF, $FF, $FF, $FF
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $C0, $C0
radar3A:
.byte $00, $10, $19, $0F, $07, $0F, $1F, $3F, $3F, $3F, $1F, $04, $0F, $0F, $3F, $3F
.byte $00, $60, $F0, $F8, $F8, $F8, $F8, $F0, $E0, $C0, $E0, $20, $F0, $F0, $FC, $FC
radar3U:
.byte $00, $01, $01, $00, $00, $00, $01, $03, $03, $03, $01, $00, $00, $00, $03, $03
.byte $00, $06, $9F, $FF, $7F, $FF, $FF, $FF, $FE, $FC, $FE, $42, $FF, $FF, $FF, $FF
.byte $00, $00, $00, $80, $80, $80, $80, $00, $00, $00, $00, $00, $00, $00, $C0, $C0
radar4A:
.byte $01, $01, $0F, $3F, $7F, $FF, $FF, $FF, $7F, $3F, $0F, $04, $0F, $0F, $3F, $3F
.byte $80, $80, $F0, $FC, $FE, $FF, $FF, $FF, $FE, $FC, $F0, $20, $F0, $F0, $FC, $FC
radar4U:
.byte $00, $00, $00, $03, $07, $0F, $0F, $0F, $07, $03, $00, $00, $00, $00, $03, $03
.byte $18, $18, $FF, $FF, $FF, $FF, $FF, $FF, $FF, $FF, $FF, $42, $FF, $FF, $FF, $FF
.byte $00, $00, $00, $C0, $E0, $F0, $F0, $F0, $E0, $C0, $00, $00, $00, $00, $C0, $C0
radar5A:
.byte $00, $06, $0F, $1F, $1F, $1F, $1F, $0F, $07, $03, $07, $04, $0F, $0F, $3F, $3F
.byte $00, $08, $98, $F0, $E0, $F0, $F8, $FC, $FC, $FC, $F8, $20, $F0, $F0, $FC, $FC
radar5U:
.byte $00, $00, $00, $01, $01, $01, $01, $00, $00, $00, $00, $00, $00, $00, $03, $03
.byte $00, $60, $F9, $FF, $FE, $FF, $FF, $FF, $7F, $3F, $7F, $42, $FF, $FF, $FF, $FF
.byte $00, $80, $80, $00, $00, $00, $80, $C0, $C0, $C0, $80, $00, $00, $00, $C0, $C0
radar6A:
.byte $00, $02, $06, $0E, $0F, $0F, $0F, $0F, $07, $03, $07, $04, $0F, $0F, $3F, $3F
.byte $00, $00, $18, $30, $60, $C0, $C0, $E0, $FC, $F8, $F0, $20, $F0, $F0, $FC, $FC
radar6U:
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $03, $03
.byte $00, $20, $61, $E3, $F6, $FC, $FC, $FE, $7F, $3F, $7F, $42, $FF, $FF, $FF, $FF
.byte $00, $00, $80, $00, $00, $00, $00, $00, $C0, $80, $00, $00, $00, $00, $C0, $C0
radar7A:
.byte $00, $06, $09, $10, $10, $18, $1C, $0E, $07, $03, $07, $04, $0F, $0F, $3F, $3F
.byte $00, $08, $98, $70, $20, $D0, $C8, $04, $84, $FC, $F8, $20, $F0, $F0, $FC, $FC
radar7U:
.byte $00, $00, $00, $01, $01, $01, $01, $00, $00, $00, $00, $00, $00, $00, $03, $03
.byte $00, $60, $99, $07, $02, $8D, $CC, $E0, $78, $3F, $7F, $42, $FF, $FF, $FF, $FF
.byte $00, $80, $80, $00, $00, $00, $80, $40, $40, $C0, $80, $00, $00, $00, $C0, $C0
explosion0A:
.byte $20, $30, $01, $00, $00, $93, $07, $07, $07, $07, $10, $00, $0C, $8C, $80, $00
.byte $00, $00, $00, $00, $16, $00, $C0, $E0, $E8, $80, $80, $10, $00, $00, $88, $00
explosion0U:
.byte $02, $03, $00, $00, $00, $09, $00, $00, $00, $00, $01, $00, $00, $08, $08, $00
.byte $00, $00, $10, $00, $01, $30, $7C, $7E, $7E, $78, $08, $01, $C0, $C0, $08, $00
.byte $00, $00, $00, $00, $60, $00, $00, $00, $80, $00, $00, $00, $00, $00, $80, $00
explosion1A:
.byte $60, $20, $00, $00, $23, $09, $0B, $06, $06, $15, $1A, $00, $00, $06, $28, $00
.byte $00, $86, $00, $09, $00, $60, $D0, $90, $60, $40, $80, $20, $08, $00, $00, $41
explosion1U:
.byte $06, $02, $00, $00, $02, $00, $00, $00, $00, $01, $01, $00, $00, $00, $02, $00
.byte $00, $08, $00, $00, $30, $96, $BD, $69, $66, $54, $A8, $02, $00, $60, $80, $04
.byte $00, $60, $00, $90, $00, $00, $00, $00, $00, $00, $00, $00, $80, $00, $00, $10
explosion2A:
.byte $40, $00, $04, $81, $21, $08, $08, $24, $04, $48, $10, $51, $00, $08, $20, $90
.byte $41, $00, $00, $08, $20, $00, $50, $80, $20, $06, $80, $08, $00, $00, $00, $01
explosion2U:
.byte $04, $00, $00, $08, $02, $00, $00, $02, $00, $04, $01, $05, $00, $00, $02, $09
.byte $04, $00, $40, $10, $12, $80, $85, $48, $42, $80, $08, $10, $00, $80, $00, $00
.byte $10, $00, $00, $80, $00, $00, $00, $00, $00, $60, $00, $80, $00, $00, $00, $10
explosion3A:
.byte $00, $40, $04, $81, $00, $20, $00, $80, $00, $81, $00, $00, $04, $20, $00, $80
.byte $00, $01, $41, $00, $00, $00, $00, $06, $00, $00, $08, $00, $80, $01, $00, $00
explosion3U:
.byte $00, $04, $00, $08, $00, $02, $00, $08, $00, $08, $00, $00, $00, $02, $00, $08
.byte $00, $00, $44, $10, $00, $00, $00, $00, $00, $10, $00, $00, $48, $00, $00, $00
.byte $00, $10, $10, $00, $00, $00, $00, $60, $00, $00, $80, $00, $00, $10, $00, $00
monsterA:
.byte $80, $DE, $FF, $7F, $FF, $DE, $CC, $CC, $ED, $7F, $3F, $33, $1E
.byte $40, $C0, $C0, $80, $C0, $C0, $C0, $C0, $C0, $80, $00, $00, $00
monsterU:
.byte $08, $0D, $0F, $07, $0F, $0D, $0C, $0C, $0E, $07, $03, $03, $01
.byte $04, $EC, $FC, $F8, $FC, $EC, $CC, $CC, $DC, $F8, $F0, $30, $E0
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00
nukeA:
.byte $18, $24, $5A, $5A, $24, $18, $24, $FF
nukeU:
.byte $01, $02, $05, $05, $02, $01, $02, $0F
.byte $80, $40, $A0, $A0, $40, $80, $40, $F0
bomb0A:
.byte $88, $A8, $F8, $70, $20, $20
bomb0U:
.byte $08, $0A, $0F, $07, $02, $02
.byte $80, $80, $80, $00, $00, $00
bomb1A:
.byte $E0, $30, $7C, $30, $E0, $00
bomb1U:
.byte $0E, $03, $07, $03, $0E, $00
.byte $00, $00, $C0, $00, $00, $00
shipA:
.byte $FF, $78, $3E, $1F, $0F, $07, $07, $07, $07, $0F, $1F, $3F
.byte $C0, $00, $00, $80, $F0, $18, $8F, $FF, $FF, $F0, $80, $FE
.byte $00, $00, $00, $00, $00, $00, $00, $F0, $80, $00, $00, $00
shipU:
.byte $0F, $07, $03, $01, $00, $00, $00, $00, $00, $00, $01, $03
.byte $FC, $80, $E0, $F8, $FF, $71, $78, $7F, $7F, $FF, $F8, $FF
.byte $00, $00, $00, $00, $00, $80, $F0, $FF, $F8, $00, $00, $E0
