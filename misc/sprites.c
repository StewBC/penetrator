#include <stdio.h>

unsigned char missile0A[] = {
0x41,                                       // X.....X
0x41,                                       // X.....X
0x41,                                       // X.....X
0x63,                                       // XX...XX
0x63,                                       // XX...XX
0x7F,                                       // XXXXXXX
0x3E,                                       // .XXXXX.
0x22,                                       // .X...X.
0x3E,                                       // .XXXXX.
0x1C,                                       // ..XXX..
0x1C,                                       // ..XXX..
0x08,                                       // ...X...
0x08,                                       // ...X...
0x08,                                       // ...X...
};

unsigned char missile0U[] = {
0x10, 0x08,                                  // ....X.....X...
0x10, 0x08,                                  // ....X.....X...
0x10, 0x08,                                  // ....X.....X...
0x30, 0x0C,                                  // ....XX...XX...
0x30, 0x0C,                                  // ....XX...XX...
0x70, 0x0F,                                  // ....XXXXXXX...
0x60, 0x07,                                  // .....XXXXX....
0x20, 0x04,                                  // .....X...X....
0x60, 0x07,                                  // .....XXXXX....
0x40, 0x03,                                  // ......XXX.....
0x40, 0x03,                                  // ......XXX.....
0x00, 0x01,                                  // .......X......
0x00, 0x01,                                  // .......X......
0x00, 0x01,                                  // .......X......
};

unsigned char missile1A[] = {
0x55,                                       // X.X.X.X
0x5D,                                       // X.XXX.X
0x49,                                       // X..X..X
0x6B,                                       // XX.X.XX
0x63,                                       // XX...XX
0x7F,                                       // XXXXXXX
0x3E,                                       // .XXXXX.
0x22,                                       // .X...X.
0x3E,                                       // .XXXXX.
0x1C,                                       // ..XXX..
0x1C,                                       // ..XXX..
0x08,                                       // ...X...
0x08,                                       // ...X...
0x08,                                       // ...X...
};

unsigned char missile1U[] = {
0x50, 0x0A,                                  // ....X.X.X.X...
0x50, 0x0B,                                  // ....X.XXX.X...
0x10, 0x09,                                  // ....X..X..X...
0x30, 0x0D,                                  // ....XX.X.XX...
0x30, 0x0C,                                  // ....XX...XX...
0x70, 0x0F,                                  // ....XXXXXXX...
0x60, 0x07,                                  // .....XXXXX....
0x20, 0x04,                                  // .....X...X....
0x60, 0x07,                                  // .....XXXXX....
0x40, 0x03,                                  // ......XXX.....
0x40, 0x03,                                  // ......XXX.....
0x00, 0x01,                                  // .......X......
0x00, 0x01,                                  // .......X......
0x00, 0x01,                                  // .......X......
};

unsigned char radar0A[] = {
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x70, 0x07,                                  // ....XXXXXX....
0x70, 0x07,                                  // ....XXXXXX....
0x20, 0x02,                                  // .....X..X.....
0x70, 0x07,                                  // ....XXXXXX....
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x7E, 0x3F,                                  // .XXXXXXXXXXXX.
0x7F, 0x7F,                                  // XXXXXXXXXXXXXX
0x7F, 0x7F,                                  // XXXXXXXXXXXXXX
0x7F, 0x7F,                                  // XXXXXXXXXXXXXX
0x7E, 0x3F,                                  // .XXXXXXXXXXXX.
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x70, 0x07,                                  // ....XXXXXX....
0x40, 0x01,                                  // ......XX......
0x40, 0x01,                                  // ......XX......
};

unsigned char radar0U[] = {
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x24, 0x00,                             // .........X..X........
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x60, 0x7F, 0x07,                             // .....XXXXXXXXXXXX....
0x70, 0x7F, 0x0F,                             // ....XXXXXXXXXXXXXX...
0x70, 0x7F, 0x0F,                             // ....XXXXXXXXXXXXXX...
0x70, 0x7F, 0x0F,                             // ....XXXXXXXXXXXXXX...
0x60, 0x7F, 0x07,                             // .....XXXXXXXXXXXX....
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x18, 0x00,                             // ..........XX.........
0x00, 0x18, 0x00,                             // ..........XX.........
};

