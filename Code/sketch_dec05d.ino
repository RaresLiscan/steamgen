#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object


void setup() {
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = 0;
  // variable above indicates that 4 resistors were placed on the digit pins.
  // set variable to 1 if you want to use 8 resistors on the segment pins.
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

  pinMode(22, OUTPUT);
  pinMode (24, OUTPUT);
  pinMode (A1, INPUT);
  pinMode(26, OUTPUT);
  Serial.begin(9600);
}
void loop() {

  double wh = 0;
  double circuitVoltage = 9;
  double intensity1 = 0.00203;
  double intensity2 = 0.0021;

  int sensorValue = analogRead(A1);
  float voltage = sensorValue * (5.0 / 1023.0);
  if (voltage < 4) {
    digitalWrite (26, HIGH);
    int power = intensity2 * 100 * circuitVoltage * 3600;
    while (power >= 10000) {
      power /= 10;
    }
    //  Serial.println(power);
    sevseg.setNumber(power, 0);
  }
  else {
    digitalWrite (26, LOW);
    int power = intensity1 * 100 * circuitVoltage * 3600;
    while (power >= 10000) {
      power /= 10;
    }
    //  Serial.println(power);
    sevseg.setNumber(power, 0);
  }

  sevseg.refreshDisplay(); // Must run repeatedly

}
