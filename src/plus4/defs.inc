;-----------------------------------------------------------------------------
; defs.inc
; Part of penetrator, the zx spectrum game, made for Commodore Plus4
;
; Stefan Wessels, 2019, 2023
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
; System locations
PNBUFR             := $025E
DOSF1L             := $026E
SETLFS             := $FFBA
SETNAM             := $FFBD
LOADSP             := $FFD5
SAVESP             := $FFD8
GETIN              := $FFE4
RESET              := $FFF6
NDX                := $00EF

ram_layer0         := $A000                      ; HGR Pages
ram_layer1         := $C000
luma_layer0        := $0800
color_layer0       := luma_layer0 + $0400
.import               __COLLYR1_LOAD__
luma_layer1        := __COLLYR1_LOAD__
color_layer1       := luma_layer1 + $0400

TED_t1_lo           = $FF00                      ; Timer #1 low
TED_t1_hi           = $FF01                      ; Timer #1 high
TED_t2_lo           = $FF02                      ; Timer #2 low
TED_t2_hi           = $FF03                      ; Timer #2 high
TED_t3_lo           = $FF04                      ; Timer #3 low
TED_t3_hi           = $FF05                      ; Timer #3 high
TED_vscroll         = $FF06                      ; Vertical scroll control
TED_hscroll         = $FF07                      ; Horizontal scroll control
TED_kbdlatch        = $FF08                      ; Keyboard latch
TED_irr             = $FF09                      ; Interrupt request register
TED_imr             = $FF0A                      ; Interrupt mask register
TED_irq_rasterline  = $FF0B                      ; Interrupt rasterline
TED_cursor_hi       = $FF0C                      ; Cursor position high
TED_cursor_lo       = $FF0D                      ; Cursor position low
TED_snd1_freq_lo    = $FF0E                      ; Channel #1 frequency
TED_snd2_freq_lo    = $FF0F                      ; Channel #2 frequency low
TED_snd2_freq_hi    = $FF10                      ; Channel #2 frequency high
TED_snd_ctrl        = $FF11                      ; Sound control
TED_misc            = $FF12                      ; Channel #1 frequency high and more
TED_char_addr       = $FF13                      ; Character data base address
TED_video_addr      = $FF14                      ; Video memory base address
TED_bgcolor         = $FF15                      ; Background color
TED_color1          = $FF16                      ; Color register #1
TED_color2          = $FF17                      ; Color register #2
TED_color3          = $FF18                      ; Color register #3
TED_bordercolor     = $FF19                      ; Border color
TED_bmap_reload_hi  = $FF1A                      ; Bitmap reload bits 8+9
TED_bmap_reload_lo  = $FF1B                      ; Bitmap reload bits 0-7
TED_rasterline_hi   = $FF1C                      ; Current rasterline bit 8
TED_rasterline_lo   = $FF1D                      ; Current rasterline bits 0-7
TED_rastercolumn    = $FF1E                      ; Current rastercolumn
TED_cursor_blink    = $FF1F                      ; Cursor blink attribute
TED_enable_rom      = $FF3E                      ; Write enables ROM
TED_enable_ram      = $FF3F                      ; Write enables RAM

; Color attributes
CATTR_LUMA0         = $00
CATTR_LUMA1         = $10
CATTR_LUMA2         = $20
CATTR_LUMA3         = $30
CATTR_LUMA4         = $40
CATTR_LUMA5         = $50
CATTR_LUMA6         = $60
CATTR_LUMA7         = $70
CATTR_BLINK         = $80

; Base colors
BCOLOR_BLACK        = $00
BCOLOR_WHITE        = $01
BCOLOR_RED          = $02
BCOLOR_CYAN         = $03
BCOLOR_PURPLE       = $04
BCOLOR_GREEN        = $05
BCOLOR_BLUE         = $06
BCOLOR_YELLOW       = $07
BCOLOR_ORANGE       = $08
BCOLOR_BROWN        = $09
BCOLOR_LEMON        = $0A                        ; What's that color?
BCOLOR_LIGHTVIOLET  = $0B
BCOLOR_BLUEGREEN    = $0C
BCOLOR_LIGHTBLUE    = $0D
BCOLOR_DARKBLUE     = $0E
BCOLOR_LIGHTGREEN   = $0F

;-----------------------------------------------------------------------------
; self-modifying address marker
PLACEHOLDER         = $FFFF

;-----------------------------------------------------------------------------
; modes
GAME_MODE_PLAY      = $00
GAME_MODE_TRAIN     = $01
GAME_MODE_EDIT      = $02

BRUSH_TERRAIN       = $00
BRUSH_ENEMIES       = $01

