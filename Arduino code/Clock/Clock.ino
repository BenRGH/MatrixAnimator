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
  int m2 = now.minute() % 10; //Only remainder
  int m1 = now.minute() / 10; //No remainder
  int h2 = now.hour() % 10;
  int h1 = now.hour() / 10;

  //Example time 12:56
  
  printNum(0,m2); // 6
  printNum(1,m1); // 5
  printNum(2,h2); // 2
  printNum(3,h1); // 1

  //fancy fading second animation
  for(int i = 8; i>3; i--){
    //Darken
    lc.setIntensity(0,i);
    lc.setIntensity(1,i);
    delay(100);
  }
  for(int i = 3; i<8; i++){
    //Lighten
    
    //Minute displays
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
