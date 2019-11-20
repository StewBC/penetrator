# penetrator
 Remake of the ZX Spectrum game for the Commander X16.

1. INTRODUCTION

Back in the '80s I played this game, Penetrator, on a ZX Spectrum.  It is a
version of the arcade game Scramble.  What totally blew me away was that it
came with a level editor.  I think it was the first time I saw user generated
content in a game.

The game itself is a lot of fun to play even though I found it very difficult
back then.  Today, while I was testing this game, I made it through to the end
of the final level without turning off collisions or cheating in any way.  This
was a first for me.  Maybe I am getting better, or maybe it's just that I
played this a lot as I was making it - way more than I ever played the ZX
Spectrum version.

There's a video of the game on YouTube at https://youtu.be/ZruQWIdOD2c
There's also a Pseudo Technical Overview at https://youtu.be/iPIi9rvafF8 (23 
minutes long and I'll admit not the most riveting video on YouTube, but it does
explain how this all works at a high level)

2. CURRENT STATUS

The game is a pretty good replica of the original.  It is missing sound.  The
ZX Spectrum version had pretty awful sound so in a way this is a blessing.

It's also missing the demo attract mode, and the fireworks.  I would have liked
to have added both, but I am out of time on this game - I have spent about a
week more on it than I had intended.

I made some changes to suit the CX16.  I use taller screens in the UI. This not
only allows me more room to show some additional text, but the font also looks
substantially nicer.

3. TECHNICAL DETAILS

The game is written in 6502 assembly using the ca65 assembler.  ca65 is part of
the cc65 tool chain.  cc65 is mostly known as a 6502 emitting C compiler but it
has a very nice assembler.

The game does not use hardware sprites.  Everything is done as a software
render.  I use the two VERA layers as a view and back buffer.  When the view
buffer is shown to the user, I render to the back buffer and at the end of the
frame flip the layers so the back becomes the view and the view the back.

The layers are configured to be 2 bits per pixel, in other words I can have 4
colors at any one time.  The one exception is the intro logo.  That is done as
a 4 bpp image, since it has more than 4 colors.

There's really nothing fancy going on.  With 2 bpp there are 80 bytes across
for a resolution of 320 pixels in width.  Each byte represents a column which
suits this game like a glove, since it scrolls by 4 pixels at a time, in other
words, by 1 byte at a time.  There's no need to OR in the second column with
the 1st column as it would have had to be done on the ZX Spectrum.

The other interesting thing about the original is that it ran the AI and user
input twice for every world move.  This version does it the same way, and in a
way it must do so.  The bullet update is also run twice for each world update
and if the world moved while the bullets moved twice, the bullets could pass
through the walls, which would be no good.

4. KEYS and JOYSTICK

The original game was keyboard driven.  The CX16 version works with a joystick,
as well as with a keyboard on the emulator when it falls back to NES emulation
with keys.

The menus all show the keys to advance.  There's also a help screen in the
editor, as there was in the original.  The keys do not match the original game
keys since I made this game work well with a joystick.

The one undocumented key is P for pause.  The original had a pause mode which
could be used to do some sort of stutter step.  I made the P here work more or
less the same but it relies on the auto-repeat from the GETIN kernel function.

5. THE FILES

I tried to comment all the code very thoroughly.  Maybe too much so but I am
not an "old hand" at 6502 and I found it very useful, for myself, to read the
comments rather than the code.  This is by far and away the most 6502 I have
written and is my first complete 6502 project.

* defs.inc       - Constants and definitions used throughout
* draw.inc       - VERA layer drawing.  drawSprite, for example
* edit.inc       - The built-in world editor
* file.inc       - Load and Save code
* fontdata.inc   - A ZX Spectrum font in 16x8
* game.inc       - The in-game logic, AI etc.  The bulk of the "game"
* input.inc      - User controls for game and editor
* logodata.inc   - Line data for writing Penetrator and logo image data
* macros.inc     - vpoke, and print macros mostly
* penetrator.asm - Where the game starts, initial setup, etc.
* penetrator.cfg - ca65 configuration file
* rodata.inc     - Read-only data such as lookup tables, sprites etc.
* terrain.inc    - The terrain drawing routines
* text.inc       - In game text and print functions
* trndata.inc    - The world data (triplet - top, bottom and enemy pos)
* ui.inc         - User facing screens, name input, etc.
* variables.inc  - All non zero page variables
* zpvars.inc     - The zero page variables

6. CREDITS

* Phillip Mitchell and Beam Software for creating and publishing the game in
  1982.  Phillip Mitchell, I learned when I looked him up a few days ago, also
  made The Hobbit which had a great parser and flood-fill. Blew me away at the
  time.
* Everyone involved in the Commander X16 project.
* Everyone involved in making the cc65 tools, it's very good.
* Oliver Schmidt & Patryk "Silver Dream !" Łogiewa for a great Makefile.

7. DEDICATION

I dedicate this game to my brother Tewie Wessels. He owned a ZX Spectrum and
this game, and then loaned it all to me for a while.  14 Nov, when I am first
publishing this game, also happens to be his birthday.  

8. CONTACT

Feel free to contact me at swessels@email.com if you have thoughts or
suggestions.

Thank you
Stefan Wessels
14 November 2019 - Initial Revision
