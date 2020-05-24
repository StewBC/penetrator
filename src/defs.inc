;-----------------------------------------------------------------------------
; defs.inc
; Part of penetrator, the zx spectrum game, made for commander x16
;
; Stefan Wessels, 2019
; This is free and unencumbered software released into the public domain.

;-----------------------------------------------------------------------------
; VRAM locations
ram_layer0       = $0000                        ; after title, layer 0 memory here
ram_layer1       = $5000                        ; after title, layer 1 memory here
gfx_layer1       = $0000                        ; the 4bpp title screen memory start

;-----------------------------------------------------------------------------
; System locations
; These are for r37 - find them in kernal.sym in the emulator folder
NDX              = $A00A
TIME_1           = $A038                        ; TIMER is at $A037 (bank 0) - +1 is APPROX 3.75 sec/tick
TIME_2           = $A039                        ; +2 is the jiffy counter (also at $A03D?)
JOYGET           = $FF56
SETLFS           = $FFBA
SETNAM           = $FFBD
LOAD             = $FFD5
SAVE             = $FFD8
GETIN            = $FFE4

;-----------------------------------------------------------------------------
; ui constants
UI_PALETTE       = $05                          ; index in rodata:gamePalette
HUD_TEXT_MASK    = $ff

;-----------------------------------------------------------------------------
; modes
GAME_MODE_PLAY   = $00
GAME_MODE_TRAIN  = $01
GAME_MODE_EDIT   = $02

BRUSH_TERRAIN    = $00
BRUSH_ENEMIES    = $01

;-----------------------------------------------------------------------------
; game constants
XSIZE            = 80                           ; columns on screen (80 * 4 pixels is 320 @ 2bpp)
YSIZE            = 240                          ; lines on screen
HSCALE           = $40
VSCALE_UI        = $40
VSCALE_GAME      = $34
VSCALE_GFX       = $35

WORLD_START      = $08                          ; top line where world is drawn
WORLD_END        = $B3                          ; last line where world is drawn
BUFLENGTH        = $100                         ; size for buffers that hold enemies

NUM_LIVES        = 5                            ; How many lives to start with
NUM_STAGES       = 5
NUM_BOMBS        = 2                            ; How many bombs the player can drop
NUM_INFLIGHT     = 3                            ; How many missiles can be in-flight at once
NUM_SKIP_MONST   = 4

TIME_WAIT        = 2                            ; TIMEs to wait before next frame (20fps)

DANGER_FONT      = 4                            ; Number of font characters that make one filled column
DANGER_LENGTH    = ((textEnd-1)-textDangerBar)  ; how many characters in the danger column (skip trailing 0)
DANGER_TICKS     = ((((worldDataEnd-worldDataStart) / 3) / DANGER_LENGTH) / DANGER_FONT)

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

SPR_MONSTER0     = %10000000                    ; enemy buffer mask MONSTER left
SPR_MONSTER1     = %10000100                    ; enemy buffer mask MONSTER col 2
SPR_MONSTER2     = %10001000                    ; enemy buffer mask MONSTER right
SPR_MISSILE0     = %00000001                    ; enemy buffer mask missile left
SPR_MISSILE1     = %00000101                    ; enemy buffer mask missile right
SPR_RADAR0       = %00000010                    ; enemy buffer mask radar left
SPR_RADAR1       = %00000110                    ; enemy buffer mask radar col 2
SPR_RADAR2       = %00001010                    ; enemy buffer mask radar col 3
SPR_RADAR3       = %00001110                    ; enemy buffer mask radar right
SPR_NUKE0        = %00000011                    ; enemy buffer mask nuke left
SPR_NUKE1        = %00000111                    ; enemy buffer mask nuke right

MONSTER_HEIGHT   = 13                           ; rows in monster sprite
MONSTER_WIDTH    = 3                            ; cols in monster sprite
MONSTER_SPEED    = 4                            ; speed at which monster moves (in rows)

MISSILE_HEIGHT   = 14                           ; rows in missile sprite
MISSILE_WIDTH    = 2                            ; cols in missile sprite

RADAR_HEIGHT     = 16                           ; rows in radar sprite
RADAR_WIDTH      = 4                            ; cols in radar sprite

NUKE_HEIGHT      = 8                            ; rows in nuke sprite
NUKE_WIDTH       = 2                            ; cols in nuke sprite

EXPLOSION_HEIGHT = 16                           ; rows in explosion sprite
EXPLOSION_WIDTH  = 4                            ; cols in explosion sprite

BOMB_HEIGHT      = 6                            ; rows in bomb sprite
BOMB_WIDTH       = 2                            ; cols in bomb sprite
BOMB_FRWRD_FRMS  = 6                            ; horz bomb travel duration

SHIP_HEIGHT      = 12                           ; rows in player ship sprite
SHIP_WIDTH       = 5                            ; cols in player ship sprite
SHIP_START       = 16                           ; height above world where ship starts
