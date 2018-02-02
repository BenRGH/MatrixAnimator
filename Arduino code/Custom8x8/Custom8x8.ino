#include "LedControl.h"

LedControl lc=LedControl(12,10,11,1);

/* we always wait a bit between updates of the display */
unsigned long delayWord=500;
unsigned long delayLong=1000;
unsigned long delayFrame=100;
void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  // Set the brightness to a medium values 
  lc.setIntensity(0,8);
  // and clear the display
  lc.clearDisplay(0);
}

void animate(){
//Animation pasting zone
//Each of these rows describes a frame and each byte describes a row of the frame
//---------------------------------------------------------------------------------------

int frames = 8;
byte anim[frames][8]=\
{{B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001},\
{B00000010,B10000100,B01100100,B00011000,B00011000,B00100110,B00100001,B01000000},\
{B00000100,B00000100,B11001000,B00111000,B00011100,B00010011,B00100000,B00100000},\
{B00001000,B00001000,B00001000,B11111000,B00011111,B00010000,B00010000,B00010000},\
{B00010000,B00011000,B00001000,B01111011,B11011110,B00010000,B00011000,B00001000},\
{B00100000,B00010000,B00010001,B00011110,B01111000,B10001000,B00001000,B00000100},\
{B01000000,B00100001,B00100110,B00011000,B00011000,B01100100,B10000100,B00000010},\
{B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001}};




//---------------------------------------------------------------------------------------
//End of paste zone

  /* Cycles through frames and during 
   * each frame cycles through and sets rows
   * with a delay at the end followed by
   * the first frame again with a delay (optional)
   */
  for(int frame=0;frame<frames;frame++){
    for(int row=0;row<8;row++){
      lc.setRow(0,row,anim[frame][row]);
    }
    delay(50);
  }
  //delay(delayLong);

  //Final frame with following delay
  /*
  for(int row=0;row<8;row++){
    lc.setRow(0,row,anim[0][row]);
  }
  delay(delayLong);
  */
}

void loop() { 
  animate();
  
}
