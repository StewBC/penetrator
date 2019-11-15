;-----------------------------------------------------------------------------
; rodata.inc
; Part of penetrator, the zx spectrum game, made for commander x16
;
; Stefan Wessels, 2019
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
.segment "RODATA"

;-----------------------------------------------------------------------------
; the lo byte for the memory at the start of every screen row
rowL:
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
.byte $00, $50, $A0, $F0, $40, $90, $E0, $30, $80, $D0, $20, $70, $C0, $10, $60, $B0
 

;-----------------------------------------------------------------------------
; the hi byte for the memory at the start of every screen row
rowH: 
.byte $00, $00, $00, $00, $01, $01, $01, $02, $02, $02, $03, $03, $03, $04, $04, $04
.byte $05, $05, $05, $05, $06, $06, $06, $07, $07, $07, $08, $08, $08, $09, $09, $09
.byte $0A, $0A, $0A, $0A, $0B, $0B, $0B, $0C, $0C, $0C, $0D, $0D, $0D, $0E, $0E, $0E
.byte $0F, $0F, $0F, $0F, $10, $10, $10, $11, $11, $11, $12, $12, $12, $13, $13, $13
.byte $14, $14, $14, $14, $15, $15, $15, $16, $16, $16, $17, $17, $17, $18, $18, $18
.byte $19, $19, $19, $19, $1A, $1A, $1A, $1B, $1B, $1B, $1C, $1C, $1C, $1D, $1D, $1D
.byte $1E, $1E, $1E, $1E, $1F, $1F, $1F, $20, $20, $20, $21, $21, $21, $22, $22, $22
.byte $23, $23, $23, $23, $24, $24, $24, $25, $25, $25, $26, $26, $26, $27, $27, $27
.byte $28, $28, $28, $28, $29, $29, $29, $2A, $2A, $2A, $2B, $2B, $2B, $2C, $2C, $2C
.byte $2D, $2D, $2D, $2D, $2E, $2E, $2E, $2F, $2F, $2F, $30, $30, $30, $31, $31, $31
.byte $32, $32, $32, $32, $33, $33, $33, $34, $34, $34, $35, $35, $35, $36, $36, $36
.byte $37, $37, $37, $37, $38, $38, $38, $39, $39, $39, $3A, $3A, $3A, $3B, $3B, $3B
.byte $3C, $3C, $3C, $3C, $3D, $3D, $3D, $3E, $3E, $3E, $3F, $3F, $3F, $40, $40, $40
.byte $41, $41, $41, $41, $42, $42, $42, $43, $43, $43, $44, $44, $44, $45, $45, $45
.byte $46, $46, $46, $46, $47, $47, $47, $48, $48, $48, $49, $49, $49, $4A, $4A, $4A

