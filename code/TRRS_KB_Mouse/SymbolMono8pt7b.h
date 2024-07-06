/*
 * This is a custom 8pt font that defines characters 0-31 and 128-136
 * Could be expanded to 255 if you have the memory and the need.
 * See https://learn.adafruit.com/creating-custom-symbol-font-for-adafruit-gfx-library
 * for details on how we created this file and similar files in other sizes.
 */
const uint8_t SymbolMono8pt7bBitmaps[] PROGMEM = {
//00 Test square
/*| 8 4 2 1 8 4 2 1 |*/
/*| X X X X X |*/  0xf8, 
/*| X . . . X |*/  0x88, 
/*| X . . . X |*/  0x88,
/*| X . . . X |*/  0x88, 
/*| X . . . X |*/  0x88,
/*| X . . . X |*/  0x88,
/*| X X X X X |*/  0xf8,

//01 Upper left arrow
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x x . |*/  0xf0, 
/*| x x . . . |*/  0xc0, 
/*| x . x . . |*/  0xa0, 
/*| x . . x . |*/  0x90, 
/*| . . . . x |*/  0x08, 

//02 Upper right arrow
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x x x |*/  0xf8, 
/*| . . . x x |*/  0x18, 
/*| . . x . x |*/  0x28,
/*| . x . . x |*/  0x48, 
/*| x . . . . |*/  0x80, 

//03 Lower left arrow
/*| 8 4 2 1 8 4 2 1 |*/
/*| x . . . x |*/  0x88, 
/*| x . . x . |*/  0x90, 
/*| x . x . . |*/  0xa0,
/*| x x . . . |*/  0xc0, 
/*| x x x x x |*/  0xf8, 

//04 Lower right arrow
/*| 8 4 2 1 8 4 2 1 |*/
/*| x . . . x |*/  0x88, 
/*| . x . . x |*/  0x48,
/*| . . x . x |*/  0x28,
/*| . . . x x |*/  0x18, 
/*| x x x x x |*/  0xf8, 

//05 Power symbol 
/*| 8 4 2 1 8 4 2 1 |*/
/*| . . X . . |*/  0x20, 
/*| . . x . . |*/  0x20, 
/*| . x x x . |*/  0x70,
/*| X . x . X |*/  0xa8, 
/*| X . x . X |*/  0xa8,
/*| X . . . X |*/  0x88,
/*| . X X X . |*/  0x70,

//06 Skip left
/*| 8 4 2 1 8 4 2 1 |*/
/*| . x . . X |*/  0x48, 
/*| . x . x X |*/  0x58, 
/*| . x x x X |*/  0x78,
/*| . x . x X |*/  0x58, 
/*| . x . . X |*/  0x48,

//07 Rewind
/*| 8 4 2 1 8 4 2 1 |*/
/*| . . x . . x |*/  0x24, 
/*| . x x . x x |*/  0x6c, 
/*| x x x x x X |*/  0xfc,
/*| . x x . x x |*/  0x6c, 
/*| . . x . . x |*/  0x24,

//08 Play
/*| 8 4 2 1 8 4 2 1 |*/
/*| x . . . . |*/  0x80, 
/*| x x . . . |*/  0xc0, 
/*| x x x . . |*/  0xe0,
/*| x x . . . |*/  0xc0, 
/*| x . . . . |*/  0x80,

//09 ff
/*| 8 4 2 1 8 4 2 1 |*/
/*| x . . x . . |*/  0x90, 
/*| x x . x x . |*/  0xd8, 
/*| x x x x x x |*/  0xfc,
/*| x x . x x . |*/  0xd8, 
/*| x . . x . . |*/  0x90,

//10 Skip Right
/*| 8 4 2 1 8 4 2 1 |*/
/*| x . . x . |*/  0x90,
/*| x x . x . |*/  0xd0, 
/*| x x x x . |*/  0xf0,
/*| x x . x . |*/  0xd0, 
/*| x . . x . |*/  0x90,

//11 pause
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x . x x |*/  0xd8, 
/*| x x . x x |*/  0xd8, 
/*| x x . x x |*/  0xd8, 
/*| x x . x x |*/  0xd8, 
/*| x x . x x |*/  0xd8, 

//12 Stop
/*| 8 4 2 1 8 4 2 1 |*/
/*| . x x x . |*/  0x70,
/*| . x x x . |*/  0x70,
/*| . x x x . |*/  0x70,

//13 ch up
/*| 8 4 2 1 8 4 2 1 |*/
/*| . . x . . |*/  0x20, 
/*| . x x x . |*/  0x70, 
/*| x x x x x |*/  0xf8,

//14 ch down
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x x x |*/  0xf8, 
/*| . x x x . |*/  0x70, 
/*| . . x . . |*/  0x20,

//15 Page up
/*| 8 4 2 1 8 4 2 1 |*/
/*| . . X . . |*/  0x20, 
/*| . x . x . |*/  0x50, 
/*| X . . . X |*/  0x88,
/*| . . x . . |*/  0x20, 
/*| . x . x . |*/  0x50,
/*| X . . . X |*/  0x88,

//16 Page down
/*| 8 4 2 1 8 4 2 1 |*/
/*| X . . . X |*/  0x88,
/*| . x . x . |*/  0x50, 
/*| . . X . . |*/  0x20, 
/*| X . . . X |*/  0x88,
/*| . x . x . |*/  0x50, 
/*| . . X . . |*/  0x20, 

//17 Bluetooth
/*| 8 4 2 1 8 4 2 1 |*/
/*| . x . . . |*/  0x40, 
/*| . x x . . |*/  0x60, 
/*| . x . x . |*/  0x50,
/*| x x x . . |*/  0xe0, 
/*| . x . x . |*/  0x50,
/*| . x x . . |*/  0x60,
/*| . X . . . |*/  0x40,

//18 Up arrow
/*| 8 4 2 1 8 4 2 1 |*/
/*| . . X . . |*/  0x20, 
/*| . x x x . |*/  0x70, 
/*| X . x . X |*/  0xa8,
/*| . . x . . |*/  0x20, 
/*| . . x . . |*/  0x20, 
/*| . . x . . |*/  0x20, 

//19 Down arrow
/*| 8 4 2 1 8 4 2 1 |*/
/*| . . x . . |*/  0x20, 
/*| . . x . . |*/  0x20, 
/*| . . x . . |*/  0x20, 
/*| x . x . x |*/  0xa8,
/*| . x x x . |*/  0x70, 
/*| . . x . . |*/  0x20, 

//20 Left arrow
/*| 8 4 2 1 8 4 2 1 |*/
/*| . . . x . |*/  0x10, 
/*| . . x . . |*/  0x20, 
/*| . x . . . |*/  0x40, 
/*| x x x x x |*/  0xf8,
/*| . x . . . |*/  0x40, 
/*| . . x . . |*/  0x20, 
/*| . . . x . |*/  0x10, 

//21 Right arrow
/*| 8 4 2 1 8 4 2 1 |*/
/*| . x . . . |*/  0x40, 
/*| . . x . . |*/  0x20, 
/*| . . . x . |*/  0x10, 
/*| x x x x x |*/  0xf8,
/*| . . . x . |*/  0x10, 
/*| . . x . . |*/  0x20, 
/*| . x . . . |*/  0x40, 

//22 Return
/*| 8 4 2 1 8 4 2 1 |*/
/*| . . x . x |*/  0x28,
/*| . x . . x |*/  0x48,
/*| x x x x x |*/  0xf8, 
/*| . x . . . |*/  0x40,
/*| . . x . . |*/  0x20,

//23 Backspace
/*| 8 4 2 1 8 4 2 1 |*/
/*| . . X X X |*/  0x38, 
/*| . X . . X |*/  0x48, 
/*| X . x . X |*/  0xa8,
/*| . X . . X |*/  0x48, 
/*| . . X X X |*/  0x38,

//24 Delete
/*| 8 4 2 1 8 4 2 1 |*/
/*| X X . . X |*/  0xc8, 
/*| X X . X . |*/  0xd0, 
/*| . x x . . |*/  0x50,
/*| . . x . . |*/  0x20, 
/*| . x . x . |*/  0x50,
/*| X . . . X |*/  0x88,
/*| X . . . X |*/  0x88,

//25 Function 1
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x . . |*/  0xe0, 
/*| x . . . . |*/  0x80, 
/*| x x . . x |*/  0xc8,
/*| x . . x x |*/  0x98, 
/*| x . . . x |*/  0x88,
/*| . . . . x |*/  0x08,
/*| . . . . x |*/  0x08,

//26 Function 2
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x . . |*/  0xe0, 
/*| x . . . . |*/  0x80,
/*| x x . x x |*/  0xd8,
/*| x . . . x |*/  0x88, 
/*| x . . x x |*/  0x98,
/*| . . . x . |*/  0x10,
/*| . . . x x |*/  0x18,

//27 Function 3
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x . . |*/  0xe0, 
/*| x . . . . |*/  0x80, 
/*| x x . x x |*/  0xd8,
/*| x . . . x |*/  0x88, 
/*| x . . x x |*/  0x98,
/*| . . . . x |*/  0x08,
/*| . . . x x |*/  0x18,
//28 Function 4
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x . . |*/  0xe0, 
/*| x . . . . |*/  0x80, 
/*| x x . . x |*/  0xc8,
/*| x . . x x |*/  0x98, 
/*| x . x . x |*/  0xa8,
/*| . x x x x |*/  0x78,
/*| . . . . x |*/  0x08,
//29 Function 5
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x . . |*/  0xe0, 
/*| x . . . . |*/  0x80, 
/*| x x . x x |*/  0xd8,
/*| x . . x . |*/  0x90, 
/*| x . . x x |*/  0x98,
/*| . . . . x |*/  0x08,
/*| . . . x x |*/  0x18,

//30 Function 6
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x . . . |*/  0xe0, 
/*| x . . . . . |*/  0x80, 
/*| x x . x x . |*/  0xd8,
/*| x . x . . . |*/  0xa0, 
/*| x . x x . . |*/  0xb0,
/*| . . x . x . |*/  0x28,
/*| . . . x . . |*/  0x10,

//31 Function 7
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x . . |*/  0xe0, 
/*| x . . . . |*/  0x80, 
/*| x x . . . |*/  0xc0,
/*| x . x x x |*/  0xb8, 
/*| x . . . x |*/  0x88,
/*| . . . x . |*/  0x10,
/*| . . x . . |*/  0x20,

//127 Function 8
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x . . . |*/  0xe0, 
/*| x . . . . . |*/  0x80, 
/*| x x . x . . |*/  0xd0,
/*| x . x . x . |*/  0xa8, 
/*| x . . x . . |*/  0x90,
/*| . . x . x . |*/  0x28,
/*| . . . x . . |*/  0x10,

//128 Function 9
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x . . . |*/  0xe0, 
/*| x . . . . . |*/  0x80, 
/*| x x . x . . |*/  0xd0,
/*| x . x . x . |*/  0xa8, 
/*| x . . x x . |*/  0x98,
/*| . . . . x . |*/  0x08,
/*| . . x x . . |*/  0x30,

//129 Function 10
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x . . . |*/  0xe0, 
/*| x . . . . . |*/  0x80, 
/*| x x . . . . |*/  0xc0,
/*| x . . . . . |*/  0x80, 
/*| x x . . x . |*/  0xc8,
/*| . x . x . x |*/  0x54,
/*| . x . x . x |*/  0x54,
/*| . x . . x . |*/  0x48,

//130 Function 11
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x . . . |*/  0xe0, 
/*| x . . . . . |*/  0x80, 
/*| x x . . . . |*/  0xc0,
/*| x . . . . . |*/  0x80, 
/*| x . x . x . |*/  0xa8,
/*| . . x . x . |*/  0x28,
/*| . . x . x . |*/  0x28,
/*| . . x . x . |*/  0x28,

//131 Function 12
/*| 8 4 2 1 8 4 2 1 |*/
/*| x x x . . . |*/  0xe0, 
/*| x . . . . . |*/  0x80, 
/*| x x . . . . |*/  0xc0,
/*| x . x . x x |*/  0xac, 
/*| x . x . . x |*/  0xa4,
/*| . . x . x x |*/  0x2c,
/*| . . x . x . |*/  0x28,
/*| . . x . x x |*/  0x2c,

//132 Double less than  
/*| 8 4 2 1 8 4 2 1 |*/
/*| . . x . . x |*/  0x24, 
/*| . x . . x . |*/  0x48, 
/*| x . . x . . |*/  0x90,
/*| . x . . x . |*/  0x48, 
/*| . . x . . x |*/  0x24,

//132 Double greater than
/*| 8 4 2 1 8 4 2 1 |*/
/*| x . . x . . |*/  0x90, 
/*| . x . . x . |*/  0x48, 
/*| . . x . . x |*/  0x24,
/*| . x . . x . |*/  0x48, 
/*| x . . x . . |*/  0x90,

//133 Space Bar
/*| 8 4 2 1 8 4 2 1 |*/
/*| x . . . . x |*/  0x84, 
/*| x x x x x x |*/  0xfc,

//134 Escape
/*| 8 4 2 1 8 4 2 |*/
/*| x x . . . . . |*/  0xc0,
/*| x . . . . . . |*/  0x80,
/*| x x . x x . . |*/  0xd8,
/*| x . . x . . . |*/  0x90,
/*| x x . x x . . |*/  0xd8,
/*| . . . . x . . |*/  0x08,
/*| . . . x x . . |*/  0x18,

//135 Print Screen
/*| 8 4 2 1 8 4 2 |*/
/*| x x . . . . . |*/  0xc0,
/*| x . x . . . . |*/  0xa0,
/*| x x . x x . . |*/  0xd8,
/*| x . . x . . . |*/  0x90,
/*| x . . x x . . |*/  0x98,
/*| . . . . x . . |*/  0x08,
/*| . . . x x . . |*/  0x18,


//   Empty array for future expansion
/*| 8 4 2 1 8 4 2 1 |*/
/*| . . . . . . . |*/  0x00,
/*| . . . . . . . |*/  0x00,
/*| . . . . . . . |*/  0x00,
/*| . . . . . . . |*/  0x00,
/*| . . . . . . . |*/  0x00,
/*| . . . . . . . |*/  0x00,
/*| . . . . . . . |*/  0x00,
0x00};//One more byte just in case

