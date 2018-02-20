#include "Engine.h"

void engineForward() {
  engineLeftForward();
  engineRightForward();
}

void engineBackward() {
  engineLeftBackward();
  engineRightBackward();
}

void engineRightForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void engineLeftForward() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void engineRightBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void engineLeftBackward() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void engineLeftStop() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(enb, OFF);
}

void engineRightStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(ena, OFF);
}


void engineStop() {
  engineLeftStop();
  engineRightStop();
}