unsigned char radar1A[] = {
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x70, 0x07,                                  // ....XXXXXX....
0x70, 0x07,                                  // ....XXXXXX....
0x20, 0x02,                                  // .....X..X.....
0x78, 0x03,                                  // ...XXXXXX.....
0x7C, 0x01,                                  // ..XXXXXX......
0x7C, 0x03,                                  // ..XXXXXXX.....
0x7C, 0x07,                                  // ..XXXXXXXX....
0x78, 0x0F,                                  // ...XXXXXXXX...
0x70, 0x0F,                                  // ....XXXXXXX...
0x60, 0x0F,                                  // .....XXXXXX...
0x70, 0x0F,                                  // ....XXXXXXX...
0x58, 0x07,                                  // ...XX.XXXX....
0x08, 0x02,                                  // ...X....X.....
0x00, 0x00,                                  // ..............
};

unsigned char radar1U[] = {
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x24, 0x00,                             // .........X..X........
0x00, 0x3F, 0x00,                             // .......XXXXXX........
0x40, 0x1F, 0x00,                             // ......XXXXXX.........
0x40, 0x3F, 0x00,                             // ......XXXXXXX........
0x40, 0x7F, 0x00,                             // ......XXXXXXXX.......
0x00, 0x7F, 0x01,                             // .......XXXXXXXX......
0x00, 0x7E, 0x01,                             // ........XXXXXXX......
0x00, 0x7C, 0x01,                             // .........XXXXXX......
0x00, 0x7E, 0x01,                             // ........XXXXXXX......
0x00, 0x7B, 0x00,                             // .......XX.XXXX.......
0x00, 0x21, 0x00,                             // .......X....X........
0x00, 0x00, 0x00,                             // .....................
};

unsigned char radar2A[] = {
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x70, 0x07,                                  // ....XXXXXX....
0x70, 0x07,                                  // ....XXXXXX....
0x20, 0x02,                                  // .....X..X.....
0x70, 0x03,                                  // ....XXXXX.....
0x78, 0x01,                                  // ...XXXXX......
0x7C, 0x03,                                  // ..XXXXXXX.....
0x60, 0x07,                                  // .....XXXXX....
0x40, 0x07,                                  // ......XXXX....
0x40, 0x07,                                  // ......XXXX....
0x60, 0x07,                                  // .....XXXXX....
0x30, 0x07,                                  // ....XX.XXX....
0x18, 0x03,                                  // ...XX..XX.....
0x00, 0x01,                                  // .......X......
0x00, 0x00,                                  // ..............
};

unsigned char radar2U[] = {
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x24, 0x00,                             // .........X..X........
0x00, 0x3E, 0x00,                             // ........XXXXX........
0x00, 0x1F, 0x00,                             // .......XXXXX.........
0x40, 0x3F, 0x00,                             // ......XXXXXXX........
0x00, 0x7C, 0x00,                             // .........XXXXX.......
0x00, 0x78, 0x00,                             // ..........XXXX.......
0x00, 0x78, 0x00,                             // ..........XXXX.......
0x00, 0x7C, 0x00,                             // .........XXXXX.......
0x00, 0x76, 0x00,                             // ........XX.XXX.......
0x00, 0x33, 0x00,                             // .......XX..XX........
0x00, 0x10, 0x00,                             // ...........X.........
0x00, 0x00, 0x00,                             // .....................
};

unsigned char radar3A[] = {
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x70, 0x07,                                  // ....XXXXXX....
0x70, 0x07,                                  // ....XXXXXX....
0x20, 0x02,                                  // .....X..X.....
0x78, 0x03,                                  // ...XXXXXX.....
0x7C, 0x01,                                  // ..XXXXXX......
0x44, 0x03,                                  // ..X...XXX.....
0x04, 0x07,                                  // ..X....XXX....
0x64, 0x0E,                                  // ..X..XX.XXX...
0x68, 0x0C,                                  // ...X.XX..XX...
0x10, 0x08,                                  // ....X.....X...
0x30, 0x08,                                  // ....XX....X...
0x48, 0x04,                                  // ...X..X..X....
0x08, 0x03,                                  // ...X...XX.....
0x00, 0x00,                                  // ..............
};

