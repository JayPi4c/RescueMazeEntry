

// Angefangen am 8.1.18

//includes
#include "Vars.h"
#include "engine.h"


#include "SharpIR.h"
#include "LiquidCrystal_I2C.h"



// Initialisierung
LiquidCrystal_I2C lcd(LCDAddress, LCDCols, LCDRows);


volatile int encoderLeft = 0;
volatile int encoderRight = 0;

SharpIR sharpLeftBack(IRLeftBack, 430);
SharpIR sharpRightBack(IRRightBack, 430);
SharpIR sharpFrontRight(IRFrontRight, 430);

int valueLB = 0;
int valueRB = 0;
int valueFR = 0;


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



  // setze die Drehrichtung der Motoren
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}






void loop() {

  lcd.clear();
  lcd.print("read sensors");
  readSensors();
  printValues();


  // Da nur zwei Sensoren funktionieren: LF und FR müssen wir das Linke Hand Prinzip verwenden!
  if (valueLB > 10) {
    // Wenn der Sensorwert des linken Sensors größer als 10 ist, dann ist links kein Hindernis und wir können uns nach links drehen
    // und dann in das leere Feld fahren
    turn(LEFT);
    moveToNextTile();
  } else if (valueFR > 25) {
    // wenn der Sensorwert des Sensors nach vorne größer ist als 25, dann ist vorne kein Hindernis und wir können geradeaus weiterfahren
    moveToNextTile();
  } else {
    // links und vorne ist ein Hindernis, als müssen wir uns nach rechts drehen und gucken, ob wir geradeaus fahren dürfen
    // das heißt: nach rechts drehen und wieder neu in die Loop-Schleife gehen!
    turn(RIGHT);
  }
}

void readSensors() {
  valueLB = sharpLeftBack.distance();
  valueFR = sharpFrontRight.distance();
  valueRB = sharpRightBack.distance();
}


void printValues() {
  lcd.clear();
  lcd.print("LB:");
  lcd.setCursor(4, 0);
  lcd.print(valueLB);
  lcd.setCursor(0, 1);
  lcd.print("FR: ");
  lcd.setCursor(4, 1);
  lcd.print(valueFR);
  lcd.setCursor(0, 2);
  lcd.print("RB: ");
  lcd.setCursor(4, 2);
  lcd.print(valueRB);
  delay(1000);
}






void countencoderLeft() {
  encoderLeft++;
}

void countencoderRight() {
  encoderRight++;
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
    while (encoderLeft < leftTurnGoal || encoderRight < rightTurnGoal) {

      if (encoderLeft < leftTurnGoal) {
        engineLeftForward();
        digitalWrite(enb, HIGHSPEED);
      } else {
        engineLeftStop();
      }

      if (encoderRight < rightTurnGoal) {
        engineRightBackward();
        digitalWrite(ena, HIGHSPEED);
      } else {
        engineRightStop();
      }
    }
  } else if (dir == LEFT) {
    while (encoderLeft < leftTurnGoal || encoderRight < rightTurnGoal) {
      Serial.print("Enoder Wert rechts: ");
      Serial.println(encoderRight);
      Serial.print("Enoder Wert links: ");
      Serial.println(encoderLeft);
      if (encoderLeft < leftTurnGoal) {
        engineLeftBackward();
        digitalWrite(enb, MIDDLESPEED);
      } else {
        engineLeftStop();
        Serial.println("Engine Left Stop");
      }

      if (encoderRight < rightTurnGoal) {
        engineRightForward();
        digitalWrite(ena, MIDDLESPEED);
      } else {
        engineRightStop();
        Serial.println("Engine Right Stop");
      }
    }

    lcd.clear();
    lcd.print("DONE!");
    delay(1000);
  }
}

// laesst den Roboter ca. 40 cm nach voren fahren
void moveToNextTile() {
  // gebe aktuelle Informationen auf dem Display aus
  lcd.clear();
  lcd.print("reaching next Tile");
  // leere die Werte der Encoder, damit nicht mit Werten von dem Drehen gearbeitet wird!
  resetEncoder();

  //solange beide Motoren noch nicht die Encoderziele erreicht haben. (Die Encoder müssen sich um x° gedreht haben, damit exakt
  // 40 cm vorwärts gefahren wurde
  while (encoderLeft < leftMoveGoal && encoderRight < rightMoveGoal) {
    // wenn linkes Ziel erreicht wurde, aufhören zu drehen
    if (encoderLeft < leftMoveGoal) {
      engineLeftForward();
      digitalWrite(enb, 255);
    } else {
      engineLeftStop();
    }
    // wenn rechtes Ziel erreicht wurde, aufhören zu drehen
    if (encoderRight < rightMoveGoal) {
      engineRightForward();
      digitalWrite(ena, 255);
    }
    else {
      engineRightStop();
    }
  }

  // anzeigen, dass 40 cm gefahren wurden
  lcd.clear();
  lcd.print("reached next Tile!");
  engineBackward();
  digitalWrite(ena, 0);
  digitalWrite(enb, 0);
  // für eine Sekunde stoppen und erst weitermachen
  delay(1000);
  lcd.print("done");
}
