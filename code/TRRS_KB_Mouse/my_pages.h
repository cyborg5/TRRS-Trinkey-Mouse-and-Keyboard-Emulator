/*
 * In this file, we define the display pages and the functions associated with them
 */
//Display of keyboard commands needs special handling so that it properly 
// displays shifted characters. 
// This array maps on shifted display glyphs to their shifted value.
uint8_t Shifted [] = {
          0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 
         10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
         20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 
         //      sp   !   "   #   $   %   &   ' 
         30, 31, 32, 33, 34, 35, 36, 37, 38,'"',
       // (   )   *   +   ,   -   .   /   0   1  
         40, 41, 42, 43,'<','_','>','?',')','!',
       // 2   3   4   5   6   7   8   9   ;   ;  
         '@','#','$','%','^','&','*','(',':',59, 
         60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
         70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
         80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
         90,'{','|','}', 94, 95,'~','A','B','C',
        'D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W',
        'X','Y','Z',123,124,125,126,127};   
        
enum cmndtype_e: uint8_t //types of commands
{
  DO_NOTHING=0, DO_KB, DO_MOUSE, DO_CHANGE, DO_KB_MOD, DO_KB_TOG
};
enum mcmd_e: uint8_t //Mouse commands
{
  MS_NONE=0, MS_RELEASE_ALL, MS_UP_LEFT, MS_UP, MS_UP_RIGHT, MS_LEFT,
  MS_LEFT_CLICK, MS_RIGHT, MS_DOWN_LEFT, MS_DOWN, MS_DOWN_RIGHT,
  MS_RIGHT_CLICK, MS_LEFT_TOG, MS_RIGHT_TOG, MS_MIDDLE_TOG,
  MS_MIDDLE_CLICK, MS_WHEEL_DOWN, MS_WHEEL_UP, MS_SLOWER, MS_FASTER
};
enum pages_e: uint8_t //These are the names of the pages
{
  PAGE_KEYBOARD, PAGE_MOUSE, PAGE_ARROWS
};

#define NUM_OF_PAGES 3 

//Keyboard modifiers can be added together
#define KBM_NONE    0
#define KBM_SHIFT   1
#define KBM_CTRL    2
#define KBM_ALT     4
#define KBM_GUI     8
#define KBM_RELEASE 16

union KPMK_u {      //various kinds of commands
  uint8_t KeyPress; //which key to press
  pages_e Page;     //which page to change to
  mcmd_e  MouseCmd; //which mouse command to execute
  uint8_t KeyMod;   //which keyboard modifiers to press
};

//We will define a multi-dimension array of this type.
typedef struct cmnd {
  uint8_t     Glyph;  //character to be displayed
  KPMK_u      Command;//command to be executed
  cmndtype_e  Type;   //page change, keyboard, or mouse
  uint8_t     Mods;   //key press modifiers
} cmnd_t;
struct cmnd Current;      //The current command that the cursor rests on.

//macros to fill out the table because I'm too lazy to do all that typing
#define EMPTY_CMD       {' ',0,DO_NOTHING,0}
#define KB(g)           {g,g,DO_KB,0}       //keypress a printable character
#define MS(g,c)         {g,c,DO_MOUSE,0}    //mouse commands
#define CHANGE_CMD(g,c) {g,c,DO_CHANGE,0}   //change the page
#define KB_SPL(g,c)     {g,c,DO_KB,0}       //keypress of a non-printable character
#define KBT(g,c)        {g,c,DO_KB_TOG,0}   //toggle shift, control, alt, or GUI
#define KBM(g,c,m)      {g,c,DO_KB_MOD,m}   //keypress with modifier such as ctrl+c or alt+tab
const uint8_t Num_Cols_In_Page [NUM_OF_PAGES]= {14, 11, 10};

