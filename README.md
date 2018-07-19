# Matrix Animator
A Visual Basic program used to generate animation code for the 8x8 Arduino MAX72XX matrix display based on user-drawn patterns and animations. Included in the appropriate directory are also example Arduino code files.

The VB program generates either a single line of bytes for use with your own programs/testing  or the full animation 2 dimensional array to be used with the arduino code examples provided. See the appropriate paste section in the Custom8x8 arduino .ino file or just replace the transition animations in the clock code.

NOTE: The LedControl.zip inside the Arduino Code Examples directory is the library required for running my examples, make sure you import it. 

# For the VB program download
 See Release.7z or go to MatrixAnimator/bin/Release and run MatrixAnimator.exe, if you would rather compile for yourself from source code, simply open MatrixAnimator.slOf

# For the Arduino code
 See appropriate directory, the Clock requires 4 displays and an RTC module, the Custom8x8 requires 1 display.

Only tested on Arduino Nano ATmega328P so if you have any issues either fork this or Google around.