unsigned char radar3U[] = {
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x24, 0x00,                             // .........X..X........
0x00, 0x3F, 0x00,                             // .......XXXXXX........
0x40, 0x1F, 0x00,                             // ......XXXXXX.........
0x40, 0x38, 0x00,                             // ......X...XXX........
0x40, 0x70, 0x00,                             // ......X....XXX.......
0x40, 0x6C, 0x01,                             // ......X..XX.XXX......
0x00, 0x4D, 0x01,                             // .......X.XX..XX......
0x00, 0x02, 0x01,                             // ........X.....X......
0x00, 0x06, 0x01,                             // ........XX....X......
0x00, 0x49, 0x00,                             // .......X..X..X.......
0x00, 0x31, 0x00,                             // .......X...XX........
0x00, 0x00, 0x00,                             // .....................
};

unsigned char radar4A[] = {
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x70, 0x07,                                  // ....XXXXXX....
0x70, 0x07,                                  // ....XXXXXX....
0x20, 0x02,                                  // .....X..X.....
0x70, 0x07,                                  // ....XXXXXX....
0x0C, 0x18,                                  // ..XX......XX..
0x02, 0x20,                                  // .X..........X.
0x01, 0x40,                                  // X............X
0x41, 0x41,                                  // X.....XX.....X
0x41, 0x41,                                  // X.....XX.....X
0x42, 0x21,                                  // .X....XX....X.
0x4C, 0x19,                                  // ..XX..XX..XX..
0x70, 0x07,                                  // ....XXXXXX....
0x40, 0x01,                                  // ......XX......
0x40, 0x01,                                  // ......XX......
};

unsigned char radar4U[] = {
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x24, 0x00,                             // .........X..X........
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x40, 0x01, 0x03,                             // ......XX......XX.....
0x20, 0x00, 0x04,                             // .....X..........X....
0x10, 0x00, 0x08,                             // ....X............X...
0x10, 0x18, 0x08,                             // ....X.....XX.....X...
0x10, 0x18, 0x08,                             // ....X.....XX.....X...
0x20, 0x18, 0x04,                             // .....X....XX....X....
0x40, 0x19, 0x03,                             // ......XX..XX..XX.....
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x18, 0x00,                             // ..........XX.........
0x00, 0x18, 0x00,                             // ..........XX.........
};

unsigned char radar5A[] = {
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x70, 0x07,                                  // ....XXXXXX....
0x70, 0x07,                                  // ....XXXXXX....
0x20, 0x02,                                  // .....X..X.....
0x60, 0x0F,                                  // .....XXXXXX...
0x40, 0x1F,                                  // ......XXXXXX..
0x60, 0x11,                                  // .....XXX...X..
0x70, 0x10,                                  // ....XXX....X..
0x38, 0x13,                                  // ...XXX.XX..X..
0x18, 0x0B,                                  // ...XX..XX.X...
0x08, 0x04,                                  // ...X.....X....
0x08, 0x06,                                  // ...X....XX....
0x10, 0x09,                                  // ....X..X..X...
0x60, 0x08,                                  // .....XX...X...
0x00, 0x00,                                  // ..............
};

unsigned char radar5U[] = {
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x24, 0x00,                             // .........X..X........
0x00, 0x7C, 0x01,                             // .........XXXXXX......
0x00, 0x78, 0x03,                             // ..........XXXXXX.....
0x00, 0x1C, 0x02,                             // .........XXX...X.....
0x00, 0x0E, 0x02,                             // ........XXX....X.....
0x00, 0x37, 0x02,                             // .......XXX.XX..X.....
0x00, 0x33, 0x01,                             // .......XX..XX.X......
0x00, 0x41, 0x00,                             // .......X.....X.......
0x00, 0x61, 0x00,                             // .......X....XX.......
0x00, 0x12, 0x01,                             // ........X..X..X......
0x00, 0x0C, 0x01,                             // .........XX...X......
0x00, 0x00, 0x00,                             // .....................
};

unsigned char radar6A[] = {
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x70, 0x07,                                  // ....XXXXXX....
0x70, 0x07,                                  // ....XXXXXX....
0x20, 0x02,                                  // .....X..X.....
0x60, 0x07,                                  // .....XXXXX....
0x40, 0x0F,                                  // ......XXXXX...
0x60, 0x1F,                                  // .....XXXXXXX..
0x70, 0x03,                                  // ....XXXXX.....
0x70, 0x01,                                  // ....XXXX......
0x70, 0x01,                                  // ....XXXX......
0x70, 0x03,                                  // ....XXXXX.....
0x70, 0x06,                                  // ....XXX.XX....
0x60, 0x0C,                                  // .....XX..XX...
0x40, 0x00,                                  // ......X.......
0x00, 0x00,                                  // ..............
};

