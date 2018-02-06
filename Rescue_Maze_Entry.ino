

// Angefangen am 8.1.18

/*
    Edit am 21.1.18
    Edit am 28.1.18

    Edit am 06.02.18 Heute werden Sensoren ausgetestet
*/

/*
  Die Loop schleife soll immmer das dier folgende Struktur folgen:

  Auslesen der Sensorwerte
  das aktuelle Tile, auf dem wir uns befinden temporär speichern
  mache "Setupsachen" mit dem Tile, also speichere, ob es Wände gibt, ob es sich um ein Checkpoint handelt, oder ob es ein
    schwarzes Feld ist.
  überprüfe, ob rechts ein feld frei ist. Wenn ja:
      Fahre dort hinein. (Achtung Richtung)
      vollziehe das Programm wieder von vorne! (return;)
  überprüfe, ob vorne ein Feld frei ist. Wenn ja:
      Fahre dort hinein. (Achtung Richtung)
      vollziehe das Programm wieder von vorne! (return;)
  überprüfe, ob links ein Feld frei ist. Wenn ja:
      Fahre dort hinein. (Achtung Richtung)
      vollziehe das Prgramm wieder von vorne! (return!)
  rechts, vorne und links sind unerreichbar -> umdrehen und zurückfahren
      (Beachte,

*/


//includes
#include "Vars.h"
#include "engine.h"

#include "Tile.h"


#include <SharpIR.h>
#include <LiquidCrystal_I2C.h>



// Initialisierung
LiquidCrystal_I2C lcd(LCDAddress, LCDCols, LCDRows);

volatile int encoderLeft = 0;
volatile int encoderRight = 0;

SharpIR sharpFR(IRFrontRight, 1080);
SharpIR sharpFL(IRFrontLeft, 20150);
SharpIR sharpLF(IRLeft, 1080);



// Werte der Entfernungssensoren
int distanceNorthLeft = 0;
int distanceNorthRight = 0;
int distanceWestLeft = 0;
int distanceWestRight = 0;
int distanceSouthLeft = 0;
int distanceSouthRight = 0;
int distanceEastLeft = 0;
int distanceEastRight = 0;

int distanceFrontLeft = 0;
int distanceFrontRight = 0;
int distanceLeft = 0;


// Das eigentliche Labyrinth (Die Karte)
// evtl. lohnt es sich auch diese in eine eigene Klasse einzubetten.
Tile** maze;

// Die aktuelle Position
int currentCol = StartCol;
int currentRow = StartRow;
int DIRECTION = NORTH;


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

// Initialisierung der Karte
  maze = new Tile*[MAZEROWS];
  for (int i = 0; i < MAZEROWS; i++) {
    maze[i] = new Tile[MAZECOLS];
  }



// setze die Drehrichtung der Motoren
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}






void loop() {

  // Lese alle Sensorwerte aus und speichere die Werte abhängig von der Ausrichtung (dir)!
  lcd.clear();
  lcd.print("read sensors");
  readSensors(NORTH);
  delay(500);

  // speichere das aktuelle Tile ab, in dem wir uns gerade befinden!
  lcd.clear();
  lcd.print("get current Tile");
  Tile current = maze[currentCol][currentRow];
  // setze das Tile als visited!
  delay(500);
  lcd.clear();
  lcd.print("set visited");
  current.setVisited(true);
  delay(500);

  lcd.clear();
  lcd.print("set Walls");
  //setze die Werte, ob eine Wall an einer Seite ist oder nicht für das currentTile fest!
  //für den Norden
  current.setWall(NORTH, checkWallNorth());
  //für den Westen
  current.setWall(WEST, checkWallWest());
  //für den Süden
  current.setWall(SOUTH, checkWallSouth());
  //für den Osten
  current.setWall(EAST, checkWallEast());
  delay(500);

  lcd.clear();
  //überprüfe, ob das rechte Feld erreichbar ist, also ob eine Wand dazwischen ist!
  if (!checkRightWall(DIRECTION)) {
    lcd.print("Rechts ist frei");
  } else if (!checkFrontWall(DIRECTION)) {
    lcd.print("Vorne ist frei");
  } else if (!checkLeftWall(DIRECTION)) {
    lcd.print("Links ist frei");
  }else{
    lcd.print("Nirgends ist frei");
    }
  delay(1000);


}

// Lese die Werte der Sensoren aus und speichere sie abhängig von der aktuellen ausrichtung!
void readSensors(int dir) {
  switch (dir) {
    case NORTH:
      distanceNorthLeft = sharpFL.distance();
      distanceNorthRight = sharpFR.distance();
      distanceWestLeft = 0;
      distanceWestRight = sharpLF.distance();
      distanceSouthLeft = 0;
      distanceSouthRight = 0;
      distanceEastLeft = 0;
      distanceEastRight = 0;
      break;
    case SOUTH:
      distanceNorthLeft = 0;
      distanceNorthRight = 0;
      distanceWestLeft = 0;
      distanceWestRight = 0;
      distanceSouthLeft = sharpFL.distance();
      distanceSouthRight = sharpFR.distance();
      distanceEastLeft = 0;
      distanceEastRight = sharpLF.distance();
      break;
    case WEST:
      distanceNorthLeft = 0;
      distanceNorthRight = 0;
      distanceWestLeft = sharpFL.distance();
      distanceWestRight = sharpFR.distance();
      distanceSouthLeft = 0;
      distanceSouthRight = sharpLF.distance();
      distanceEastLeft = 0;
      distanceEastRight = 0;
      break;
    case EAST:
      distanceNorthLeft = 0;
      distanceNorthRight = sharpLF.distance();
      distanceWestLeft = 0;
      distanceWestRight = 0;
      distanceSouthLeft = 0;
      distanceSouthRight = 0;
      distanceEastLeft = sharpFL.distance();
      distanceEastRight = sharpFR.distance();
      break;
  }
}

boolean checkRightWall(int dir) {
  switch (dir) {
    case NORTH:
      return checkWallEast();
      break;
    case WEST:
      return checkWallNorth();
      break;
    case SOUTH:
      return checkWallWest();
      break;
    case EAST:
      return checkWallSouth();
      break;
    default:
      return false;
  }
}

boolean checkFrontWall(int dir) {
  switch (dir) {
    case NORTH:
      return checkWallNorth();
      break;
    case WEST:
      break;
      return checkWallWest();
      break;
    case SOUTH:
      return checkWallSouth();
      break;
    case EAST:
      return checkWallEast();
      break;
    default:
      return false;
      break;
  }
}

boolean checkLeftWall(int dir) {
  switch (dir) {
    case NORTH:
      return checkWallWest();
      break;
    case WEST:
      break;
      return checkWallSouth();
      break;
    case SOUTH:
      return checkWallEast();
      break;
    case EAST:
      return checkWallNorth();
      break;
    default:
      return false;
      break;
  }
}

boolean checkWallNorth() {
  return (distanceNorthLeft < SharpThreshold || distanceNorthRight < SharpThreshold);
}

boolean checkWallWest() {
  return (distanceWestLeft < SharpThreshold || distanceWestRight < SharpThreshold);
}


boolean checkWallSouth() {
  return (distanceSouthLeft < SharpThreshold || distanceSouthRight < SharpThreshold);
}

boolean checkWallEast() {
  return (distanceEastLeft < SharpThreshold || distanceEastRight < SharpThreshold);
}













boolean WallFront() {
  return distanceFrontRight < 20;
}

boolean WallLeft() {
  return distanceLeft < 25;
}

void printValues() {
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