const cmnd_t MyCommands[][COL_MAX]= {
  //page change commands -- keyboard, mouse, arrows. Appears at the top of every page
  #define ROW_PAGES 0
  {CHANGE_CMD('K',PAGE_KEYBOARD), CHANGE_CMD('M',PAGE_MOUSE),  CHANGE_CMD('A', PAGE_ARROWS), EMPTY_CMD, 
    EMPTY_CMD, EMPTY_CMD, EMPTY_CMD, EMPTY_CMD, EMPTY_CMD, EMPTY_CMD, EMPTY_CMD, EMPTY_CMD, EMPTY_CMD, EMPTY_CMD},

  //keyboard page has 6 additional rows
  #define ROW_KB_1  1
  {KB('`'), KB('1'), KB('2'), KB('3'), KB('4'), KB('5'), KB('6'), 
   KB('7'), KB('8'), KB('9'), KB('0'), KB('-'), KB('='), KB_SPL(MY_BACKSPACE, KEY_BACKSPACE)},
  #define ROW_KB_2  2
  {KB('q'), KB('w'), KB('e'), KB('r'), KB('t'), KB('y'), KB('u'),
   KB('i'), KB('o'), KB('p'), KB('['), KB(']'), KB('\\'), KB_SPL(MY_DELETE,KEY_DELETE)},
  #define ROW_KB_3  3
  {KB('a'), KB('s'), KB('d'), KB('f'), KB('g'), KB('h'), KB('j'),
   KB('k'), KB('l'), KB(';'), KB('\''), KB_SPL(MY_RETURN,KEY_RETURN),KB_SPL(MY_SPACE_BAR,' '), EMPTY_CMD},
  #define ROW_KB_4  4
  {KB('z'), KB('x'), KB('c'), KB('v'), KB('b'), KB('n'), KB('m'),
   KB(','), KB('.'), KB('/'), KBT('S',KBM_SHIFT), KBT('C',KBM_CTRL), KBT('A',KBM_ALT), 
   KBT('G',KBM_GUI)},
  #define ROW_KB_5  5
  {KB_SPL(MY_SKIP_LEFT,KEY_HOME), KB_SPL(MY_UP_ARROW,KEY_UP_ARROW), KB_SPL(MY_PAGE_UP,KEY_PAGE_UP), 
   KB_SPL(MY_LEFT_ARROW,KEY_LEFT_ARROW), KB_SPL(MY_RETURN,KEY_RETURN), KB_SPL(MY_RIGHT_ARROW,KEY_RIGHT_ARROW),
   KB_SPL(MY_SKIP_RIGHT,KEY_END), KB_SPL(MY_DOWN_ARROW,KEY_DOWN_ARROW),
   KB_SPL(MY_PAGE_DOWN,KEY_PAGE_DOWN), KB_SPL('g',KEY_LEFT_GUI), KBT('0',KBM_RELEASE),
   KB_SPL(MY_ESCAPE,KEY_ESC), KB_SPL(MY_PRINT_SCREEN,KEY_PRINT_SCREEN), EMPTY_CMD},
  #define ROW_KB_6  6
  {KB_SPL(MY_F1,KEY_F1), KB_SPL(MY_F2,KEY_F2), KB_SPL(MY_F3,KEY_F3), KB_SPL(MY_F4,KEY_F4), 
   KB_SPL(MY_F5,KEY_F5), KB_SPL(MY_F6,KEY_F6), KB_SPL(MY_F7,KEY_F7), KB_SPL(MY_F8,KEY_F8), 
   KB_SPL(MY_F9,KEY_F9), KB_SPL(MY_F10,KEY_F10), KB_SPL(MY_F11,KEY_F11), KB_SPL(MY_F12,KEY_F12),
   EMPTY_CMD, EMPTY_CMD}, 

  //Mouse page consists of 2 additional rows
  #define ROW_MS_1  7
  {MS(MY_UPPER_LEFT_ARROW,MS_UP_LEFT), MS(MY_UP_ARROW,MS_UP), MS(MY_UPPER_RIGHT_ARROW,MS_UP_RIGHT), 
   MS(MY_LEFT_ARROW,MS_LEFT), MS('l',MS_LEFT_CLICK), MS(MY_RIGHT_ARROW,MS_RIGHT),
   MS(MY_LOWER_LEFT_ARROW,MS_DOWN_LEFT), MS(MY_DOWN_ARROW,MS_DOWN), MS(MY_LOWER_RIGHT_ARROW,MS_DOWN_RIGHT), 
   MS('r',MS_RIGHT_CLICK),MS('0',MS_RELEASE_ALL)},
  #define ROW_MS_2  8
  {MS('L',MS_LEFT_TOG), MS('R',MS_RIGHT_TOG), MS('M',MS_MIDDLE_TOG), MS('m',MS_MIDDLE_CLICK),
   MS('w',MS_WHEEL_DOWN), MS('W',MS_WHEEL_UP), KBT('S',KBM_SHIFT), 
   KBT('C',KBM_CTRL), KBT('A',KBM_ALT), MS('f',MS_FASTER), MS('s',MS_SLOWER)}, 

  //Arrow page consists of 3 additional rows
  #define ROW_AR_1  9
  {KB_SPL(MY_SKIP_LEFT,KEY_HOME), KB_SPL(MY_UP_ARROW,KEY_UP_ARROW), KB_SPL(MY_PAGE_UP,KEY_PAGE_UP), 
   KB_SPL(MY_LEFT_ARROW,KEY_LEFT_ARROW), KB_SPL(MY_RETURN,KEY_RETURN), KB_SPL(MY_RIGHT_ARROW,KEY_RIGHT_ARROW), 
   KB_SPL(MY_SKIP_RIGHT,KEY_END), KB_SPL(MY_DOWN_ARROW,KEY_DOWN_ARROW), KB_SPL(MY_PAGE_DOWN,KEY_PAGE_DOWN), 
   KB_SPL(MY_SPACE_BAR,'_')}, 
  #define ROW_AR_2  10
  {KBM('z','z',KBM_CTRL), KBM('y','y',KBM_CTRL), KBM('x','x',KBM_CTRL), 
   KBM('c','c',KBM_CTRL), KBM('v','v',KBM_CTRL), KB_SPL(MY_ESCAPE,KEY_ESC), 
   KB_SPL(MY_BACKSPACE,KEY_BACKSPACE), KB_SPL('i',KEY_INSERT), KB_SPL(MY_DELETE,KEY_DELETE),
   KB_SPL('t',KEY_TAB)},
  #define ROW_AR_3  11
  {KBT('S',KBM_SHIFT), KBT('C',KBM_CTRL), KBT('A',KBM_ALT), 
   KBT('G',KBM_GUI), KB_SPL('g',KEY_LEFT_GUI),KBT('0',KBM_RELEASE),
   KBM('t',KEY_TAB,KBM_ALT),
   KBM (MY_SKIP_LEFT,KEY_LEFT_ARROW,KBM_ALT+KBM_GUI),//dock window left with ALT+WIN+ left arrow
   KBM (MY_SKIP_RIGHT,KEY_RIGHT_ARROW,KBM_ALT+KBM_GUI),//dock window right with ALT+WIN+ right arrow
   EMPTY_CMD},              
   
 //Extras: just in case
  {EMPTY_CMD,EMPTY_CMD,EMPTY_CMD,EMPTY_CMD,EMPTY_CMD,EMPTY_CMD,EMPTY_CMD,
   EMPTY_CMD,EMPTY_CMD,EMPTY_CMD,EMPTY_CMD,EMPTY_CMD,EMPTY_CMD,EMPTY_CMD}
};
const char Num_Rows_in_Page[]= {7,3,4};

//Define which pages contain which rows. Note each page begins with the page change row
const uint8_t Pages [] [10]= {
  /*Keyboard*/{ROW_PAGES, ROW_KB_1,ROW_KB_2,ROW_KB_3,ROW_KB_4,ROW_KB_5,ROW_KB_6},
  /*Mouse*/   {ROW_PAGES, ROW_MS_1, ROW_MS_2},
  /*arrows*/  {ROW_PAGES, ROW_AR_1, ROW_AR_2, ROW_AR_3}
};