unsigned char radar6U[] = {
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x24, 0x00,                             // .........X..X........
0x00, 0x7C, 0x00,                             // .........XXXXX.......
0x00, 0x78, 0x01,                             // ..........XXXXX......
0x00, 0x7C, 0x03,                             // .........XXXXXXX.....
0x00, 0x3E, 0x00,                             // ........XXXXX........
0x00, 0x1E, 0x00,                             // ........XXXX.........
0x00, 0x1E, 0x00,                             // ........XXXX.........
0x00, 0x3E, 0x00,                             // ........XXXXX........
0x00, 0x6E, 0x00,                             // ........XXX.XX.......
0x00, 0x4C, 0x01,                             // .........XX..XX......
0x00, 0x08, 0x00,                             // ..........X..........
0x00, 0x00, 0x00,                             // .....................
};

unsigned char radar7A[] = {
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x7C, 0x1F,                                  // ..XXXXXXXXXX..
0x70, 0x07,                                  // ....XXXXXX....
0x70, 0x07,                                  // ....XXXXXX....
0x20, 0x02,                                  // .....X..X.....
0x60, 0x0F,                                  // .....XXXXXX...
0x40, 0x1F,                                  // ......XXXXXX..
0x60, 0x1F,                                  // .....XXXXXXX..
0x70, 0x1F,                                  // ....XXXXXXXX..
0x78, 0x0F,                                  // ...XXXXXXXX...
0x78, 0x07,                                  // ...XXXXXXX....
0x78, 0x03,                                  // ...XXXXXX.....
0x78, 0x07,                                  // ...XXXXXXX....
0x70, 0x0D,                                  // ....XXXX.XX...
0x20, 0x08,                                  // .....X....X...
0x00, 0x00,                                  // ..............
};

unsigned char radar7U[] = {
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x40, 0x7F, 0x03,                             // ......XXXXXXXXXX.....
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x7E, 0x00,                             // ........XXXXXX.......
0x00, 0x24, 0x00,                             // .........X..X........
0x00, 0x7C, 0x01,                             // .........XXXXXX......
0x00, 0x78, 0x03,                             // ..........XXXXXX.....
0x00, 0x7C, 0x03,                             // .........XXXXXXX.....
0x00, 0x7E, 0x03,                             // ........XXXXXXXX.....
0x00, 0x7F, 0x01,                             // .......XXXXXXXX......
0x00, 0x7F, 0x00,                             // .......XXXXXXX.......
0x00, 0x3F, 0x00,                             // .......XXXXXX........
0x00, 0x7F, 0x00,                             // .......XXXXXXX.......
0x00, 0x5E, 0x01,                             // ........XXXX.XX......
0x00, 0x04, 0x01,                             // .........X....X......
0x00, 0x00, 0x00,                             // .....................
};

unsigned char explosion0A[] = {
 0x04, 0x00,                                 // ..X...........
 0x0C, 0x00,                                 // ..XX..........
 0x00, 0x41,                                 // .......X.....X
 0x00, 0x00,                                 // ..............
 0x00, 0x10,                                 // ...........X..
 0x49, 0x01,                                 // X..X..XX......
 0x60, 0x07,                                 // .....XXXXX....
 0x60, 0x0F,                                 // .....XXXXXX...
 0x60, 0x2F,                                 // .....XXXXXX.X.
 0x60, 0x03,                                 // .....XXXX.....
 0x08, 0x02,                                 // ...X....X.....
 0x00, 0x10,                                 // ...........X..
 0x30, 0x00,                                 // ....XX........
 0x31, 0x00,                                 // X...XX........
 0x01, 0x62,                                 // X.......X...XX
 0x00, 0x00,                                 // ..............
};

unsigned char explosion0U[] = {
 0x20, 0x00, 0x00,                            // .....X...............
 0x60, 0x00, 0x00,                            // .....XX..............
 0x00, 0x08, 0x04,                            // ..........X.....X....
 0x00, 0x00, 0x00,                            // .....................
 0x00, 0x00, 0x01,                            // ..............X......
 0x48, 0x0C, 0x00,                            // ...X..X..XX..........
 0x00, 0x3E, 0x00,                            // ........XXXXX........
 0x00, 0x7E, 0x00,                            // ........XXXXXX.......
 0x00, 0x7E, 0x02,                            // ........XXXXXX.X.....
 0x00, 0x1E, 0x00,                            // ........XXXX.........
 0x40, 0x10, 0x00,                            // ......X....X.........
 0x00, 0x00, 0x01,                            // ..............X......
 0x00, 0x03, 0x00,                            // .......XX............
 0x08, 0x03, 0x00,                            // ...X...XX............
 0x08, 0x10, 0x06,                            // ...X.......X...XX....
 0x00, 0x00, 0x00,                            // .....................
};

