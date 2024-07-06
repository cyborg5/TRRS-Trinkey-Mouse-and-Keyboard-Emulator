/*
 * In this file we need to define a function "Read_Buttons()"
 * This function will be continuously called waiting for you to do something.
 * If you aren't doing anything, it returned zero. If you are pushing a button, it
 * returns a value from indicating all of the buttons that were pressed. 
 * There may be multiple buttons pressed at once.
 * 
 * It also sets the global variable "Current_Buttons" to the returned value.
 * 
 * This code presumes you're using 3 buttons labeled NEXT, PREVIOUS, and SELECT.
 * You can however get by with just SELECT and one of the other two buttons for a
 * 2 buttons solution.
 * 
 * If debugging is enabled you can enter commands through the serial monitor.
 *       'u'=Up, 'd'=Down, 'l'=Left, 'r'=Right, 's'=Select
 * Also define function "Initialize_Buttons()" which will be called by "setup()" at the beginning.
 */

/*
 * Everything below here is hardware specific
 */
//GPIO pin numbers for pushbuttons. Rearrange these to suit your application
#define PREVIOUS  PIN_TIP
#define SELECT    PIN_RING1
#define NEXT      PIN_RING2

//This macro encodes the three pushbuttons into a single value 0-7. 
//Note that digitalRead() will return "1" when the button is NOT pressed and
// returns "0" when it is pressed. That's the reason for the logical not "~" in the
// formula below.
#define  READ_SWITCHES (7&(~(digitalRead(PREVIOUS)*4+digitalRead(SELECT)*2+digitalRead(NEXT))) )

//Return codes from Read_Buttons(). 
#define PUSHED_NONE     0
#define PUSHED_LEFT     1
#define PUSHED_SELECT   2
#define PUSHED_RIGHT    4
#define PUSHED_DOWN     (PUSHED_RIGHT + PUSHED_SELECT)
#define PUSHED_UP       (PUSHED_LEFT  + PUSHED_SELECT)
//Not used but here just for illustrative purposes
#define PUSHED_ALL      (PUSHED_LEFT  + PUSHED_SELECT + PUSHED_RIGHT)
#define PUSHED_SPLIT    (PUSHED_RIGHT + PUSHED_LEFT)

//The time stamp when the buttons first started to be pressed.
uint32_t Start_of_Press;

uint8_t Read_Buttons() {
  //Save the most recent button press for future comparison
  uint8_t Previous_Buttons = Current_Buttons;
  //Length of time that buttons have been pressed
  uint32_t Length_of_Press;
  //The following statement is not a mistake. We want to get the value, save it in Current_Buttons and 
  //  if it is nonzero do something.
  if (Current_Buttons = READ_SWITCHES) {
    //At this point we know that one or more buttons is currently being pressed.
    if(Current_Buttons==Previous_Buttons) {
      //If the value is the same as last time we called Read_Buttons then compute how long we've been this way.
      Length_of_Press=millis()-Start_of_Press;
    } else {
      //If the button state was different from a risetime we checked, reset the clock.
      Length_of_Press=0; 
      Start_of_Press=millis();
    }
    //We want to use a chorded system in which pushing the buttons simultaneously
    // expands the number of types of button presses we can use.
    //The chances of pressing 2 buttons absolutely simultaneously is pretty slim 
    // so we continue to sample the buttons for 50 milliseconds and do a bitwise 
    // logical OR on the button states. That way if you press one button, then 
    // while holding it you press another one, and then while holding the second 
    // one you release the first one, it will register as a press of both buttons 
    // simultaneously. The bitwise OR also ensures that if the press is less than 50
    // milliseconds it will still register properly.
    uint8_t Sample;
    do {
      delay(50);  //We already know the buttons were pressed. Wait a fraction of a second.
      //Take a sample and bitwise OR
      Current_Buttons |= (Sample = READ_SWITCHES);
      Length_of_Press=millis()-Start_of_Press; //Recompute length of press
      if(Length_of_Press>200) {
        Sample=0;   //If we've been here long enough, get out
      }
    } while (Sample);
  } else {
    //Buttons are not pressed
    Previous_Buttons=Length_of_Press=0;
  }
//Alternate input method using serial monitor for debugging purposes
#if (MY_DEBUG)
  if(Serial.available ()) {
    uint8_t c= Serial.read ();
    switch  (c) {
      case 'u': Current_Buttons=PUSHED_UP; break;
      case 'd': Current_Buttons=PUSHED_DOWN; break;
      case 'l': Current_Buttons=PUSHED_LEFT; break;
      case 's': Current_Buttons=PUSHED_SELECT; break;
      case 'r': Current_Buttons=PUSHED_RIGHT;  break;
      default:  Current_Buttons=PUSHED_NONE; break;
    }
  }
#endif
  return  Current_Buttons;
};
void Initialize_Buttons(void) {
  Start_of_Press = 0; 
  pinMode (SELECT, INPUT_PULLUP);
  pinMode (NEXT, INPUT_PULLUP);
  pinMode (PREVIOUS, INPUT_PULLUP);
  pinMode (PIN_SLEEVE, OUTPUT);
  digitalWrite (PIN_SLEEVE,LOW);  //used as ground
};
