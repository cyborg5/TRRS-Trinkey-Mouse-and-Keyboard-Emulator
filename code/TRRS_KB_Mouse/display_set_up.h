/*
 * This file includes all display specific information. If you want to port
 * this code to a different display you should be able to only change
 * this information.
 */
 
#include <SPI.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define DISPLAY_BLACK SSD1306_BLACK
#define DISPLAY_WHITE SSD1306_WHITE
#define DELTA_R  9
#define DELTA_C  7
#define BASE_C   0
#define BASE_R   0
#define COL_MAX 14  

//custom monospaced eight point font includes special characters not found in the standard
//GFX Library font.
#include "SymbolMono8pt7b.h"
void Initialize_Display(void){
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    DEBUG_PRINTLN("SSD1306 allocation failed");
    while(true); // Don't proceed, loop forever
  }
  display.display();  //show default Adafruit logo for two seconds
  delay(2000); 
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
};