unsigned char explosion1A[] = {
 0x06, 0x00,                                 // .XX...........
 0x04, 0x42,                                 // ..X.....X....X
 0x00, 0x00,                                 // ..............
 0x00, 0x20,                                 // ............X.
 0x44, 0x01,                                 // ..X...XX......
 0x10, 0x0D,                                 // ....X..X.XX...
 0x50, 0x17,                                 // ....X.XXXX.X..
 0x60, 0x0A,                                 // .....XX.X.X...
 0x60, 0x0C,                                 // .....XX..XX...
 0x68, 0x41,                                 // ...X.XXX.....X
 0x18, 0x02,                                 // ...XX...X.....
 0x00, 0x08,                                 // ..........X...
 0x00, 0x20,                                 // ............X.
 0x30, 0x00,                                 // ....XX........
 0x14, 0x40,                                 // ..X.X........X
 0x00, 0x04,                                 // .........X....
};

unsigned char explosion1U[] = {
 0x30, 0x00, 0x00,                            // ....XX...............
 0x20, 0x10, 0x04,                            // .....X.....X....X....
 0x00, 0x00, 0x00,                            // .....................
 0x00, 0x00, 0x02,                            // ...............X.....
 0x20, 0x0C, 0x00,                            // .....X...XX..........
 0x00, 0x69, 0x00,                            // .......X..X.XX.......
 0x00, 0x3D, 0x01,                            // .......X.XXXX.X......
 0x00, 0x56, 0x00,                            // ........XX.X.X.......
 0x00, 0x66, 0x00,                            // ........XX..XX.......
 0x40, 0x0E, 0x04,                            // ......X.XXX.....X....
 0x40, 0x11, 0x00,                            // ......XX...X.........
 0x00, 0x40, 0x00,                            // .............X.......
 0x00, 0x00, 0x02,                            // ...............X.....
 0x00, 0x03, 0x00,                            // .......XX............
 0x20, 0x01, 0x04,                            // .....X.X........X....
 0x00, 0x20, 0x00,                            // ............X........
};

unsigned char explosion2A[] = {
0x02, 0x04,                                  // .X.......X....
0x00, 0x00,                                  // ..............
0x20, 0x40,                                  // .....X.......X
0x01, 0x21,                                  // X......X....X.
0x04, 0x09,                                  // ..X....X..X...
0x10, 0x00,                                  // ....X.........
0x10, 0x14,                                  // ....X....X.X..
0x24, 0x20,                                  // ..X..X......X.
0x20, 0x08,                                  // .....X....X...
0x12, 0x00,                                  // .X..X.........
0x08, 0x02,                                  // ...X....X.....
0x0A, 0x21,                                  // .X.X...X....X.
0x00, 0x00,                                  // ..............
0x10, 0x40,                                  // ....X........X
0x04, 0x00,                                  // ..X...........
0x09, 0x40,                                  // X..X.........X
};

unsigned char explosion2U[] = {
0x10, 0x20, 0x00,                             // ....X.......X........
0x00, 0x00, 0x00,                             // .....................
0x00, 0x02, 0x04,                             // ........X.......X....
0x08, 0x08, 0x02,                             // ...X......X....X.....
0x20, 0x48, 0x00,                             // .....X....X..X.......
0x00, 0x01, 0x00,                             // .......X.............
0x00, 0x21, 0x01,                             // .......X....X.X......
0x20, 0x02, 0x02,                             // .....X..X......X.....
0x00, 0x42, 0x00,                             // ........X....X.......
0x10, 0x01, 0x00,                             // ....X..X.............
0x40, 0x10, 0x00,                             // ......X....X.........
0x50, 0x08, 0x02,                             // ....X.X...X....X.....
0x00, 0x00, 0x00,                             // .....................
0x00, 0x01, 0x04,                             // .......X........X....
0x20, 0x00, 0x00,                             // .....X...............
0x48, 0x00, 0x04,                             // ...X..X.........X....
};

