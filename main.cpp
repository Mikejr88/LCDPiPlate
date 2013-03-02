#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "Adafruit_RGBLCDShield.h"

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

int main(int argc, char *argv[])
{
	Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
	
	lcd.begin(16, 2);

	lcd.setBacklight(RED);
	lcd.clear();
	lcd.home();
	lcd.setCursor(0,0);
	lcd.myPrint("Hello World");
	
	int count = 0;
	for(int i = 0; i < 20; i++){
		usleep(300000);
		if(count < 5){
			lcd.scrollDisplayRight();
		}
		count++;
		if(count > 5){
			lcd.scrollDisplayLeft();
		}
		if(count > 9) count = 0;
	}
	
	uint8_t buttons = lcd.readButtons();

	while(!(buttons & BUTTON_SELECT)){
		if (buttons) {
			if (buttons & BUTTON_LEFT) {
				lcd.scrollDisplayLeft();
				lcd.setBacklight(GREEN);
			}
			if (buttons & BUTTON_RIGHT) {
				lcd.scrollDisplayRight();
				lcd.setBacklight(TEAL);
			}
		}
		buttons = lcd.readButtons();
		usleep(90000);
    }
    
	return 0;
}
