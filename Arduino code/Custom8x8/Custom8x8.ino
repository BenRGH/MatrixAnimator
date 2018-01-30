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
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void animate(){
//Animation pasting zone
//Each of these rows describes a frame and each byte describes a row of the frame
//---------------------------------------------------------------------------------------






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
    delay(delayFrame);
  }
  delay(delayLong);

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