unsigned char explosion3A[] = {
0x00, 0x00,                                  // ..............
0x02, 0x10,                                  // .X.........X..
0x20, 0x04,                                  // .....X...X....
0x01, 0x01,                                  // X......X......
0x00, 0x40,                                  // .............X
0x04, 0x00,                                  // ..X...........
0x08, 0x10,                                  // ...X.......X..
0x41, 0x00,                                  // X.....X.......
0x00, 0x20,                                  // ............X.
0x01, 0x01,                                  // X......X......
0x10, 0x00,                                  // ....X.........
0x00, 0x08,                                  // ..........X...
0x02, 0x02,                                  // .X......X.....
0x04, 0x00,                                  // ..X...........
0x00, 0x10,                                  // ...........X..
0x01, 0x00,                                  // X.............
};

unsigned char explosion3U[] = {
0x00, 0x00, 0x00,                             // .....................
0x10, 0x00, 0x01,                             // ....X.........X......
0x00, 0x22, 0x00,                             // ........X...X........
0x08, 0x08, 0x00,                             // ...X......X..........
0x00, 0x00, 0x04,                             // ................X....
0x20, 0x00, 0x00,                             // .....X...............
0x40, 0x00, 0x01,                             // ......X.......X......
0x08, 0x04, 0x00,                             // ...X.....X...........
0x00, 0x00, 0x02,                             // ...............X.....
0x08, 0x08, 0x00,                             // ...X......X..........
0x00, 0x01, 0x00,                             // .......X.............
0x00, 0x40, 0x00,                             // .............X.......
0x10, 0x10, 0x00,                             // ....X......X.........
0x20, 0x00, 0x00,                             // .....X...............
0x00, 0x00, 0x01,                             // ..............X......
0x08, 0x00, 0x00,                             // ...X.................
};

unsigned char monsterA[] = {
0x78, 0x00,                                  // ...XXXX.......
0x4C, 0x01,                                  // ..XX..XX......
0x7C, 0x01,                                  // ..XXXXXX......
0x7E, 0x03,                                  // .XXXXXXXX.....
0x37, 0x07,                                  // XXX.XX.XXX....
0x33, 0x06,                                  // XX..XX..XX....
0x33, 0x06,                                  // XX..XX..XX....
0x7B, 0x06,                                  // XX.XXXX.XX....
0x7F, 0x07,                                  // XXXXXXXXXX....
0x7E, 0x03,                                  // .XXXXXXXX.....
0x7F, 0x07,                                  // XXXXXXXXXX....
0x7B, 0x06,                                  // XX.XXXX.XX....
0x01, 0x04,                                  // X........X....
};

unsigned char monsterU[] = {
0x00, 0x0F,                                  // .......XXXX...
0x40, 0x19,                                  // ......XX..XX..
0x40, 0x1F,                                  // ......XXXXXX..
0x60, 0x3F,                                  // .....XXXXXXXX.
0x70, 0x76,                                  // ....XXX.XX.XXX
0x30, 0x66,                                  // ....XX..XX..XX
0x30, 0x66,                                  // ....XX..XX..XX
0x30, 0x6F,                                  // ....XX.XXXX.XX
0x70, 0x7F,                                  // ....XXXXXXXXXX
0x60, 0x3F,                                  // .....XXXXXXXX.
0x70, 0x7F,                                  // ....XXXXXXXXXX
0x30, 0x6F,                                  // ....XX.XXXX.XX
0x10, 0x40,                                  // ....X........X
};

unsigned char nukeA[] = {
0x3F,                                       // XXXXXX.
0x12,                                       // .X..X..
0x0C,                                       // ..XX...
0x12,                                       // .X..X..
0x2D,                                       // X.XX.X.
0x2D,                                       // X.XX.X.
0x12,                                       // .X..X..
0x0C,                                       // ..XX...
};

unsigned char nukeU[] = {
0x70, 0x07,                                  // ....XXXXXX....
0x20, 0x02,                                  // .....X..X.....
0x40, 0x01,                                  // ......XX......
0x20, 0x02,                                  // .....X..X.....
0x50, 0x05,                                  // ....X.XX.X....
0x50, 0x05,                                  // ....X.XX.X....
0x20, 0x02,                                  // .....X..X.....
0x40, 0x01,                                  // ......XX......
};

unsigned char bomb0A[] = {
0x04,                                       // ..X....
0x04,                                       // ..X....
0x0E,                                       // .XXX...
0x1F,                                       // XXXXX..
0x15,                                       // X.X.X..
0x11,                                       // X...X..
};

