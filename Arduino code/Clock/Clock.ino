#include "LedControl.h"

//Vars
unsigned long delayFrame=100; //Frame rate
int displays = 4; //Number of displays
//Pins
int DIN = 12;
int CLK = 10;
int CS = 11;


LedControl lc=LedControl(DIN,CLK,CS,displays);


void setup() {
  /*
   * The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
   */

  for(int i=0;i<displays;i++){
    lc.shutdown(i,false);
    // Set the brightness to a medium values 
    lc.setIntensity(i,8);
    // and clear the display
    lc.clearDisplay(i);
  }
  
}

void animate(int currentTime){

  //Numbers 0-9
  int frames = 10;
  byte numbers[frames][8]=\
  {{B01111110,B01111110,B01100110,B01100110,B01100110,B01100110,B01111110,B01111110},\
  {B00111000,B01111000,B01111000,B00011000,B00011000,B00011000,B00011000,B00011000},\
  {B01111110,B01111110,B00000110,B00011110,B01111000,B01100000,B01111110,B01111110},\
  {B01111110,B01111110,B00000110,B00111110,B00111110,B00000110,B01111110,B01111110},\
  {B01100110,B01100110,B01111110,B01111110,B00000110,B00000110,B00000110,B00000110},\
  {B01111110,B01111110,B01100000,B01111100,B01111110,B00000110,B01111110,B01111110},\
  {B01111110,B01111110,B01100000,B01111110,B01111110,B01100110,B01111110,B01111110},\
  {B01111110,B01111110,B00000110,B00001100,B00011000,B00011000,B00011000,B00011000},\
  {B01111110,B01111110,B01100110,B01111110,B01111110,B01100110,B01111110,B01111110},\
  {B01111110,B01111110,B01100110,B01111110,B01111110,B00000110,B00000110,B00000110}};

  /* This is a mess
   *  
   *  h1/H1 here represent the furthest left digit of time, the first hour no,
   *  h2/H2 is the second digit and the same with the minutes e.g.
   *  0   2 : 3   5
   *  h1  h2  m1  m2
   */

  for(int time=currentTime; time<720; time++){
    //1 unit of time is 1 minute, 12*60=720
    int hour = time/60; //int division, no remainder
    int minute = time%60; //mod division, only remainder
  
    //Set first minute digit
    for(int row=0;row<8;row++){
      lc.setRow(0,row,numbers[(minute%10)][row]);
    }

    //Set second minute digit
    for(int row=0;row<8;row++){
      lc.setRow(1,row,numbers[(minute/10)][row]);
    }

    //Set hour digits
    if(hour>9){
      for(int row=0;row<8;row++){lc.setRow(3,row,numbers[1][row]);}
      for(int row=0;row<8;row++){lc.setRow(2,row,numbers[(hour-10)][row]);};
    }else{
      for(int row=0;row<8;row++){lc.setRow(3,row,numbers[0][row]);};
      for(int row=0;row<8;row++){lc.setRow(2,row,numbers[hour][row]);};
    }

    delay(60000);
    
  }
}

void loop() { 
  int h = 12;
  int m = 4;

  int currentTime = (h*60)+m;
  
  //example:
  //animate(11,50)
  animate(currentTime);
}