;-----------------------------------------------------------------------------
; rgb or in this case gbr - Green, Blue, Red packed in nibbles as GB, 0R for bits bits 00,01,10,11
gamePalette:
.byte $00, $00,   $F6, $0F,   $0F, $0F,   $FF, $00    ; 0 - black, yellow, purple, cyan  - (Stage 1)
.byte $0F, $00,   $FF, $0F,   $F0, $0F,   $F0, $00    ; 1 - blue , white , yellow, green - (Stage 2)
.byte $B5, $03,   $00, $00,   $0F, $00,   $00, $00    ; 2 - green, black , blue  , black - (Stage 3)
.byte $ED, $03,   $00, $00,   $0F, $00,   $00, $0F    ; 3 - cyan , black , blue  , red   - (Stage 4)
.byte $00, $0F,   $00, $00,   $0F, $00,   $FF, $0F    ; 4 - red  , black , blue  , white - (Stage 5)
.byte $00, $00,   $88, $08,   $C8, $0C,   $FF, $0F    ; 5 - black, gray  , olive?, white - (UI)
.byte $00, $00,   $ff, $0f,   $00, $0f,   $ff, $00    ; 6 - black, white , red   , cyan  - (Title GFX 1 4bpp)
.byte $f0, $00,   $f0, $00,   $0f, $00,   $00, $00    ; 7 - green, green , blue  , black - (Title GFX 2 4bpp)
.byte $FF, $0F,   $00, $00,   $00, $00,   $00, $00    ; 8 - white, black , black , black - (used with #5 to invert the bonus)
gamePaletteEnd:

;-----------------------------------------------------------------------------
; Offsets for printing the high score table on the title screen
scoreTextOffset:
.byte textHighScore1-textHS
.byte textHighScore2-textHS
.byte textHighScore3-textHS
.byte textHighScore4-textHS
.byte textHighScore5-textHS
scoreTextPosX:
.byte 28, 12, 44, 10, 46
scoreTextPosY:
.byte 8 , 16, 16, 24, 24
scorePosX:
.byte 42, 26, 58, 24, 60

;-----------------------------------------------------------------------------
radarColL:
.byte <radar1, <(radar1+RADAR_HEIGHT), <(radar1+2*RADAR_HEIGHT), <(radar1+3*RADAR_HEIGHT)
.byte <radar2, <(radar2+RADAR_HEIGHT), <(radar2+2*RADAR_HEIGHT), <(radar2+3*RADAR_HEIGHT)
.byte <radar3, <(radar3+RADAR_HEIGHT), <(radar3+2*RADAR_HEIGHT), <(radar3+3*RADAR_HEIGHT)
.byte <radar4, <(radar4+RADAR_HEIGHT), <(radar4+2*RADAR_HEIGHT), <(radar4+3*RADAR_HEIGHT)
.byte <radar5, <(radar5+RADAR_HEIGHT), <(radar5+2*RADAR_HEIGHT), <(radar5+3*RADAR_HEIGHT)
.byte <radar6, <(radar6+RADAR_HEIGHT), <(radar6+2*RADAR_HEIGHT), <(radar6+3*RADAR_HEIGHT)
.byte <radar7, <(radar7+RADAR_HEIGHT), <(radar7+2*RADAR_HEIGHT), <(radar7+3*RADAR_HEIGHT)
.byte <radar8, <(radar8+RADAR_HEIGHT), <(radar8+2*RADAR_HEIGHT), <(radar8+3*RADAR_HEIGHT)
radarColH:
.byte >radar1, >(radar1+RADAR_HEIGHT), >(radar1+2*RADAR_HEIGHT), >(radar1+3*RADAR_HEIGHT)
.byte >radar2, >(radar2+RADAR_HEIGHT), >(radar2+2*RADAR_HEIGHT), >(radar2+3*RADAR_HEIGHT)
.byte >radar3, >(radar3+RADAR_HEIGHT), >(radar3+2*RADAR_HEIGHT), >(radar3+3*RADAR_HEIGHT)
.byte >radar4, >(radar4+RADAR_HEIGHT), >(radar4+2*RADAR_HEIGHT), >(radar4+3*RADAR_HEIGHT)
.byte >radar5, >(radar5+RADAR_HEIGHT), >(radar5+2*RADAR_HEIGHT), >(radar5+3*RADAR_HEIGHT)
.byte >radar6, >(radar6+RADAR_HEIGHT), >(radar6+2*RADAR_HEIGHT), >(radar6+3*RADAR_HEIGHT)
.byte >radar7, >(radar7+RADAR_HEIGHT), >(radar7+2*RADAR_HEIGHT), >(radar7+3*RADAR_HEIGHT)
.byte >radar8, >(radar8+RADAR_HEIGHT), >(radar8+2*RADAR_HEIGHT), >(radar8+3*RADAR_HEIGHT)

missileColL:
.byte <missile1, <(missile1+MISSILE_HEIGHT)
.byte <missile2, <(missile2+MISSILE_HEIGHT)
missileColH:
.byte >missile1, >(missile1+MISSILE_HEIGHT)
.byte >missile2, >(missile2+MISSILE_HEIGHT)

explosionColL:
.byte <explosion1
.byte <explosion2
.byte <explosion3
.byte <explosion4
explosionColH:
.byte >explosion1
.byte >explosion2
.byte >explosion3
.byte >explosion4

monsterColL:
.byte <monster, <(monster+MONSTER_HEIGHT), <(monster+2*MONSTER_HEIGHT)
monsterColH:
.byte >monster, >(monster+MONSTER_HEIGHT), >(monster+2*MONSTER_HEIGHT)

nukeColL:
.byte <nuke, <(nuke+NUKE_HEIGHT)
nukeColH:
.byte >nuke, >(nuke+NUKE_HEIGHT)

;-----------------------------------------------------------------------------
layersL:
.byte <ram_layer0, <ram_layer1
layersH:
.byte >ram_layer0, >ram_layer1

;-----------------------------------------------------------------------------
; nuke, missile, monster, radar
scoreTable:
.word $0100, $0001, $0002, $0010

;-----------------------------------------------------------------------------
Bit1Mask:
.byte %00000001
Bit2Mask:
.byte %00000010
Bit3Mask:
.byte %00000100
Bit4Mask:
.byte %00001000
Bit5Mask:
.byte %00010000
Bit6Mask:
.byte %00100000
Bit7Mask:
.byte %01000000
Bit8Mask:
.byte %10000000
Bit12Mask:
.byte %00000011
Bit34Mask:
.byte %00001100
Bit8432Mask:
.byte %10001110
Bit8765Mask:
.byte %11110000

;-----------------------------------------------------------------------------
; 2bpp = 4 colour, but 00 is transparent leaving 3 more colours
; Missile 01
; Radar 10
; Explosion 11
; monster 11
; Nuke 10
; 
; These next 3 have to be 11 because they need to collide (and <> 0) with
; the other elements.  If the ship was, let's say, 01 then the ship would
; perfectly go through a radar (10) with no collision.
;
; Bomb 11
; Ship 11
; Bullets don't have a sprite but are 11
; 
; The data is in column format (top row of numbers are the left column of the sprite)

.align $0100
spriteData:

missile1: ; bits 01
.byte $01, $01, $01, $05, $05, $15, $10, $15, $55, $50, $50, $40, $40, $40
.byte $00, $00, $00, $40, $40, $50, $10, $50, $54, $14, $14, $04, $04, $04

missile2:
.byte $01, $01, $01, $05, $05, $15, $10, $15, $55, $50, $51, $41, $45, $44
.byte $00, $00, $00, $40, $40, $50, $10, $50, $54, $14, $14, $04, $44, $44

radar1: ; bits 10
.byte $00, $00, $00, $0A, $20, $80, $80, $80, $20, $0A, $00, $00, $00, $00, $0A, $0A
.byte $02, $02, $AA, $02, $02, $02, $02, $00, $00, $00, $AA, $20, $AA, $AA, $AA, $AA
.byte $80, $80, $AA, $80, $80, $80, $80, $00, $00, $00, $AA, $08, $AA, $AA, $AA, $AA
.byte $00, $00, $00, $A0, $08, $02, $02, $02, $08, $A0, $00, $00, $00, $00, $A0, $A0

radar2:
.byte $00, $02, $02, $00, $00, $00, $02, $08, $08, $0A, $02, $00, $00, $00, $0A, $0A
.byte $00, $00, $82, $A8, $20, $8A, $0A, $00, $02, $AA, $AA, $20, $AA, $AA, $AA, $AA
.byte $00, $28, $82, $00, $00, $02, $0A, $2A, $A8, $A0, $A8, $08, $AA, $AA, $AA, $AA
.byte $00, $00, $00, $80, $80, $80, $80, $00, $00, $00, $00, $00, $00, $00, $A0, $A0

radar3:
.byte $00, $00, $02, $00, $00, $00, $00, $00, $0A, $02, $00, $00, $00, $00, $0A, $0A
.byte $00, $00, $80, $A0, $28, $0A, $0A, $2A, $AA, $AA, $AA, $20, $AA, $AA, $AA, $AA
.byte $00, $20, $28, $2A, $AA, $AA, $AA, $AA, $A8, $A0, $A8, $08, $AA, $AA, $AA, $AA
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $A0, $A0

radar4:
.byte $00, $02, $02, $00, $00, $00, $02, $0A, $0A, $0A, $02, $00, $00, $00, $0A, $0A
.byte $00, $00, $82, $AA, $2A, $AA, $AA, $AA, $AA, $AA, $AA, $20, $AA, $AA, $AA, $AA
.byte $00, $28, $AA, $AA, $AA, $AA, $AA, $AA, $A8, $A0, $A8, $08, $AA, $AA, $AA, $AA
.byte $00, $00, $00, $80, $80, $80, $80, $00, $00, $00, $00, $00, $00, $00, $A0, $A0

radar5:
.byte $00, $00, $00, $0A, $2A, $AA, $AA, $AA, $2A, $0A, $00, $00, $00, $00, $0A, $0A
.byte $02, $02, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $20, $AA, $AA, $AA, $AA
.byte $80, $80, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $AA, $08, $AA, $AA, $AA, $AA
.byte $00, $00, $00, $A0, $A8, $AA, $AA, $AA, $A8, $A0, $00, $00, $00, $00, $A0, $A0

radar6:
.byte $00, $00, $00, $02, $02, $02, $02, $00, $00, $00, $00, $00, $00, $00, $0A, $0A
.byte $00, $28, $AA, $AA, $AA, $AA, $AA, $AA, $2A, $0A, $2A, $20, $AA, $AA, $AA, $AA
.byte $00, $00, $82, $AA, $A8, $AA, $AA, $AA, $AA, $AA, $AA, $08, $AA, $AA, $AA, $AA
.byte $00, $80, $80, $00, $00, $00, $80, $A0, $A0, $A0, $80, $00, $00, $00, $A0, $A0

radar7:
.byte $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $00, $0A, $0A
.byte $00, $08, $28, $A8, $AA, $AA, $AA, $AA, $2A, $0A, $2A, $20, $AA, $AA, $AA, $AA
.byte $00, $00, $02, $0A, $28, $A0, $A0, $A8, $AA, $AA, $AA, $08, $AA, $AA, $AA, $AA
.byte $00, $00, $80, $00, $00, $00, $00, $00, $A0, $80, $00, $00, $00, $00, $A0, $A0

radar8:
.byte $00, $00, $00, $02, $02, $02, $02, $00, $00, $00, $00, $00, $00, $00, $0A, $0A
.byte $00, $28, $82, $00, $00, $80, $A0, $A8, $2A, $0A, $2A, $20, $AA, $AA, $AA, $AA
.byte $00, $00, $82, $2A, $08, $A2, $A0, $00, $80, $AA, $AA, $08, $AA, $AA, $AA, $AA
.byte $00, $80, $80, $00, $00, $00, $80, $20, $20, $A0, $80, $00, $00, $00, $A0, $A0

explosion1: ; bits 11
.byte $0C, $0F, $00, $00, $00, $C3, $00, $00, $00, $00, $03, $00, $00, $C0, $C0, $00
.byte $00, $00, $03, $00, $00, $0F, $3F, $3F, $3F, $3F, $00, $00, $F0, $F0, $00, $00
.byte $00, $00, $00, $00, $03, $00, $F0, $FC, $FC, $C0, $C0, $03, $00, $00, $C0, $00
.byte $00, $00, $00, $00, $3C, $00, $00, $00, $C0, $00, $00, $00, $00, $00, $C0, $00

explosion2:
.byte $3C, $0C, $00, $00, $0C, $00, $00, $00, $00, $03, $03, $00, $00, $00, $0C, $00
.byte $00, $00, $00, $00, $0F, $C3, $CF, $3C, $3C, $33, $CC, $00, $00, $3C, $C0, $00
.byte $00, $C0, $00, $00, $00, $3C, $F3, $C3, $3C, $30, $C0, $0C, $00, $00, $00, $30
.byte $00, $3C, $00, $C3, $00, $00, $00, $00, $00, $00, $00, $00, $C0, $00, $00, $03

explosion3:
.byte $30, $00, $00, $C0, $0C, $00, $00, $0C, $00, $30, $03, $33, $00, $00, $0C, $C3
.byte $00, $00, $30, $03, $03, $C0, $C0, $30, $30, $C0, $00, $03, $00, $C0, $00, $00
.byte $30, $00, $00, $00, $0C, $00, $33, $C0, $0C, $00, $C0, $00, $00, $00, $00, $00
.byte $03, $00, $00, $C0, $00, $00, $00, $00, $00, $3C, $00, $C0, $00, $00, $00, $03

explosion4:
.byte $00, $30, $00, $C0, $00, $0C, $00, $C0, $00, $C0, $00, $00, $00, $0C, $00, $C0
.byte $00, $00, $30, $03, $00, $00, $00, $00, $00, $03, $00, $00, $30, $00, $00, $00
.byte $00, $00, $30, $00, $00, $00, $00, $00, $00, $00, $00, $00, $C0, $00, $00, $00
.byte $00, $03, $03, $00, $00, $00, $00, $3C, $00, $00, $C0, $00, $00, $03, $00, $00

monster: ; bits 11
.byte $C0, $F3, $FF, $3F, $FF, $F3, $F0, $F0, $FC, $3F, $0F, $0F, $03
.byte $00, $FC, $FF, $FF, $FF, $FC, $F0, $F0, $F3, $FF, $FF, $0F, $FC
.byte $30, $F0, $F0, $C0, $F0, $F0, $F0, $F0, $F0, $C0, $00, $00, $00

nuke: ; bits 10
.byte $02, $08, $22, $22, $08, $02, $08, $AA
.byte $80, $20, $88, $88, $20, $80, $20, $AA

bomb1: ; bits 11
.byte $FC, $0F, $3F, $0F, $FC, $00
.byte $00, $00, $F0, $00, $00, $00

bomb2:
.byte $C0, $CC, $FF, $3F, $0C, $0C
.byte $C0, $C0, $C0, $00, $00, $00

ship: ; bits 11
.byte $FF, $3F, $0F, $03, $00, $00, $00, $00, $00, $00, $03, $0F
.byte $FF, $C0, $FC, $FF, $FF, $3F, $3F, $3F, $3F, $FF, $FF, $FF
.byte $F0, $00, $00, $C0, $FF, $03, $C0, $FF, $FF, $FF, $C0, $FF
.byte $00, $00, $00, $00, $00, $C0, $FF, $FF, $FF, $00, $00, $FC
.byte $00, $00, $00, $00, $00, $00, $00, $FF, $C0, $00, $00, $00
spriteDataEnd:
