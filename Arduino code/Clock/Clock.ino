#include "LedControl.h"
#include <Wire.h>
#include "DS3231.h"

DS3231 Clock;

//Vars
int displays = 4; //Number of displays
int intensity = 5; //Brightness of displays
//Pins
int DIN = 12;
int CLK = 10;
int CS = 11;
int AButn = 9;
int BButn = 8;


LedControl lc=LedControl(DIN,CLK,CS,displays);


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

  pinMode(AButn, INPUT_PULLUP);  
  pinMode(BButn, INPUT_PULLUP);


  Serial.begin(9600); //REMOVE THIS AFTER DEBUG!
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

void printLetter(int disp, int let){
  //Prints the specified letter to the specified display

  //18 letter alphabet (only chars needed):
  //ACDEFHJLMNOPRSTUWY
  int frames = 18;
  byte letter[frames][8]=\
  {{B11111111,B11111111,B11000011,B11000011,B11111111,B11111111,B11000011,B11000011},\
  {B11111111,B11111111,B11000000,B11000000,B11000000,B11000000,B11111111,B11111111},\
  {B11111110,B11000111,B11000011,B11000011,B11000011,B11000011,B11000111,B11111110},\
  {B11111111,B11111111,B11000000,B11111111,B11111111,B11000000,B11111111,B11111111},\
  {B11111111,B11111111,B11000000,B11111111,B11111111,B11000000,B11000000,B11000000},\
  {B11000011,B11000011,B11000011,B11111111,B11111111,B11000011,B11000011,B11000011},\
  {B11111111,B11111111,B00011000,B00011000,B00011000,B00011000,B11111000,B11111000},\
  {B11000000,B11000000,B11000000,B11000000,B11000000,B11000000,B11111111,B11111111},\
  {B11111111,B11111111,B11111111,B11011011,B11011011,B11011011,B11011011,B11011011},\
  {B11000011,B11100011,B11110011,B11111011,B11011111,B11001111,B11000111,B11000011},\
  {B11111111,B11111111,B11000011,B11000011,B11000011,B11000011,B11111111,B11111111},\
  {B11111110,B11111111,B11000011,B11000011,B11111111,B11111110,B11000000,B11000000},\
  {B11111110,B11111111,B11000011,B11000011,B11111110,B11111110,B11000111,B11000011},\
  {B11111111,B11111111,B11000000,B11111111,B11111111,B00000011,B11111111,B11111111},\
  {B11111111,B11111111,B00011000,B00011000,B00011000,B00011000,B00011000,B00011000},\
  {B11000011,B11000011,B11000011,B11000011,B11000011,B11000011,B11111111,B11111111},\
  {B11000011,B11000011,B11011011,B11011011,B11011011,B11011011,B11111111,B11111111},\
  {B10000001,B11000011,B01111110,B00111100,B00011000,B00011000,B00011000,B00011000}};

  for(int row=0;row<8;row++){lc.setRow(disp,row,letter[let][row]);}
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
    //Do each frame at the same time on each display
    
    for(int disp=digitFromRight;disp>=0;){
      //Work from the furthest left disp
      
      for(int row=0;row<8;row++){
        //Draw
        lc.setRow(disp,row,anim[frame][row]);
      }
      
      disp--; //Go right
    }
    
    delay(15); //15*18 = 270ms for this section
  }
}

void showTime(){
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

  //Sets current time in their separate digits
  int m2 = Clock.getMinute() % 10; //Only remainder
  int m1 = Clock.getMinute() / 10; //No remainder
  bool h12; //These bools are needed by getHour for some reason
  bool PM;
  int h2 = Clock.getHour(h12, PM) % 10;
  int h1 = Clock.getHour(h12, PM) / 10;
  
  //Example time 12:56
  
  printNum(0,m2); // 6
  printNum(1,m1); // 5
  printNum(2,h2); // 2
  printNum(3,h1); // 1
 
}

void showDate_Week(){
  //Similar to animate time but only shows the day of the week as follows
  // [T][U][0][9] = Tuesday the 9th

  int dow = Clock.getDoW(); //Turns the byte into easier int
  
  switch(dow){
    case 1:
      //Monday
      printLetter(3,8); //Prints 'M' on disp 3 (farthest left)
      printLetter(2,10); //'O' on disp 2 (second farthest left)
      break;
      
    case 2:
      //Tuesday
      printLetter(3,14); //T
      printLetter(2,15); //U
      break;
            
    case 3:
      //Wednesday
      printLetter(3,16); //W
      printLetter(2,3); //E
      break;
      
    case 4:
      //Thursday
      printLetter(3,14); //T
      printLetter(2,5); //H
      break;
      
    case 5:
      //Friday
      printLetter(3,4); //F
      printLetter(2,12); //R
      break;
      
    case 6:
      //Saturday
      printLetter(3,13); //S
      printLetter(2,0); //A
      break;
      
    case 7:
      //Sunday
      printLetter(3,13); //S
      printLetter(2,15); //U
      break;

    default:
      printLetter(3,17);
      printLetter(2,17);
  }

  int date = Clock.getDate();
  
  printNum(1,date/10); //First digit of the date
  printNum(0,date%10); //Second digit


  Serial.print(Clock.getDoW());
}

void showDate_Year(){
  // Shows month and year
  // [M][A][1][8] = May 2018

  bool cent; //Required for get month
  int month = Clock.getMonth(cent);

  switch(month){
    case 1:
      //Jan
      printLetter(3,6); //J
      printLetter(2,0); //A
      break;
      
    case 2:
      //Feb
      printLetter(3,4); //F
      printLetter(2,3); //E
      break;
      
    case 3:
      //Mar
      printLetter(3,8); //M
      printLetter(2,12); //R
      break;
      
    case 4:
      //Apr
      printLetter(3,0); //A
      printLetter(2,11); //P
      break;
      
    case 5:
      //May
      printLetter(3,8); //M
      printLetter(2,17); //Y
      break;
      
    case 6:
      //Jun
      printLetter(3,6); //J
      printLetter(2,9); //N
      break;
      
    case 7:
      //Jul
      printLetter(3,6); //J
      printLetter(2,7); //L
      break;
      
    case 8:
      //Aug
      printLetter(3,0); //A
      printLetter(2,15); //U
      break;
      
    case 9:
      //Sep
      printLetter(3,13); //S
      printLetter(2,3); //E
      break;
      
    case 10:
      //Oct
      printLetter(3,9); //O
      printLetter(2,1); //C
      break;
      
    case 11:
      //Nov
      printLetter(3,9); //N
      printLetter(2,10); //O
      break;
      
    case 12:
      //Dec
      printLetter(3,2); //D
      printLetter(2,3); //E
      break;

    default:
      printLetter(3,17);
      printLetter(2,17);
    
  }

  int year = Clock.getYear();

  printNum(1,year/10);
  printNum(0,year%10);
  
}

void loop() { 
  //This applies the current time to the displays
  showTime();

  delay(10000); //10s
  fizzle(3);

  showDate_Week();

  delay(10000); //10s
  fizzle(3);

  showDate_Year();

  delay(10000); //10s
  fizzle(3);

  //the delays make the whole loop take 30s
  //e.g. it only checks every thirty seconds for the time


  
}
