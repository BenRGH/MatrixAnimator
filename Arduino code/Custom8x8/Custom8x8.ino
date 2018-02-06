#include "LedControl.h"

//Vars
unsigned long delayFrame=100; //Frame rate
int displays = 1; //Number of displays
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

void animate(){
//Animation pasting zone
//Each of these rows describes a frame and each byte describes a row of the frame
//---------------------------------------------------------------------------------------

int frames = 106;
byte anim[frames][8]=\
{{B11111111,B10000001,B10111101,B10100101,B10100101,B10111101,B10000001,B11111111},\
{B00000000,B01111110,B01000010,B01011010,B01011010,B01000010,B01111110,B00000000},\
{B11111111,B10000001,B10111101,B10100101,B10100101,B10111101,B10000001,B11111111},\
{B00000000,B01111110,B01000010,B01011010,B01011010,B01000010,B01111110,B00000000},\
{B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000},\
{B10000001,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B10000001},\
{B10000001,B01000010,B00000000,B00011000,B00011000,B00000000,B01000010,B10000001},\
{B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001},\
{B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000},\
{B00000000,B00000000,B00100100,B00011000,B00011000,B00100100,B00000000,B00000000},\
{B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000},\
{B10000001,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B10000001},\
{B10000001,B01000010,B00000000,B00011000,B00011000,B00000000,B01000010,B10000001},\
{B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001},\
{B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000},\
{B00000000,B00000000,B00100100,B00011000,B00011000,B00100100,B00000000,B00000000},\
{B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000},\
{B00000000,B00000000,B00000000,B00111100,B00111100,B00000000,B00000000,B00000000},\
{B00000000,B00000000,B00000000,B01111110,B01111110,B00000000,B00000000,B00000000},\
{B00000000,B00000000,B00000000,B11111111,B11111111,B00000000,B00000000,B00000000},\
{B00000000,B00000000,B11111111,B11111111,B11111111,B11111111,B00000000,B00000000},\
{B00000000,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B00000000},\
{B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},\
{B01111110,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B01111110},\
{B01111110,B10111101,B11111111,B11111111,B11111111,B11111111,B10111101,B01111110},\
{B01111110,B10111101,B11011011,B11111111,B11111111,B11011011,B10111101,B01111110},\
{B01111110,B10111101,B11011011,B11100111,B11100111,B11011011,B10111101,B01111110},\
{B01111100,B00111101,B11011011,B11100111,B11100111,B11011011,B10111100,B00111110},\
{B11111001,B00111001,B00010011,B11000111,B11100011,B11001000,B10011100,B10011111},\
{B11110011,B11110011,B00110111,B00000111,B11100000,B11101100,B11001111,B11001111},\
{B11100111,B11100111,B11101111,B00100000,B00000100,B11110111,B11100111,B11100111},\
{B11001111,B11001111,B11011000,B11100100,B00100111,B00011011,B11110011,B11110011},\
{B10001111,B10001000,B10011000,B11100100,B00100111,B00011001,B00010001,B11110001},\
{B00001000,B00001000,B00011000,B11100100,B00100111,B00011000,B00010000,B00010000},\
{B00000000,B00001000,B00011000,B01100100,B00100110,B00011000,B00010000,B00000000},\
{B00000000,B00000000,B00011000,B00100100,B00100100,B00011000,B00000000,B00000000},\
{B00000000,B00000000,B00110100,B00000100,B00100000,B00101100,B00000000,B00000000},\
{B00000000,B00000100,B01110100,B00000100,B00100000,B00101110,B00100000,B00000000},\
{B00000100,B00000100,B11110100,B00000100,B00100000,B00101111,B00100000,B00100000},\
{B00000100,B00000100,B11100100,B00000000,B00000000,B00100111,B00100000,B00100000},\
{B00000100,B00000100,B11000000,B00000000,B00000000,B00000011,B00100000,B00100000},\
{B00000100,B00000000,B10000000,B00000000,B00000000,B00000001,B00000000,B00100000},\
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},\
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},\
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},\
{B00000000,B00000000,B00010000,B00010000,B00001000,B00000100,B00000010,B00000000},\
{B00000000,B00000000,B00010000,B00010000,B00001100,B00000010,B00000000,B00000000},\
{B00000000,B00000000,B00010000,B00010000,B00001110,B00000000,B00000000,B00000000},\
{B00000000,B00000000,B00010000,B00010110,B00001000,B00000000,B00000000,B00000000},\
{B00000000,B00000000,B00010010,B00010100,B00001000,B00000000,B00000000,B00000000},\
{B00000000,B00000100,B00010100,B00010100,B00001000,B00000000,B00000000,B01000000},\
{B00000000,B00000100,B00010100,B00010100,B00001000,B00000000,B00000000,B01001000},\
{B00000000,B00000100,B00010100,B00010100,B00001000,B00000000,B00000000,B01001010},\
{B00000000,B00000100,B00010100,B00010100,B00001000,B00000010,B00000000,B01001010},\
{B00000000,B00100100,B00010100,B00010100,B01001000,B00000010,B00000000,B01001010},\
{B00000000,B00100110,B00010100,B00010110,B01001000,B00000010,B00000000,B01001010},\
{B00000000,B00100110,B00010100,B00010110,B01001000,B00001010,B01000000,B01001010},\
{B00000000,B10100110,B10010100,B00010110,B01001000,B00001010,B01000000,B01001010},\
{B00000000,B10100110,B10010100,B00010110,B01001000,B00001010,B01000011,B01001010},\
{B00000000,B10100110,B10010100,B00010110,B01001010,B01001011,B11000010,B01001010},\
{B00000000,B10100110,B10010100,B00010110,B01001011,B11001010,B01000010,B01001010},\
{B11000000,B10100110,B10010100,B00010111,B11001010,B01001010,B01000010,B01001010},\
{B11000100,B10100100,B10010100,B00010111,B11001010,B01001010,B01000010,B01001010},\
{B11000000,B10101100,B10010100,B00010111,B11001010,B01001010,B01000010,B01001010},\
{B11000000,B10101100,B10010100,B00010111,B11001010,B01101010,B01000011,B01001010},\
{B11000010,B10101101,B10010100,B00010111,B11001010,B01101010,B01000011,B01101010},\
{B11000010,B10101101,B10010100,B01010111,B11101010,B01101010,B11000111,B01101010},\
{B11010010,B10101101,B10010100,B01010111,B11101111,B01101010,B11000111,B01101010},\
{B11010110,B10101101,B11111100,B01010111,B11101111,B01111010,B11011111,B01101010},\
{B11010111,B10111101,B11111110,B01010111,B11101111,B01111010,B11011111,B01101010},\
{B11010111,B10111101,B11111110,B11010111,B11111111,B01111010,B11011111,B01101110},\
{B11010111,B10111101,B11111110,B11010111,B11111111,B01111011,B11111111,B01111110},\
{B11110111,B10111111,B11111110,B11110111,B11111111,B01111011,B11111111,B01111110},\
{B11110111,B10111111,B11111110,B11110111,B11111111,B01111111,B11111111,B11111111},\
{B11111111,B11111111,B11111111,B11110111,B11111111,B01111111,B11111111,B11111111},\
{B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},\
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},\
{B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},\
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},\
{B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},\
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},\
{B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111},\
{B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111},\
{B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111},\
{B01111110,B11000011,B11000011,B11000011,B10000001,B10000001,B10000001,B11111111},\
{B01111110,B01100110,B11100111,B11000011,B10000001,B10000001,B10000001,B11111111},\
{B00111100,B01100110,B01100110,B11000011,B11000011,B10000001,B10000001,B11111111},\
{B00111100,B00100100,B01100110,B01000010,B11000011,B10000001,B10000001,B11111111},\
{B00011000,B00111100,B00100100,B01100110,B01000010,B11000011,B10000001,B11111111},\
{B00011000,B00111100,B00100100,B01100110,B01000010,B11000011,B10000001,B11111111},\
{B00011000,B00111100,B00100100,B01100110,B01000010,B11000011,B10000001,B11111111},\
{B00011000,B00111100,B00100100,B01100110,B01000010,B01000010,B11000011,B11111111},\
{B00011000,B00111100,B00100100,B01100110,B01000010,B01000010,B01100110,B01111110},\
{B00011000,B00111100,B00100100,B01100110,B01000010,B01000010,B01100110,B00111100},\
{B00011000,B00111100,B00100100,B01100110,B01000010,B01100110,B00100100,B00111100},\
{B00011000,B00111100,B00100100,B01100110,B01000010,B01100110,B00111100,B00011000},\
{B00000000,B00011000,B00111100,B01100110,B01000010,B01100110,B00111100,B00011000},\
{B00000000,B00000000,B00111100,B01100110,B01000010,B01100110,B00111100,B00000000},\
{B00000000,B00000000,B00011000,B00100100,B01000010,B00100100,B00011000,B00000000},\
{B00000000,B00000000,B00011000,B00100100,B01000010,B00111100,B00000000,B00000000},\
{B00000000,B00000000,B00000000,B00111100,B01000010,B00111100,B00000000,B00000000},\
{B00000000,B00000000,B00000000,B00011000,B00100100,B00011000,B00000000,B00000000},\
{B00000000,B00000000,B00000000,B00011000,B00011000,B00011000,B00000000,B00000000},\
{B00000000,B00000000,B00000000,B00000000,B00011000,B00000000,B00000000,B00000000},\
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},\
{B11111111,B10000001,B10111101,B10100101,B10100101,B10111101,B10000001,B11111111}};

//---------------------------------------------------------------------------------------
//End of paste zone


  /* Cycles through frames and during each frame cycles through and sets rows on the display.
   * disp is temp and is the display being animated 
   */
  int disp=0;

  for(int frame=0;frame<frames;frame++){
    for(int row=0;row<(8*(disp+1));row++){
      lc.setRow(disp,row,anim[frame][row]);
    }
    delay(delayFrame);
  }
  
}

void loop() { 
  animate();
}
