/*
 * This code goes with the Adafruit TRRS Trinkey
 * https://www.adafruit.com/product/5954
 * 
 * Connect from 2 to 3 Assistive Technology Buttons and it will emulate
 * a USB keyboard and mouse. Also requires the Monochrome 1.3" 128x64
 * OLED graphic display with STEMMA QT connector
 * https://www.adafruit.com/product/938
 * 
 * See learn.adafruit.com for details.
 * 
 * All files in his package are open source under Creative Commons CC BY-SA
 * 
 * Developed by Chris Young cy_borg5@cyborg5.com
 * http://tech.cyborg5.com/
 * 
 */
/*
 * Some values you can customize
 */
#define DEFAULT_SPEED 10  //default mouse speed
#define SELECT_SPEED 200  //delay when pushing the SELECT button
#define UP_AND_DOWN_SPEED 300 //delay when navigating up-and-down
#define LEFT_AND_SPEED 150
#define MY_DEBUG 0        //change to 1 to turn on debug output to serial monitor
/***************************
 * Global Variables
 ***************************/
uint8_t Row, Col;   //Current position of the cursor.
uint8_t pRow, pCol; //Previous position of the cursor. 
uint8_t Num_Rows;   //The number of rows in the current page.
uint8_t Num_Cols;   //The width of the current page.
uint8_t Page;       //Currently displayed page
uint8_t Speed;      //Mouse speed per button press
uint8_t Current_Buttons;  //The most recent results from Read_Buttons()
//Status of modifier keys and mouse button toggles
bool is_shifted, is_alt, is_ctrl, is_gui, is_left, is_right, is_middle;

#include <Mouse.h>
#include <Keyboard.h>
#include <HID.h>
#include "my_stuff.h"       //Debug print macros
#include "display_set_up.h" //Display specific code. Can be modified for use with other displays.
#include "my_pages.h"       //Pages of commands for the menu
#include "my_inputs.h"      //Assign buttons to different versions. Customize as needed.
//Sometimes when you reboot a computer, the attached board glitches.
//Use the SleepyDog library to detect a lockup and reboot if necessary.
#define USE_SLEEPY 1
#if (USE_SLEEPY)
  #include <Adafruit_SleepyDog.h>
#endif
    
/*  
 *   Displays the command character at the specified row and column
 */
void Show_Cmd (uint8_t r, uint8_t c) {
  uint16_t fg,bg,Glyph; //Foreground color, background, and character to be displayed
  Glyph=MyCommands[Pages[Page][r]][c].Glyph;
  if(is_shifted && (MyCommands[Pages[Page][r]][c].Type==DO_KB) && (Glyph<127)) {
    Glyph= Shifted[Glyph];
  };  
  if ( (r==Row) && (c==Col)) {//This is a cursor so reverse the colors
    fg=DISPLAY_BLACK;      bg=DISPLAY_WHITE;
    //To the right of the last column is a pair of virtual columns that allow you to 
    //go up or down a row without having to use chords.
    if(c==(Num_Cols+1)) { //Go 2 presses right of the last command and select to go up
      c--;
      Glyph=MY_UP_ARROW;
    } else if(c==Num_Cols) { //Go one press right of the last command and select to go down
      Glyph=MY_DOWN_ARROW;
    }
  } else {//Not a cursor
    fg=DISPLAY_WHITE;    bg=DISPLAY_BLACK;    
    //If we are in a virtual column, and we know we are not a cursor it means we need to
    //  erase the up or down arrow that was displayed.
    if(c==(Num_Cols+1)) c--;  //if we are in the 2nd virtual column, backup one
    if(c==Num_Cols) Glyph=' ';//printing a space does nothing.
  }
  // Draw background rectangle to erase previous character
  display.fillRect(DELTA_C*c-1, DELTA_R*r, DELTA_C+1, DELTA_R,bg);
  if ( (Glyph>=32) && (Glyph<=126) ) {  //decide which font to use
    display.setFont();//anything 32-126 use standard font
  } else {
    display.setFont(&SymbolMono8pt7b); //use symbol font
    if (Glyph> 126) {//remap anything above 127 to the range 32 and up
      Glyph-=(127-32);
    }
  }
  display.drawChar(BASE_C+c*DELTA_C, BASE_R+r*DELTA_R,Glyph,fg,bg,1);
  display.display();
  display.setFont();//reset font to defaut
}
/*
 * After every move of the cursor,  rewrite the character normally and then
 * redraw the current location inverted
 */
void Update_Cursor() {
  Show_Cmd(pRow,pCol);  //Erase the previous cursor
  Show_Cmd(Row,Col);    //Draw the new cursor
  pRow=Row;pCol=Col;    //Record the cursor current position so we can erase it next time
};
/*
 * In the far right column we display the letters S,C,A,G,L,R, or M
 * to indicate the status of the mouse and keyboard toggleu
 */