const GFXglyph SymbolMono8pt7bGlyphs[] PROGMEM = {
  //Index,  W, H,xAdv,dX, dY
  {     0,  8, 7, 6, 0,0}, // 00 test square
  {     7,  8, 5, 6, 0,1}, // 01 Upper_Left_Arrow
  {    12,  8, 5, 6, 0,1}, // 02 Upper_Right_Arrow
  {    17,  8, 5, 6, 0,1},  // 03 lower left arrow
  {    22,  8, 5, 6, 0,1},  // 04 lower right arrow
  {    27,  8, 7, 6, 0,0},  // 05 power symbol
  {    34,  8, 5, 6, 0,1},  // 06 skip left
  {    39,  8, 5, 6, 0,1},  // 07 rewind
  {    44,  8, 5, 6, 2,1},  // 08 play
  {    49,  8, 5, 6, 0,1},  // 09 fast-forward
  {    54,  8, 5, 6, 0,1},  // 10 skip right
  {    59,  8, 5, 6, 0,1},  // 11 pause
  {    64,  8, 3, 6, 0,2},  // 12 Stop
  {    67,  8, 3, 6, 0,2},  // 13 ch up
  {    70,  8, 3, 6, 0,2},  // 14 ch down
  {    73,  8, 6, 6, 0,1},  // 15 page up
  {    79,  8, 6, 6, 0,1},  // 16 page down
  {    85,  8, 7, 6, 0,0},  // 17 Bluetooth
  {    92,  8, 6, 6, 0,0},  // 18 up Arrow
  {    98,  8, 6, 6, 0,0},  // 19 down arrow
  {   104,  8, 7, 6, 0,0},  // 20 left arrow
  {   111,  8, 7, 6, 0,0},  // 21 right arrow
  {   118,  8, 5, 6, 0,2},  // 22 Return
  {   123,  8, 5, 6, 0,1},  // 23 backspace
  {   128,  8, 7, 6, 0,0},  // 24 delete
  {   135,  8, 7, 6, 0,0},  // 25 F1
  {   142,  8, 7, 6, 0,0},  // 26 F2
  {   149,  8, 7, 6, 0,0},  // 27 F3
  {   156,  8, 7, 6, 0,0},  // 28 F4
  {   163,  8, 7, 6, 0,0},  // 29 F5
  {   170,  8, 7, 6, 0,0},  // 30 F6
  {   177,  8, 7, 6, 0,0},  // 31 F7
  {   184,  8, 7, 6, 0,0},  //127 F8
  {   191,  8, 7, 6, 0,0},  //128 F9
  {   198,  8, 8, 6, 0,0},  //129 F10
  {   206,  8, 8, 6, 0,0},  //130 F11
  {   214,  8, 8, 6, 0,0},  //131 F12
  {   222,  8, 5, 6, 0,1},  //132 double less than
  {   227,  8, 5, 6, 0,1},  //133 double greater than
  {   232,  8, 2, 6, 0,4},  //134 space bar
  {   234,  8, 7, 6, 0,0},  //135 Escape
  {   241,  8, 7, 6, 0,0},  //136 PrntScn
  {     0,  8, 7, 6, 0,0},//137
  {     0,  8, 7, 6, 0,0},//138
  {     0,  8, 7, 6, 0,0},//139
  {     0,  8, 7, 6, 0,0},//140
  {     0,  8, 7, 6, 0,0},//141
  {     0,  8, 7, 6, 0,0},//142
  {     0,  8, 7, 6, 0,0},//143
  {     0,  8, 7, 6, 0,0}};//144
  //Index,  W, H,xAdv,dX, dY
const GFXfont SymbolMono8pt7b PROGMEM = {
  (uint8_t  *)SymbolMono8pt7bBitmaps,
  (GFXglyph *)SymbolMono8pt7bGlyphs,
  0,48, 35 //ASCII start, ASCII stop,y Advance
};
#define MY_TEST_SQUARE 0
#define MY_UPPER_LEFT_ARROW 1
#define MY_UPPER_RIGHT_ARROW 2
#define MY_LOWER_LEFT_ARROW 3
#define MY_LOWER_RIGHT_ARROW 4
#define MY_POWER_SYMBOL 5
#define MY_SKIP_LEFT 6
#define MY_REWIND 7
#define MY_PLAY 8
#define MY_FF 9
#define MY_SKIP_RIGHT 10
#define MY_PAUSE 11
#define MY_STOP 12
#define MY_CH_UP 13
#define MY_CH_DOWN 14
#define MY_PAGE_UP 15
#define MY_PAGE_DOWN 16
#define MY_BLUETOOTH 17
#define MY_UP_ARROW 18
#define MY_DOWN_ARROW 19
#define MY_LEFT_ARROW 20
#define MY_RIGHT_ARROW 21
#define MY_RETURN 22
#define MY_BACKSPACE 23
#define MY_DELETE 24
#define MY_F1 25
#define MY_F2 26
#define MY_F3 27
#define MY_F4 28
#define MY_F5 29
#define MY_F6 30
#define MY_F7 31
#define MY_F8 127
#define MY_F9 128
#define MY_F10 129
#define MY_F11 130
#define MY_F12 131
#define MY_DOUBLE_LESS_THAN 132
#define MY_DOUBLE_GREATER_THAN 133
#define MY_SPACE_BAR 134
#define MY_ESCAPE 135
#define MY_PRINT_SCREEN 136
