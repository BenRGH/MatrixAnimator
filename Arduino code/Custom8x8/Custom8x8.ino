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

void animate(){
//Animation pasting zone
//Each of these rows describes a frame and each byte describes a row of the frame
//---------------------------------------------------------------------------------------

int frames = 1;
byte anim[frames][16]=\
{{B11111111,B10000001,B10111101,B10100101,B10100101,B10111101,B10000001,B11111111,B11111111,B10000001,B10111101,B10100101,B10100101,B10111101,B10000001,B11111111}};

//---------------------------------------------------------------------------------------
//End of paste zone


  /* Cycles through frames and during each frame cycles through and sets rows on the display.
   * disp is temp and is the display being animated 
   */
  int disp=0;

  for(int frame=0;frame<frames;frame++){
    for(int row=0;row<(16);row++){
      lc.setRow(disp,row,anim[frame][row]);
    }
    delay(delayFrame);
  }
  
}

void loop() { 
  animate();
}