void Show_Indicators (void) {
  #define X (BASE_C+16*DELTA_C)
  display.fillRect(X,0,DELTA_C+1,DELTA_R*7,DISPLAY_BLACK);//Erase indicators before redraw
  if (is_shifted) {display.setCursor(X,0); display.write('S');};
  if (is_ctrl)    {display.setCursor(X,DELTA_R*1); display.write('C');};
  if (is_alt)     {display.setCursor(X,DELTA_R*2); display.write('A');};
  if (is_gui)     {display.setCursor(X,DELTA_R*3); display.write('G');};
  if (is_left)    {display.setCursor(X,DELTA_R*4); display.write('L');};
  if (is_right)   {display.setCursor(X,DELTA_R*5); display.write('R');};
  if (is_middle)  {display.setCursor(X,DELTA_R*6); display.write('M');};
  display.display();
};

/*
 * Erase the entire screen and draw it from scratch. Used when switching pages or initializing
 */
void Display_Entire_Page (void) {
  Num_Cols = Num_Cols_In_Page[Page]; //The width of the current page
  display.fillScreen(DISPLAY_BLACK);
  Row = 1; Col = 0; pRow=1; pCol=0;
  Num_Rows = Num_Rows_in_Page[Page]; 
  uint8_t i,j;
  for (i = 0; i < Num_Rows; i++) {
    for (j =0; j < Num_Cols; j++) {
      Show_Cmd(i,j);
    }
  };
  Show_Indicators();
};
/*
 * When adjusting mouse speed, display a message at the bottom showing current speed
 */
void Show_Speed(void) {
  //Erase previous text before redraw
  display.fillRect(0,DELTA_R*6-1,DELTA_C*18, DELTA_R+2,DISPLAY_BLACK);
  display.setCursor(5,6*DELTA_R); 
  display.print("Mouse Speed:");display.print(Speed); display.print(" ");
  display.display();
};

/*
 * These functions perform up, down, left, and right cursor movements
 */
void Do_Up() {
  Row = (Row - 1 + Num_Rows) % Num_Rows; Update_Cursor();
};
void Do_Down () {
  ++Row;
  Row = Row % Num_Rows; Update_Cursor();
};
void Do_Right () {
  Col = (Col + 1) % (Num_Cols+2); Update_Cursor();
};
void Do_Left () {
  Col = (Col - 1 + Num_Cols+2) % (Num_Cols+2); Update_Cursor();
};
/*
 * Perform pressing of SELECT button. Function depends on context.
 */
