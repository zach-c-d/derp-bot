#include <UCMotor.h>

UC_DCMotor leftMotor1(3, MOTOR34_64KHZ);
UC_DCMotor rightMotor1(4, MOTOR34_64KHZ);
UC_DCMotor leftMotor2(1, MOTOR34_64KHZ);
UC_DCMotor rightMotor2(2, MOTOR34_64KHZ);


void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  leftMotor1.run(1); rightMotor1.run(1);
  leftMotor2.run(1); rightMotor2.run(1);
  leftMotor1.setSpeed(200); rightMotor1.setSpeed(200);
  leftMotor2.setSpeed(200); rightMotor2.setSpeed(200);
}
