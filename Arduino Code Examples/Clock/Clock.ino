#include "LedControl.h"
#include <Wire.h>
#include "DS3231.h"

DS3231 Clock;

//Vars
int displays = 4; //Number of displays (check this is right)
int intensity = 5; //Brightness of displays (don't recommend changing!)
//Pins
int DIN = 12;
int CLK = 10;
int CS = 11;

//Init the display obj
LedControl lc = LedControl(DIN,CLK,CS,displays); 


void setup() {
  //Start RTC stuff
  Wire.begin(); 

  //This cycles through the displays and preps them
  for(int i = 0; i < displays; i++){
    //Display is in power-saving mode, this does a wakeup call
    lc.shutdown(i,false);
    
    // Set the brightness
    lc.setIntensity(i,intensity);
    
    // and clear the display just in case
    lc.clearDisplay(i);
  }

  //Use this for debugging RTC or anything really: Serial.begin(9600); 
}


void printNum(int disp, int num){
  //Simply prints the number row by row to the display specified
  
  /* 
   * The wall of gibberish that follows is the numbers 0-9 drawn in my VB.net 
   * program Matrix Animator (in the same github repo in case you missed it)
   * stuffed into a 2D array.
   * 
   * Each line is a number and each of the 'Bxxxxxxxx' elements are Bytes for  
   * each row with a 1 corresponding to an on LED and 0's corresponding to off. 
   * If you like you can copy them into notepad and rearrange them to see how it 
   * looks (requires squinting).
   */
   
  byte number[10][8]=\
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

  //This sets the LED's according to the bytes above and the given arguments
  for(int row = 0; row < 8; row++){
    lc.setRow(disp, row, number[num][row]);
  }
  
}

void printLetter(int disp, int let){
  //Prints the given letter to the given display, same deal as above

  //18 letter alphabet (only characters needed by me):
  //ACDEFHJLMNOPRSTUWY
  byte letter[18][8]=\
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
  /* 
   * Plays Fizzle animation on ALL the displays up to the given argument.
   * 
   * This works differently to the functions above, this array uses each of the
   * level 1 elements of the array as a frame in an animation (made using my 
   * Matrix Animator program) and it draws it to ALL the displays up to the number
   * given. 
   * 
   * The framerate can be changed at the bottom (how fast the animation plays)
   * and yes I know this is O(n^3) but efficiency is unnecessary here.
   */

  int frames = 18; //Just for clarity
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
    
    delay(15); //15*18 = 270ms for the animation
  }
}

void wipe(int digitFromRight){
  //Plays wipe animation, see fizzle() for more details

  int frames = 18; //Just for clarity
  byte anim[18][8]=\
  {{B00010000,B00000000,B00000000,B00000001,B10000000,B00000000,B00000000,B00001000},\
  {B00010000,B00010000,B00000000,B00000011,B11000000,B00000000,B00001000,B00001000},\
  {B00010000,B00010000,B00010000,B00000111,B11100000,B00001000,B00001000,B00001000},\
  {B00010000,B00010000,B00010000,B00011111,B11111000,B00001000,B00001000,B00001000},\
  {B00010000,B00010000,B00011000,B00111111,B11111100,B00011000,B00001000,B00001000},\
  {B00010000,B00011000,B00011000,B01111111,B11111110,B00011000,B00011000,B00001000},\
  {B00011000,B00011000,B00011000,B11111111,B11111111,B00011000,B00011000,B00011000},\
  {B00100100,B00100100,B11111111,B00100100,B00100100,B11111111,B00100100,B00100100},\
  {B01000010,B11111111,B01000010,B01000010,B01000010,B01000010,B11111111,B01000010},\
  {B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111},\
  {B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111},\
  {B11111111,B11111111,B11000011,B11000011,B11000011,B11000011,B11111111,B11111111},\
  {B11111111,B11111111,B11111111,B11100111,B11100111,B11111111,B11111111,B11111111},\
  {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},\
  {B00000000,B01111110,B01111110,B01111110,B01111110,B01111110,B01111110,B00000000},\
  {B00000000,B00000000,B00111100,B00111100,B00111100,B00111100,B00000000,B00000000},\
  {B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000},\
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
    
    delay(15); //15*18 = 270ms for the animation
  }
}

void spiral(int digitFromRight){
  //Plays spiral animation, see fizzle() for more details

  int frames = 18; //Just for clarity
  byte anim[18][8]=\
  {{B10000001,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B10000001},\
  {B10000011,B10000000,B00000000,B00000000,B00000000,B00000000,B00000001,B11000001},\
  {B10000111,B10000000,B10000000,B00000000,B00000000,B00000001,B00000001,B11100001},\
  {B10001111,B10000000,B10000000,B10000000,B00000001,B00000001,B00000001,B11110001},\
  {B10011111,B10000000,B10000000,B10000001,B10000001,B00000001,B00000001,B11111001},\
  {B10111111,B10000000,B10000001,B10000001,B10000001,B10000001,B00000001,B11111101},\
  {B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111},\
  {B11111111,B11000011,B10000001,B10000001,B10000001,B10000001,B11000011,B11111111},\
  {B11111111,B11000011,B10100101,B10000001,B10000001,B10100101,B11000011,B11111111},\
  {B11111111,B11000011,B10100101,B10011001,B10011001,B10100101,B11000011,B11111111},\
  {B11111111,B10000101,B11001001,B10111001,B10011101,B10010011,B10100001,B11111111},\
  {B11111111,B10001001,B10001001,B11111001,B10011111,B10010001,B10010001,B11111111},\
  {B11111111,B10011001,B10001001,B11111011,B11011111,B10010001,B10011001,B11111111},\
  {B11111111,B10011001,B10011001,B11111111,B11111111,B10011001,B10011001,B11111111},\
  {B11111111,B10111001,B10011011,B11111111,B11111111,B11011001,B10011101,B11111111},\
  {B11111111,B11111011,B10011011,B11111111,B11111111,B11011001,B11011111,B11111111},\
  {B11111111,B11111111,B11011011,B11111111,B11111111,B11011011,B11111111,B11111111},\
  {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111}};
  

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
    
    delay(15); //15*18 = 270ms for the animation
  }
}

void showTime(){
  /* 
   * This is used to put the time taken from the RTC onto the displays. It's a 
   * little weird with the way my displays are laid out but it works well.
   * 
   * The time on the displays are ordered as follows in this 100% accurate diagram:
   * 
   * [3][2][1][0]--cables
   *  1  2 :5  6 
   *  
   * Print each digit onto its own individual display (shown in brackets), excluding 
   * the colon because that is unnecessary.
   *  
   * We work from right to left so the first display on the right is the second 
   * digit of minutes (m2), the second display from the right is the first digit 
   * of minutes (m1), same goes for hours. 
   * If this made things more confusing, look back at the diagram...
  */

  //Separates the digits of time into vars from right to left
  int m2 = Clock.getMinute() % 10; //Only remainder
  int m1 = Clock.getMinute() / 10; //No remainder
  bool h12; //These bools are needed by getHour
  bool PM;
  int h2 = Clock.getHour(h12, PM) % 10;
  int h1 = Clock.getHour(h12, PM) / 10;

  //With printNum(display, number) we set the vars of time onto the actual 
  //displays, the example time 12:56 alongside them shows how it works.
  printNum(0,m2); // 6
  printNum(1,m1); // 5
  printNum(2,h2); // 2
  printNum(3,h1); // 1
 
}

void showDate_Week(){
  /*
   * This is the same as the above showTime() despite appearances,
   * with only a small difference: it shows the day of the week on the left two 
   * displays and the day of the month in the right two, as follows:
   * 
   * [T][U][0][9] = Tuesday the 9th
   */

  int dow = Clock.getDoW(); //getDoW() returns a byte so this turns it into an int

  //An easier way to do this would be preferable but I couldn't find one
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
      //Something bad has happened if this comes up
      printLetter(3,17); //Y
      printLetter(2,17); //Y
  }

  int date = Clock.getDate(); //Gets day of month
  
  printNum(1,date/10); //First digit of the date
  printNum(0,date%10); //Second digit


  //Use for debugging RTC: Serial.print(Clock.getDoW());
}

void showDate_Year(){
  // Same as the last two but shows month and year:
  // [M][A][1][8] = May 2018

  bool cent; //Required for get month
  int month = Clock.getMonth(cent);

  //Same inconvenience as above
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
      //Error
      printLetter(3,17); //Y
      printLetter(2,17); //Y
    
  }

  int year = Clock.getYear();

  printNum(1,year/10); //First digit of year
  printNum(0,year%10); //Second
  
}

void loop() { 
  //This applies the current time to the displays:
  // [1][2][5][6]
  showTime();

  delay(5000); //5s
  fizzle(3);

  //Applies current day of the week and day of month:
  // [T][H][1][9]
  showDate_Week();

  delay(5000); //5s
  wipe(3);

  //Applies month and year:
  // [J][L][1][8]
  showDate_Year();

  delay(5000); //5s
  spiral(3);

  //the delays make the whole loop take ~15.81s
  //e.g. it only checks every ~15.81 seconds for the time
  
}
