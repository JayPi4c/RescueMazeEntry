

// Angefangen am 8.1.18

/*
   Edit am 21.1.18


*/

#include "Vars.h"
#include "engine.h"

#include <SharpIR.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(LCDAddress, LCDCols, LCDRows);

volatile int encoderLeft = 0;
volatile int encoderRight = 0;

SharpIR sharpFR(IRFrontRight, 1080);
SharpIR sharpFL(IRFrontLeft, 20150);
SharpIR sharpLF(IRLeft, 1080);




boolean onBlackTile = false;


int distanceFrontLeft = 0;
int distanceFrontRight = 0;
int distanceLeft = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Hello World!");

  Serial.begin(9600);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(TACHO0), countencoderLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(TACHO2), countencoderRight, CHANGE);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  newTile();
}

void loop() {
  readSensors(); 
  printValues();

  if(WallLeft()){
    if(WallFront()){
      turn(RIGHT);
      }
    }else{
      turn(LEFT);
      }

      moveToNextTile();
  
}

boolean WallFront(){
  return distanceFrontRight < 20;
  }

boolean WallLeft(){
  return distanceLeft < 25;
  }

void printValues(){
  lcd.clear();
  lcd.print("FL:");
  lcd.setCursor(4, 0);
  lcd.print(distanceFrontLeft);
  lcd.setCursor(10, 0);
  lcd.print("FR:");
  lcd.setCursor(14, 0);
  lcd.print(distanceFrontRight);
  lcd.setCursor(0, 1);
  lcd.print("LF:");
  lcd.setCursor(4, 1);
  lcd.print(distanceLeft);
  }





void readSensors(){
  distanceFrontLeft = sharpFL.distance();
  distanceFrontRight = sharpFR.distance();
  distanceLeft = sharpLF.distance();
  }



void countencoderLeft() {
  encoderLeft++;
}

void countencoderRight() {
  encoderRight++;
}


void newTile() {
  encoderRight = 0;
  encoderLeft = 0;
}



void resetEncoder() {
  encoderLeft = 0;
  encoderRight = 0;
}


void turn(int dir) {
  lcd.clear();
  String s = "turn ";
  if (dir == RIGHT) {
    s += "right";
  } else {
    s += "left";
  }
  lcd.print(s);

  resetEncoder();
  if (dir == RIGHT) {
    while (encoderLeft < leftTurnGoal && encoderRight < rightTurnGoal) {

      if (encoderLeft < leftTurnGoal) {
        engineLeftForward();
        digitalWrite(enb, MIDDLESPEED);
      } else {
        engineLeftStop();
      }

      if (encoderRight < rightTurnGoal) {
        engineRightBackward();
        digitalWrite(ena, MIDDLESPEED);
      } else {
        engineRightStop();
      }
    }
  } else if (dir == LEFT) {
    while (encoderLeft < leftTurnGoal && encoderRight < rightTurnGoal) {

      if (encoderLeft < leftTurnGoal) {
        engineLeftBackward();
        digitalWrite(enb, MIDDLESPEED);
      } else {
        engineLeftStop();
      }

      if (encoderRight < rightTurnGoal) {
        engineRightForward();
        digitalWrite(ena, MIDDLESPEED);
      } else {
        engineRightStop();
      }
    }

    lcd.clear();
    lcd.print("DONE!");
    delay(1000);
  }
} 


void moveToNextTile() {
  lcd.clear();
  lcd.print("reaching next Tile");
  int valueLeft = 700;
  int valueRight = 700;
  while (encoderLeft < valueLeft && encoderRight < valueRight) {
    if (encoderLeft < valueLeft) {
      engineLeftForward();
      digitalWrite(enb, 255);
    } else {
      engineLeftStop();
    }
    if (encoderRight < valueRight) {
      engineRightForward();
      digitalWrite(ena, 255);
    }
    else {
     engineRightStop();
    }
    if(random(10) > 8){
      onBlackTile = true;
      }

    /*if (onBlackTile) {
      lcd.clear();
      lcd.print("Yep: Black");
      delay(1000);
      break;
    }*/
  }
  /*if (onBlackTile) {
    valueLeft = encoderLeft * 2;
    valueRight = encoderRight * 2;

    while (encoderLeft < valueLeft && encoderRight < valueRight) {
      lcd.clear();
      lcd.print("well, maybe black!");
      delay(1000);
      if (encoderLeft < valueLeft) {
        engineLeftBackward();
        digitalWrite(enb, 255);
      } else {
        engineLeftStop();
      }
      if (encoderRight < valueRight) {
        engineRightBackward();
        digitalWrite(ena, 255);
      }
      else {
        engineRightStop();
      }
    }
    onBlackTile = false;
  }*/
  //und jetzt müsste einmal nach rechts oder links gedreht werden

  lcd.clear();
  lcd.print("reached next Tile!");
  engineBackward();
  digitalWrite(ena, 0);
  digitalWrite(enb, 0);
  
  delay(1000);
  lcd.print("done");
  newTile();
}