;-----------------------------------------------------------------------------
; digital input constants
KEY_UP              = %00000001
KEY_DOWN            = %00000010
KEY_LEFT            = %00000100
KEY_RIGHT           = %00001000
KEY_START           = %00010000
KEY_SELECT          = %00100000
KEY_FIRE            = %01000000
KEY_BOMB            = %10000000

;-----------------------------------------------------------------------------
; game constants
XINSET              = 4                          ; By how many BYTE cols the display is offset into X
PENXSIZE            = (80 - (4 * XINSET))        ; columns on screen (1 BYTE col=2 game cols)
; YSIZE             = 192                                                           ; lines on screen

WORLD_START         = $08                        ; top line where world is drawn
WORLD_END           = $B3                        ; last line where world is drawn
BUFLENGTH           = $100                       ; size for buffers that hold enemies

NUM_LIVES           = 5                          ; How many lives to start with
NUM_STAGES          = 5
NUM_BOMBS           = 2                          ; How many bombs the player can drop
NUM_INFLIGHT        = 3                          ; How many missiles can be in-flight at once
NUM_SKIP_MONST      = 4                          ; How many rockets to skip before making one a monster

DANGER_FONT         = 4                          ; Number of font characters that make one filled column
DANGER_LENGTH       = ((textEnd-1)-textDangerBar); how many characters in the danger column (skip trailing 0)
DANGER_TICKS        = ((((worldDataEnd-worldDataStart) / 3) / DANGER_LENGTH) / DANGER_FONT)

; audio constants
AUDIO_BOMB_DROP     = %01000000                  ; Releasing a bomb
AUDIO_FIRE          = %00100000                  ; Firing the gun
AUDIO_EXPLOSION     = %00010000                  ; An enemy exploding
AUDIO_MOTOR_FWD     = %00001000                  ; Speeding up
AUDIO_MOTOR_REW     = %00000100                  ; slowing down
AUDIO_MOTOR_PLAY    = %00000010                  ; flying at a constant speed
AUDIO_UI_TICK       = %00000001                  ; UI selection

; The enemyBuffer is filled with these values, which break down as:
;
; Bits 1 & 2    - Type. 0 - monster, 1 - missile, 2 - radar & 3 - nuke
; Bits 3 & 4    - Column of sprite - Missile 2 wide, radar 4 wide, etc.
; Bits 5, 6 & 7 - Animation frame number, 0 - 7 (Radar has 8 frames)
; Bit 8         - 1 - Flying, 0 - on ground
;
; For monsters, Bits 5, 6 and 7 mean the following:
; Monster Bit 5 - Direction - 0 is up and 1 is down
; Monster Bit 6 & 7 - The delay counter while it is stopped. 0 - moving, <> 0 paused
;
; All 0 means empty, no enemy at that location

SPR_MONSTER0        = %10000000                  ; enemy buffer mask MONSTER left
SPR_MONSTER1        = %10000100                  ; enemy buffer mask MONSTER col 2
SPR_MONSTER2        = %10001000                  ; enemy buffer mask MONSTER right
SPR_MISSILE0        = %00000001                  ; enemy buffer mask missile left
SPR_MISSILE1        = %00000101                  ; enemy buffer mask missile right
SPR_RADAR0          = %00000010                  ; enemy buffer mask radar left
SPR_RADAR1          = %00000110                  ; enemy buffer mask radar col 2
SPR_RADAR2          = %00001010                  ; enemy buffer mask radar col 3
SPR_RADAR3          = %00001110                  ; enemy buffer mask radar right
SPR_NUKE0           = %00000011                  ; enemy buffer mask nuke left
SPR_NUKE1           = %00000111                  ; enemy buffer mask nuke right

MONSTER_HEIGHT      = 13                         ; rows in monster sprite
MONSTER_WIDTH       = 3                          ; cols in monster sprite
MONSTER_SPEED       = 4                          ; speed at which monster moves (in rows)

MISSILE_HEIGHT      = 14                         ; rows in missile sprite

RADAR_HEIGHT        = 16                         ; rows in radar sprite

NUKE_HEIGHT         = 8                          ; rows in nuke sprite

EXPLOSION_HEIGHT    = 16                         ; rows in explosion sprite

BOMB_HEIGHT         = 6                          ; rows in bomb sprite
BOMB_FRWRD_FRMS     = 6                          ; horz bomb travel duration

SHIP_HEIGHT         = 12                         ; rows in player ship sprite
SHIP_WIDTH          = 4                          ; cols in player ship sprite
SHIP_START          = 16                         ; height above world where ship starts
