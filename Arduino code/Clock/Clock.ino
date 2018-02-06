#include "LedControl.h"
#include <Wire.h>
#include "DS3231.h"

RTClib RTC;

//Vars
unsigned long delayFrame=100; //Frame rate
int displays = 4; //Number of displays
//Pins
int DIN = 12;
int CLK = 10;
int CS = 11;

DateTime lastTime; //Required for checking changes


LedControl lc=LedControl(DIN,CLK,CS,displays);


void setup() {
  Wire.begin(); //Start RTC stuff

  //The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  for(int i=0;i<displays;i++){
    lc.shutdown(i,false);
    // Set the brightness to a medium values 
    lc.setIntensity(i,8);
    // and clear the display
    lc.clearDisplay(i);
  }

  lastTime = RTC.now();
  
}

void printNum(int disp, int num){
  //Simply prints the number row by row to the display specified
  
  //Numbers 0-9
  int frames = 10;
  byte number[frames][8]=\
  {{B01111110,B01111110,B01100110,B01100110,B01100110,B01100110,B01111110,B01111110},\
  {B00011000,B00111000,B01111000,B00011000,B00011000,B00011000,B00011000,B00011000},\
  {B01111110,B01111110,B00000110,B00011110,B01111000,B01100000,B01111110,B01111110},\
  {B01111110,B01111110,B00000110,B00111110,B00111110,B00000110,B01111110,B01111110},\
  {B01100110,B01100110,B01111110,B01111110,B00000110,B00000110,B00000110,B00000110},\
  {B01111110,B01111110,B01100000,B01111100,B01111110,B00000110,B01111110,B01111110},\
  {B01111110,B01111110,B01100000,B01111110,B01111110,B01100110,B01111110,B01111110},\
  {B01111110,B01111110,B00000110,B00001100,B00011000,B00011000,B00011000,B00011000},\
  {B01111110,B01111110,B01100110,B01111110,B01111110,B01100110,B01111110,B01111110},\
  {B01111110,B01111110,B01100110,B01111110,B01111110,B00000110,B00000110,B00000110}};

  for(int row=0;row<8;row++){lc.setRow(disp,row,number[num][row]);}
  
}

void fizzle(int digitFromRight){
  //Plays Fizzle animation on the selected displays

  int frames = 18;
  byte anim[frames][8]=\
  {{B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},\
  {B11111111,B01111101,B11111111,B11111111,B11111111,B10111111,B11111111,B11111011},\
  {B11111111,B01111101,B11101111,B11111111,B11111101,B10111111,B11111111,B10111011},\
  {B11110111,B01111101,B11101111,B11111111,B11111101,B10101111,B11111111,B10111001},\
  {B11110111,B01111101,B01100111,B11111111,B11111001,B10101111,B11111111,B10111000},\
  {B11110111,B01011101,B01100111,B11111110,B10111001,B10101111,B11110111,B10111000},\
  {B11110110,B01011101,B01100101,B11101110,B10111001,B10101101,B11110111,B10111000},\
  {B11110110,B00011101,B01100101,B11101110,B10111001,B00101100,B11110111,B10101000},\
  {B01110110,B00010101,B01100101,B11101110,B10111001,B00101100,B11010111,B00101000},\
  {B01110010,B00010101,B01100101,B11100110,B10111000,B00101100,B11010011,B00101000},\
  {B01010010,B00010101,B00100101,B11000110,B10111000,B00101000,B11010011,B00101000},\
  {B01010010,B00010100,B00100101,B11000010,B10101000,B00101000,B10010011,B00101000},\
  {B01010010,B00000000,B00100101,B11000010,B10001000,B00101000,B10010010,B00101000},\
  {B00010010,B00000000,B00100100,B10000010,B10001000,B00101000,B10000010,B00101000},\
  {B00010000,B00000000,B00100100,B10000010,B10000000,B00001000,B10000010,B00100000},\
  {B00000000,B00000000,B00000100,B10000000,B10000000,B00001000,B10000000,B00100000},\
  {B00000000,B00000000,B00000000,B10000000,B00000000,B00000000,B10000000,B00000000},\
  {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000}};

  for(int disp=0;disp<=digitFromRight;disp++){
    for(int frame=0;frame<frames;frame++){
      for(int row=0;row<8;row++){lc.setRow(disp,row,anim[frame][row]);}
      delay(10);
    }
    delay(40);
  }
}

void animate(DateTime now){
  /* This is a mess
   * 
   * The display is ordered as follows:
   * [3][2][1][0]--cables
   *  1  2 :5  6 
   *  
   * Print each digit individually because it's easier that way.
   *  
   * We work from right to left so the first digit (m2) is the second 
   * digit of minutes, the second digit (m1) is the first digit of minutes,
   * same goes for hours.
   * 
  */

  //Current time in digits
  int m2 = now.minute() % 10; //Only remainder
  int m1 = now.minute() / 10; //No remainder
  int h2 = now.hour() % 10;
  int h1 = now.hour() / 10;

  //Last time in digits
  int last_m2 = lastTime.minute() % 10;
  int last_m1 = lastTime.minute() / 10; 
  int last_h2 = lastTime.hour() % 10;
  int last_h1 = lastTime.hour() / 10;

  //if in doubt use an if
  //This plays the appropriate fizzle animation depending on degree of change
  if(m2 > last_m2){
    if(m1 > last_m1){
      if(h2 > last_h2){
        if(h1 > last_h1){
          //Fizzle all the way left
          fizzle(3);
        }
        //Fizzle 3 digits left
        fizzle(2);
      }
      //Fizzle 2 digits left
      fizzle(1);
    }
    //Fizzle rightmost digit
    fizzle(0);
  }

  lastTime = now;
  

  //Example time 12:56
  
  printNum(0,m2); // 6
  printNum(1,m1); // 5
  printNum(2,h2); // 2
  printNum(3,h1); // 1

  //fancy fading every second on the minute displays
  for(int i = 8; i>3; i--){
    //Darken
    lc.setIntensity(0,i);
    lc.setIntensity(1,i);
    delay(100);
  }
  for(int i = 3; i<8; i++){
    //Lighten
    lc.setIntensity(0,i);
    lc.setIntensity(1,i);
    delay(100);
  }
}

void loop() { 
  //Get current time
  DateTime now = RTC.now();

  //Pass it to the display animator
  animate(now);
}
