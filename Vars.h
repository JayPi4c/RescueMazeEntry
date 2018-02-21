#include "Arduino.h"

#define ena 9 //Rechter Motor
#define enb 8
#define IN1 45
#define IN2 44
#define IN3 43
#define IN4 42


//INTERRUPTS
//Müssen InterruptPins sein (einer von
// 2, 3, 18, 19, 20, 21 auf einem Arduino Mega

//Rechts
#define TACHO0 3 
#define TACHO1 2
// Links
#define TACHO2 18 
#define TACHO3 19


//Address of the LCD
#define LCDAddress 0x20
#define LCDCols 20
#define LCDRows 4

#define LEFT 0
#define RIGHT 1

#define leftTurnGoal 440
#define rightTurnGoal 440

#define rightMoveGoal 825
#define leftMoveGoal 825

#define HIGHSPEED 255
#define MIDDLESPEED 170
#define LOWSPEED 80
#define OFF 0


//define Sensors

///////////////////////////////////////////////////
/////////////////////// ^ /////////////////////////
/////////////////////// | /////////////////////////
///////////////////////////////////////////////////
//////////            |  |
//                  A1|  |
//              ______|  |______
//                A0        A4     
//              ______    ______
//                    |  |
//                  A6|  |A5 
//                    |  |


#define IRFrontLeft A0  // 1080
#define IRLeftFront A1  // 430
#define IRFrontRight A4 // 430
#define IRRightBack A5  // 430
#define IRLeftBack A6   // 430

#define grSclL A8
#define grSclR A9


//define Sensor threshold
#define SharpThreshold 20


//directions
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


// Maze definitions
#define MAZECOLS 10
#define MAZEROWS 10
#define StartCol 5
#define StartRow 5