void Do_Select () {
  uint8_t R,C;    //Temporary cursor storage
  if(Col==Num_Cols) {  //If we are in the first virtual column then go down
    Do_Down();
    delay(UP_AND_DOWN_SPEED);
    return;
  } else if(Col==(Num_Cols+1)) { //If we are in the second virtual column then go up
    Do_Up();
    delay(UP_AND_DOWN_SPEED);
    return;
  }
  //Pick the current command out of the command table
  Current=MyCommands[Pages[Page][Row]][Col];
  switch(Current.Type) {
    case DO_CHANGE:   //Change to a different page
      Page=Current.Command.Page;
      Display_Entire_Page();
      break;
    case DO_KB:   //basic unmodified keypress and release
      Keyboard.write(Current.Command.KeyPress);
      break;
    case DO_KB_TOG:   //Toggle a modifier key
      switch (Current.Command.KeyPress) {
        case KBM_SHIFT:
          if (is_shifted) Keyboard.release (KEY_LEFT_SHIFT); else Keyboard.press(KEY_LEFT_SHIFT);
          is_shifted=!is_shifted;
          R=Row;  C=Col;
          Display_Entire_Page();  //Need to redraw the page to show shifted characters
          Row=R; Col=C;
          Update_Cursor();
          break; 
        case KBM_CTRL:
          if (is_shifted) Keyboard.release (KEY_LEFT_CTRL); else Keyboard.press(KEY_LEFT_CTRL);
          is_ctrl=!is_ctrl; 
          break;
        case KBM_ALT:
          if (is_shifted) Keyboard.release (KEY_LEFT_ALT); else Keyboard.press(KEY_LEFT_ALT);
          is_alt=!is_alt;
          break;
        case KBM_GUI: //Windows key or Command (⌘) on Mac
          if (is_shifted) Keyboard.release (KEY_LEFT_GUI); else Keyboard.press(KEY_LEFT_GUI);
          is_gui=!is_gui;
          break; 
        case KBM_RELEASE:
          bool was_shifted=is_shifted;
          is_shifted=is_ctrl=is_alt=is_gui=false;
          Keyboard.releaseAll();
          if (was_shifted){
            R=Row;  C=Col;
            Display_Entire_Page();
            Row=R; Col=C;
            Update_Cursor();
          }
          break;
      };
      Show_Indicators();
      break;
    case DO_KB_MOD:   //Press a key with a modifier such as Ctrl+c or Alt+tab
      if(Current.Mods & KBM_SHIFT) Keyboard.press(KEY_LEFT_SHIFT);
      if(Current.Mods & KBM_CTRL) Keyboard.press(KEY_LEFT_CTRL);
      if(Current.Mods & KBM_ALT) Keyboard.press(KEY_LEFT_ALT);
      if(Current.Mods & KBM_GUI) Keyboard.press(KEY_LEFT_GUI);
      Keyboard.write(Current.Command.KeyPress);
      if(Current.Mods & KBM_SHIFT) Keyboard.release(KEY_LEFT_SHIFT);
      if(Current.Mods & KBM_CTRL) Keyboard.release(KEY_LEFT_CTRL);
      if(Current.Mods & KBM_ALT) Keyboard.release(KEY_LEFT_ALT);
      if(Current.Mods & KBM_GUI) Keyboard.release(KEY_LEFT_GUI);
      break;
    case DO_MOUSE:    //Mouse commands
      switch(Current.Command.MouseCmd) {
        case MS_RELEASE_ALL: 
          Mouse.release(MOUSE_LEFT);    is_left=false;
          Mouse.release(MOUSE_RIGHT);   is_right=false;
          Mouse.release(MOUSE_MIDDLE);  is_middle=false;
          Show_Indicators();
          break;
        case MS_UP_LEFT:    Mouse.move(-Speed,-Speed,0);  break;
        case MS_UP:         Mouse.move(0,-Speed,0);       break;
        case MS_UP_RIGHT:   Mouse.move(Speed,-Speed,0);   break;
        case MS_LEFT:       Mouse.move(-Speed,0,0);       break;
        case MS_LEFT_CLICK: Mouse.click(MOUSE_LEFT);      break;
        case MS_RIGHT:      Mouse.move(Speed,0,0);        break;
        case MS_DOWN_LEFT:  Mouse.move(-Speed,Speed,0);   break;
        case MS_DOWN:       Mouse.move(0,Speed,0);        break;
        case MS_DOWN_RIGHT: Mouse.move(Speed,Speed,0);    break;
        case MS_RIGHT_CLICK:Mouse.click(MOUSE_RIGHT);     break;
        case MS_LEFT_TOG:
          if (is_left) Mouse.release(MOUSE_LEFT); else Mouse.press(MOUSE_LEFT);
          is_left=!is_left; delay(SELECT_SPEED);
          Show_Indicators();
          break;
        case MS_RIGHT_TOG:
          if (is_right) Mouse.release(MOUSE_RIGHT); else Mouse.press(MOUSE_RIGHT);
          is_right=!is_right;
          Show_Indicators(); delay(SELECT_SPEED);
          break;
        case MS_MIDDLE_TOG:
          if (is_middle) Mouse.release(MOUSE_MIDDLE); else Mouse.press(MOUSE_MIDDLE);
          is_middle=!is_middle; delay(SELECT_SPEED);
          Show_Indicators();
          break;
        case MS_MIDDLE_CLICK: Mouse.click(MOUSE_MIDDLE); break;
        case MS_WHEEL_DOWN:   Mouse.move(0,0,-Speed);    break;
        case MS_WHEEL_UP:     Mouse.move(0,0,Speed);     break;
        case MS_SLOWER: Speed--; Show_Speed(); break;
        case MS_FASTER: Speed++; Show_Speed(); break;
      };
      break;
  };
};

/*
 * Initialize everything
 */
void setup() {
  #if (MY_DEBUG)
    Serial.begin(9600);while (! Serial) {};
  #endif
  #if (USE_SLEEPY)
    int countdownMS = Watchdog.enable(20000);
    //DEBUG_PRINT("Watchdog Enabled=");DEBUG_PRINTLN(countdownMS);
  #endif
  Mouse.begin();
  Keyboard.begin();
  Initialize_Buttons();
  Initialize_Display();
  is_shifted=is_alt=is_ctrl=is_gui=is_left=is_right=is_middle=0;
  Speed=DEFAULT_SPEED;
  Page=PAGE_KEYBOARD;
  Display_Entire_Page();
}
/*
 * does everything of course
 */
void loop() {
  if(Read_Buttons()) {  //If buttons were pressed, handle cursor and select commands
    switch(Current_Buttons) {
      case PUSHED_RIGHT:  
        Do_Right();   delay(LEFT_AND_SPEED); 
        break;
      case PUSHED_LEFT:   
        Do_Left();    delay(LEFT_AND_SPEED); 
        break;
      case PUSHED_SELECT: 
        Do_Select();  delay(SELECT_SPEED); 
        break;
      case PUSHED_UP:     
        Do_Up();      delay(UP_AND_DOWN_SPEED);
        break;
      case PUSHED_DOWN:   
        Do_Down();    delay(UP_AND_DOWN_SPEED);
        break;
    };
  };
  #if (USE_SLEEPY)
    Watchdog.reset();
  #endif
}
