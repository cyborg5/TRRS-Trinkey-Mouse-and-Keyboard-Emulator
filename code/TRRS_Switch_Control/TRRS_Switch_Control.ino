/*
 * This code goes with the Adafruit TRRS Trinkey
 * https://www.adafruit.com/product/5954
 * 
 * Connect from 2 to 3 Assistive Technology Buttons and connect it
 * to an iOS or android device using Switch Control
 * 
 * See learn.adafruit.com for details.
 * 
 * All files in his package are open source under Creative Commons CC BY-SA
 * 
 * Developed by Chris Young cy_borg5@cyborg5.com
 * http://tech.cyborg5.com/
 * 
 */
#include <Keyboard.h>
#include <HID.h>

//Sometimes when you reboot a computer, the attached board glitches.
//Use the SleepyDog library to detect a lockup and reboot if necessary.
#define USE_SLEEPY 1
#if (USE_SLEEPY)
  #include <Adafruit_SleepyDog.h>
#endif

#define MY_DEBUG 0        //change to 1 to turn on debug output to serial monitor
/*
 * Characters to be sent to switch controlled device.
 * You can modify the values to suit your needs.
 */
#define UP_PRESS      'u'
#define DOWN_PRESS    'd'
#define SELECT_PRESS  's'
#define LEFT_PRESS    'l'
#define RIGHT_PRESS   'r'
/***************************
 * Global Variables
 ***************************/
uint8_t Current_Buttons;  //The most recent results from Read_Buttons()
#include "my_stuff.h"
#include "my_inputs.h"
void Send_Keypress(uint8_t c) {
  Keyboard.press(c);  DEBUG_PRINT("Pressed="); DEBUG_PRINTLN(c);
  delay(100);//de-bounce
  while(Current_Buttons) {  //Keep reading until button designer longer pressed
    Read_Buttons ();
  }
  Keyboard.release(c);;  DEBUG_PRINT("Released="); DEBUG_PRINTLN(c);
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
  Keyboard.begin();
  Initialize_Buttons();
}
/*
 * does everything of course
 */
void loop() {
  if(Read_Buttons()) {  
    switch(Current_Buttons) {
      case PUSHED_RIGHT:  
        Send_Keypress(RIGHT_PRESS);
        break;
      case PUSHED_LEFT:   
        Send_Keypress(LEFT_PRESS);
        break;
      case PUSHED_SELECT: 
        Send_Keypress(SELECT_PRESS);
        break;
      case PUSHED_UP:     
        Send_Keypress(UP_PRESS);
        break;
      case PUSHED_DOWN:   
        Send_Keypress(DOWN_PRESS);
        break;
    };
  };
  #if (USE_SLEEPY)
    Watchdog.reset();
  #endif
}