unsigned char bomb0U[] = {
0x40, 0x00,                                  //......X.......
0x40, 0x00,                                  //......X.......
0x60, 0x01,                                  //.....XXX......
0x70, 0x03,                                  //....XXXXX.....
0x50, 0x02,                                  //....X.X.X.....
0x10, 0x02,                                  //....X...X.....
};

unsigned char bomb1A[] = {
0x07,                                       // XXX....
0x0C,                                       // ..XX...
0x3E,                                       // .XXXXX.
0x0C,                                       // ..XX...
0x07,                                       // XXX....
};

unsigned char bomb1U[] = {
0x70, 0x00,                                  // ....XXX.......
0x40, 0x01,                                  // ......XX......
0x60, 0x07,                                  // .....XXXXX....
0x40, 0x01,                                  // ......XX......
0x70, 0x00,                                  // ....XXX.......
};

unsigned char shipA[] = {
0x7C, 0x7F, 0x03,                             // ..XXXXXXXXXXXXXX.....
0x78, 0x03, 0x00,                             // ...XXXXXX............
0x70, 0x1F, 0x00,                             // ....XXXXXXXX.........
0x60, 0x7F, 0x0F,                             // .....XXXXXXXXXXXXX...
0x60, 0x7F, 0x7F,                             // .....XXXXXXXXXXXXXXXX
0x60, 0x63, 0x07,                             // .....XXXX...XXXXX....
0x60, 0x31, 0x00,                             // .....XXX...XX........
0x70, 0x1F, 0x00,                             // ....XXXXXXXX.........
0x78, 0x03, 0x00,                             // ...XXXXXX............
0x7C, 0x00, 0x00,                             // ..XXXXX..............
0x1E, 0x00, 0x00,                             // .XXXX................
0x7F, 0x07, 0x00,                             // XXXXXXXXXX...........
};

unsigned char shipU[] = {
0x40, 0x7F, 0x3F, 0x00,                        // ......XXXXXXXXXXXXXX.....
0x00, 0x3F, 0x00, 0x00,                        // .......XXXXXX............
0x00, 0x7E, 0x07, 0x00,                        // ........XXXXXXXXX........
0x00, 0x7C, 0x7F, 0x01,                        // .........XXXXXXXXXXXXX...
0x00, 0x7C, 0x7F, 0x0F,                        // .........XXXXXXXXXXXXXXXX
0x00, 0x3C, 0x78, 0x00,                        // .........XXXX....XXXX....
0x00, 0x1C, 0x0C, 0x00,                        // .........XXX....XX.......
0x00, 0x7E, 0x07, 0x00,                        // ........XXXXXXXXX........
0x00, 0x3F, 0x00, 0x00,                        // .......XXXXXX............
0x40, 0x0F, 0x00, 0x00,                        // ......XXXXX..............
0x60, 0x03, 0x00, 0x00,                        // .....XXXX................
0x70, 0x7F, 0x00, 0x00,                        // ....XXXXXXXXXX...........
};

unsigned char *assets[] = {
bomb0A,
bomb0U,
bomb1A,
bomb1U,
explosion0A,
explosion0U,
explosion1A,
explosion1U,
explosion2A,
explosion2U,
explosion3A,
explosion3U,
missile0A,
missile0U,
missile1A,
missile1U,
monsterA,
monsterU,
nukeA,
nukeU,
radar0A,
radar0U,
radar1A,
radar1U,
radar2A,
radar2U,
radar3A,
radar3U,
radar4A,
radar4U,
radar5A,
radar5U,
radar6A,
radar6U,
radar7A,
radar7U,
shipA,
shipU,
};

