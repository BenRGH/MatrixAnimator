#include "LedControl.h"
#include <Wire.h>
#include "DS3231.h"

//This is required, does time stuff
RTClib RTC;

//Vars
unsigned long delayFrame=100; //Frame rate defined here in ms
int displays = 4; //Number of displays
int intensity = 7; //Brightness of displays
//Pins
int DIN = 12;
int CLK = 10;
int CS = 11;
//Time stuff
int currentTime; //currentTime is time in seconds, max is 86,399
int lastTime; //Required for checking changes
//Disp
LedControl lc = LedControl(DIN,CLK,CS,displays);


void setup() {
  Wire.begin(); //Start RTC stuff

  //The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  for(int i=0;i<displays;i++){
    lc.shutdown(i,false);
    // Set the brightness to a medium values 
    lc.setIntensity(i,intensity);
    // and clear the display
    lc.clearDisplay(i);
  }

  //Get current time
  DateTime RTCTime = RTC.now(); //Get the time provided by the RTC component
  //And then put it all into a messy big number which is the time in seconds from midnight
  currentTime = (RTCTime.hour()*3600) + (RTCTime.minute()*60) + RTCTime.second();
  
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

  
  for(int frame=0;frame<frames;frame++){
    //Each frame all displays are updated the same
    
    for(int disp=digitFromRight;disp>=0;){
      //Work from the furthest disp left
      
      for(int row=0;row<8;row++){
        //Draw
        lc.setRow(disp,row,anim[frame][row]);
      }
      
      disp--; //Go right
    }
    delay(15);//Changes the frame rate, 18 frames at 15ms delay is 270ms total
  }
}

void animate(){
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

  int currentTime_h = currentTime / 3600; //Gets hours from the number of seconds since midnight
  int currentTime_m = (currentTime - (currentTime_h * 3600)) / 60; //Gets minutes
  int lastTime_h = lastTime / 3600;
  int lastTime_m = (lastTime - (lastTime_h * 3600)) / 60;
  

  //Current time in digits
  int m2 = currentTime_m % 10; //Only remainder
  int m1 = currentTime_m / 10; //No remainder
  int h2 = currentTime_h % 10;
  int h1 = currentTime_h / 10;

  //Last time in digits
  int last_m2 = lastTime_m % 10;
  int last_m1 = lastTime_m / 10; 
  int last_h2 = lastTime_h % 10;
  int last_h1 = lastTime_h / 10;

  //if in doubt use an if
  //This plays the appropriate fizzle animation depending on degree of change
  if(h1 != last_h1){
    //Fizzle all the way left
    fizzle(3);
  }else if(h2 != last_h2){
    //Fizzle 3 digits left
    fizzle(2);
  }else if(m1 != last_m1){
    //Fizzle 2 digits left
    fizzle(1);
  }else if(m2 != last_m2){
    //Fizzle just rightmost digit
    fizzle(0);
  }else{
    delay(270);
  }
  
  //Example time 12:56
  
  printNum(0,m2); // 6
  printNum(1,m1); // 5
                  // :
  printNum(2,h2); // 2
  printNum(3,h1); // 1

  //Fancy fading every second on the minute displays
  /* removed for accuracy testing
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
  */

  //Total time so far is only 270ms so to make it 1s we add 730ms delay
  delay(730);

  lastTime = currentTime;
  
  if(currentTime < 86399){
    currentTime += 1;
  }else{
    currentTime = 0;
  }
  
}

void loop() { 
  animate();

}
