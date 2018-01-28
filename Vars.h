#include "Arduino.h"

#define ena 9 //Rechter Motor
#define enb 8
#define IN1 42
#define IN2 43
#define IN3 45
#define IN4 44

#define TACHO0 18
#define TACHO1 19
#define TACHO2 2
#define TACHO3 3

//Address of the LCD
#define LCDAddress 0x20
#define LCDCols 20
#define LCDRows 4

#define LEFT 0
#define RIGHT 1

#define leftTurnGoal 425
#define rightTurnGoal 425

#define rightMoveGoal 800
#define leftMoveGoal 800

#define HIGHSPEED 255
#define MIDDLESPEED 170
#define LOWSPEED 80
#define OFF 0


//define Sensors
#define IRFrontLeft A5
#define IRFrontRight A1
#define IRRight
#define IRLeft A0


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