unsigned int asset_sizes[] = {
sizeof(bomb0A) / sizeof(bomb0A[0]),
sizeof(bomb0U) / sizeof(bomb0U[0]),
sizeof(bomb1A) / sizeof(bomb1A[0]),
sizeof(bomb1U) / sizeof(bomb1U[0]),
sizeof(explosion0A) / sizeof(explosion0A[0]),
sizeof(explosion0U) / sizeof(explosion0U[0]),
sizeof(explosion1A) / sizeof(explosion1A[0]),
sizeof(explosion1U) / sizeof(explosion1U[0]),
sizeof(explosion2A) / sizeof(explosion2A[0]),
sizeof(explosion2U) / sizeof(explosion2U[0]),
sizeof(explosion3A) / sizeof(explosion3A[0]),
sizeof(explosion3U) / sizeof(explosion3U[0]),
sizeof(missile0A) / sizeof(missile0A[0]),
sizeof(missile0U) / sizeof(missile0U[0]),
sizeof(missile1A) / sizeof(missile1A[0]),
sizeof(missile1U) / sizeof(missile1U[0]),
sizeof(monsterA) / sizeof(monsterA[0]),
sizeof(monsterU) / sizeof(monsterU[0]),
sizeof(nukeA) / sizeof(nukeA[0]),
sizeof(nukeU) / sizeof(nukeU[0]),
sizeof(radar0A) / sizeof(radar0A[0]),
sizeof(radar0U) / sizeof(radar0U[0]),
sizeof(radar1A) / sizeof(radar1A[0]),
sizeof(radar1U) / sizeof(radar1U[0]),
sizeof(radar2A) / sizeof(radar2A[0]),
sizeof(radar2U) / sizeof(radar2U[0]),
sizeof(radar3A) / sizeof(radar3A[0]),
sizeof(radar3U) / sizeof(radar3U[0]),
sizeof(radar4A) / sizeof(radar4A[0]),
sizeof(radar4U) / sizeof(radar4U[0]),
sizeof(radar5A) / sizeof(radar5A[0]),
sizeof(radar5U) / sizeof(radar5U[0]),
sizeof(radar6A) / sizeof(radar6A[0]),
sizeof(radar6U) / sizeof(radar6U[0]),
sizeof(radar7A) / sizeof(radar7A[0]),
sizeof(radar7U) / sizeof(radar7U[0]),
sizeof(shipA) / sizeof(shipA[0]),
sizeof(shipU) / sizeof(shipU[0]),
};

unsigned int asset_cols[] = {
1, // bomb0A
2, // bomb0U
1, // bomb1A
2, // bomb1U
2, // explosion0A
3, // explosion0U
2, // explosion1A
3, // explosion1U
2, // explosion2A
3, // explosion2U
2, // explosion3A
3, // explosion3U
1, // missile0A
2, // missile0U
1, // missile1A
2, // missile1U
2, // monsterA
2, // monsterU
1, // nukeA
2, // nukeU
2, // radar0A
3, // radar0U
2, // radar1A
3, // radar1U
2, // radar2A
3, // radar2U
2, // radar3A
3, // radar3U
2, // radar4A
3, // radar4U
2, // radar5A
3, // radar5U
2, // radar6A
3, // radar6U
2, // radar7A
3, // radar7U
3, // shipA
4, // shipU
};

char *asset_names[] = {
"bomb0A",
"bomb0U",
"bomb1A",
"bomb1U",
"explosion0A",
"explosion0U",
"explosion1A",
"explosion1U",
"explosion2A",
"explosion2U",
"explosion3A",
"explosion3U",
"missile0A",
"missile0U",
"missile1A",
"missile1U",
"monsterA",
"monsterU",
"nukeA",
"nukeU",
"radar0A",
"radar0U",
"radar1A",
"radar1U",
"radar2A",
"radar2U",
"radar3A",
"radar3U",
"radar4A",
"radar4U",
"radar5A",
"radar5U",
"radar6A",
"radar6U",
"radar7A",
"radar7U",
"shipA",
"shipU",
};


const int num_assets = sizeof(assets) / sizeof(assets[0]);

void convert_asset(const char *name, unsigned char *data, unsigned int data_size, unsigned int num_cols) {
    int r, c, b, i, j;
    unsigned int rows = data_size / num_cols;
    char ascii[96];
    printf("%s:\n", name);
    for(r = 0; r < rows; r++) {
        printf(".byte ");
        i = 0;
        for(c = 0; c < num_cols; c++) {
            b = data[r*num_cols+c];
            b = (b * 0x0202020202ULL & 0x010884422010ULL) % 1023;
            printf("$%02X%s",b , c != num_cols - 1 ? ", " : "        ");
            for(j = 7 ; j >= 0 ; j--) {
                if(b & (1 << j)) {
                    ascii[i++] = 'X';
                } else {
                    ascii[i++] = '-';
                }
            }
        }
        ascii[i] = '\0';
        printf("; %s\n", ascii);
    }
    printf("\n");
}

int main() {
    int i;

    for(i = 0; i < num_assets; i++) {
        convert_asset(asset_names[i], assets[i], asset_sizes[i], asset_cols[i]);
    }
}