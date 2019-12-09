
// 0---0-----0-----0---0
// |         |         |                T  |  F  |  RES
// | |_|_|_| | |_|_|_| |              
// | | | | | | | | | | |                FL          turnSMRight()       
// |         |         |                BR
// 0---0-----0-----0---0                
// |         |         |                FR          turnSMLeft()
// | |_|_|_| | |_|_|_| | FL|FM|FR       BL
// | | | | | | | | | | |    ***
// |         |         |    
// 0---0-----0-----0---0    ***
//                       BL|BM|BR   

#include <AFMotor.h>
#include <Servo.h>
#include "Adafruit_VL53L0X.h"

//#define  C     131    // 131 Hz
//#define  D     147    // 147 Hz
//#define  E     165    // 165 Hz
//#define  F     175    // 175 Hz
//#define  G     196    // 196 Hz
//#define  a     220    // 220 Hz
//#define  b     247    // 247 Hz
//#define  c     262    // 262 Hz
//#define  d     294    // 294 Hz
//#define  e     330    // 330 Hz
//#define  f     349    // 349 Hz
//#define  g     392    // 392 Hz

// Define a special note, 'R', to represent a rest
#define  R     0

//Ultrasonic for Edge Detection
#define L_EDGE_TRIG 23 
#define L_EDGE_ECHO A9
#define R_EDGE_TRIG 22 
#define R_EDGE_ECHO A8

//IR Sensors for Obstacle Avoidance
#define LeftIRSensor 48
#define RightIRSensor 26
//#define MiddleIRSensor A10 

//Front Line Sensor
#define lineLeft 52
#define lineRight 51
#define lineMiddle 53

//Back Line Sensor
#define TURN_DIST 15
#define BK_LINE_TRACKER_L 39 
#define BK_LINE_TRACKER_M 35
#define BK_LINE_TRACKER_R 37

//Flame Sensor and IR Sensors for Flame Sensing
#define flameSensor A10
#define flameDetectLeft A12
#define flameDetectRight A11

//#define FRONT_TRIG 52 
//#define FRONT_ECHO A15

#define SERVO_PIN 10

long lastTurn = millis();

unsigned int S;
unsigned int Sleft;
unsigned int Sright;

int motorSpeed = 200;

int leftDetect;
int rightDetect;
//int middleDetect;

AF_DCMotor motorBL(1);
AF_DCMotor motorBR(2);
AF_DCMotor motorFL(3);
AF_DCMotor motorFR(4);


Adafruit_VL53L0X lox = Adafruit_VL53L0X();

Servo neckControllerServoMotor;

inline void turnLeft(){
    motorFL.run(BACKWARD); motorFR.run(FORWARD); // TURN LEFT
    motorBL.run(BACKWARD); motorBR.run(FORWARD);
}

inline void turnRight(){
    motorFL.run(FORWARD); motorFR.run(BACKWARD); // TURN RIGHT
    motorBL.run(FORWARD); motorBR.run(BACKWARD);
    
}

inline void forward(){
    motorFL.run(FORWARD); motorFR.run(FORWARD);
    motorBL.run(FORWARD); motorBR.run(FORWARD);
}

inline void backward(){
    motorFL.run(BACKWARD); motorFR.run(BACKWARD);
    motorBL.run(BACKWARD); motorBR.run(BACKWARD);
}

inline void stopp(){
    motorFL.run(RELEASE); motorFR.run(RELEASE); // STOP
    motorBL.run(RELEASE); motorBR.run(RELEASE);
}

void setup() {
  Serial.begin(9600);
    delay(100);
  while (! Serial) {
    delay(1);
    
  }
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println("Failed to boot VL53L0X");
    delay(4000);
  }
   

   //Object detection Ultrasonic setup
//   pinMode(FRONT_ECHO, INPUT); 
//   pinMode(FRONT_TRIG, OUTPUT);

   //Object Detection IR setup
//   pinMode(LeftIRSensor, INPUT);
//   pinMode(RightIRSensor, INPUT);
//   pinMode(MiddleIRSensor, INPUT)+


;
   
   neckControllerServoMotor.attach(SERVO_PIN);
   neckControllerServoMotor.write(90);
   delay(100);
   neckControllerServoMotor.detach();
  
   setMotorSpeed(150);

//  tone(50, D);
//  delay(200);
//  tone(50, F);
//  delay(200);
//  tone(50, a);
//  delay(200);
//  tone(50, G);
//  delay(200);
//  tone(50, E);
//  delay(200);
//  tone(50, D, 400);
   /*
      Serial.print("left sensor: ");
      Serial.println(readLeftSensor());
      Serial.print("right sensor: ");
      Serial.println(readRightSensor());
      Serial.print("front sensor: ");
      Serial.println(readPing());
      */
}

void loop() {
  // put your main code here, to run repeatedly:

  neckControllerServoMotor.attach(SERVO_PIN);
   neckControllerServoMotor.write(90);
  delay(50);
  S = readPing();
 //IR SENSOR Stuff
   leftDetect = digitalRead(LeftIRSensor);
   rightDetect = digitalRead(RightIRSensor);
//  middleDetect = digitalRead(MiddleIRSensor);

  
  Serial.print ("Left IR Sensor: " );
    Serial.println (leftDetect);

//     Serial.print ("Middle IR Sensor: " );
//    Serial.println (middleDetect);

    Serial.print ("Right IR Sensor: " );
    Serial.println (rightDetect);


  if (S > 0 && S <= TURN_DIST ) {
    turn();
  } 
  
  
  //Check if edge         check if very small object is approaching
  if (leftDetect == 0)
  {
    turn(); 
  }

  else if (rightDetect == 0)
  {
    turn(); 
  }

  //Flame Sensor
  findFire();
  
  //Line Sensor
  moveTrack();
  forward();
  setMotorSpeed(170);
  delay(15);
  
//  motorFL.run(RELEASE); motorFR.run(RELEASE);
//  motorBL.run(RELEASE); motorBR.run(RELEASE);
  setMotorSpeed(60);
  delay(10);
//  setMotorSpeed(50);
//  delay(5);
  
  
}


//Edge case detection (needs to backup and then go
void backupAndTurn()
{
    stopp();
    setMotorSpeed(150);
  //Needs to stop, backup and then turn
  //SHit needs consistency
  //turns are too large (any way to change) 
  //Backup
//  leftMotor1.run(5); motorFL.run(5);//5-> stop
//  motorBR.run(5); motorBL.run(5);
//  delay(400);
    
  if(lastTurn < millis()){
    
    backward();
    setMotorSpeed(150);
    delay(20);
    setMotorSpeed(70);
    delay(10);
  }
//   //Stop moving
//   motorFR.run(5); motorFL.run(5);//5-> stop
//  motorBR.run(5); motorBL.run(5);
//  motorFR.setSpeed(0); motorFL.setSpeed(0);
//  motorBR.setSpeed(0); motorBL.setSpeed(0);
  //neckControllerServoMotor.write(150);
//  delay(300);
    backward();
    setMotorSpeed(150);
    delay(15);
    setMotorSpeed(60);
    delay(15);
  //Turn left
    backward();
    setMotorSpeed(200);
    
    
    S = readPing();
    
    
    delay(random(50, 100));
    lastTurn = millis() + 900;
}

//Turn on obstacle avoidance
void turn() {
  stopp();
  setMotorSpeed(150);
  Serial.print("left sensor: ");
  Serial.print("right sensor: ");
  Serial.print("front sensor: ");
  Serial.println(S);
  stopp();
  leftDetect = digitalRead(LeftIRSensor);
//  middleDetect = readIRmiddle();
   rightDetect = digitalRead(RightIRSensor);
  while(leftDetect == 0){
    
    backward();
    leftDetect = digitalRead(LeftIRSensor);
    delay(5);
  }
//  while(middleDetect > 0){
//    
//    motorFL.run(BACKWARD); motorFR.run(BACKWARD);
//    motorBL.run(BACKWARD); motorBR.run(BACKWARD);
//    delay(5);
//    motorFL.run(FORWARD); motorFR.run(BACKWARD); // TURN RIGHT
//    motorBL.run(FORWARD); motorBR.run(BACKWARD);
//    middleDetect = readIRmiddle();
//    delay(5);
//  }
  while(rightDetect == 0){
    
    backward();
    rightDetect = digitalRead(RightIRSensor);
    delay(5);
  }

//  motorFL.run(BACKWARD); motorFR.run(FORWARD); // TURN LEFT
//  motorBL.run(BACKWARD); motorBR.run(FORWARD);
//  delay(100);
  stopp();
  neckControllerServoMotor.write(175);
  delay(300);
  S = readPing();
  Sright = S;
  
  Serial.print("right: ");
  Serial.println(Sright);
  delay(300);
  neckControllerServoMotor.write(90);
//    motorFL.run(FORWARD); motorFR.run(BACKWARD); // TURN RIGHT
//    motorBL.run(FORWARD); motorBR.run(BACKWARD);
  delay(300);
//  motorFL.run(RELEASE); motorFR.run(RELEASE);
//  motorBL.run(RELEASE); motorBR.run(RELEASE);
  neckControllerServoMotor.write(15);
  delay(300);
  S = readPing();
  Sleft = S;
  Serial.print("left: ");
  Serial.println(Sleft);
  delay(300);
  neckControllerServoMotor.write(90);
//  motorFL.run(BACKWARD); motorFR.run(FORWARD); // TURN LEFT
//  motorBL.run(BACKWARD); motorBR.run(FORWARD);
//  delay(100);
//  motorFL.run(RELEASE); motorFR.run(RELEASE);
//  motorBL.run(RELEASE); motorBR.run(RELEASE);
  delay(300);
  if (Sleft <= TURN_DIST && Sright <= TURN_DIST) {

    backward();
    delay(50);
    if (Sleft >= Sright) {
      turnLeft();
    } else {
      turnRight();
    }
    delay(200);
  } else {
    if (Sleft >= Sright) {
      turnLeft();
    } else {
      turnRight();
    }
    delay(200);
  }
}
void moveTrack(void)
{
  
  stopp();
  setMotorSpeed(200);
  int temp = 0, num1 = 0, num2 = 0, num3 = 0;
  
  num1 = digitalRead(lineLeft);
  num2 = digitalRead(lineMiddle);
  num3 = digitalRead(lineRight);
//  Serial.print("left line: ");
//  Serial.println(num1);
//  Serial.print("middle line: ");
//  Serial.println(num2);
//  Serial.print("right line: ");
//  Serial.println(num3);

  if ((num2 == 0)) {
//    num1 = digitalRead(lineLeft);
//    num2 = digitalRead(lineMiddle);
//    num3 = digitalRead(lineRight);
//    if ((num2 == 0) && (num1 == 0) && (num3 == 0)) {
//      leftMotor1.run(5); rightMotor1.run(5);//5-> stop
//      leftMotor2.run(5); rightMotor2.run(5);
//      leftMotor1.setSpeed(0); rightMotor1.setSpeed(0);
//      leftMotor2.setSpeed(0); rightMotor2.setSpeed(0);
//      continue;
//    } else 
    if ( (num1 == 0) && num3 == 1) { //leaning right
      turnLeft();
      delay(40);
      stopp();
      
//      while (1) {
//        num2 = digitalRead(lineMiddle);
//        if (num2) {
//          motorFL.run(RELEASE); motorFR.run(FORWARD); // TURN LEFT
//          motorBL.run(RELEASE); motorBR.run(FORWARD);
//          continue;
//        }else{
//          motorFL.run(FORWARD); motorFR.run(FORWARD); // TURN LEFT
//          motorBL.run(FORWARD); motorBR.run(FORWARD);
//          break;
//        }
//      }
    } else if ((num3 == 0) && (num1 == 1)) { // leaning left
      turnRight();
      delay(40);
      stopp();
//      while (1) {
//        num2 = digitalRead(lineMiddle);
//        if (num2) {
//          motorFL.run(FORWARD); motorFR.run(RELEASE); // TURN RIGHT
//          motorBL.run(FORWARD); motorBR.run(RELEASE);
//          continue;
//        }else{
//          motorFL.run(FORWARD); motorFR.run(FORWARD); // TURN LEFT
//          motorBL.run(FORWARD); motorBR.run(FORWARD);
//          break;
//        }
//      }
    }
//    motorFL.run(FORWARD); motorFR.run(FORWARD);
//    motorBL.run(FORWARD); motorBR.run(FORWARD);
  } else if(num1 == 0 || num3 == 0){
    if ( (num1 == 1) && num3 == 0) { //line is right
      turnRight();
//      while (1) {
//        num2 = digitalRead(lineMiddle);
//        if (num2) {
//          motorFL.run(RELEASE); motorFR.run(FORWARD); // TURN LEFT
//          motorBL.run(RELEASE); motorBR.run(FORWARD);
//          continue;
//        }else{
//          motorFL.run(FORWARD); motorFR.run(FORWARD); // TURN LEFT
//          motorBL.run(FORWARD); motorBR.run(FORWARD);
//          break;
//        }
//      }
      delay(20);
      stopp();
    } else if ((num3 == 1) && (num1 == 0)) { // line is left
      turnLeft();
//      while (1) {
//        num2 = digitalRead(lineMiddle);
//        if (num2) {
//          motorFL.run(FORWARD); motorFR.run(RELEASE); // TURN RIGHT
//          motorBL.run(FORWARD); motorBR.run(RELEASE);
//          continue;
//        }else{
//          motorFL.run(FORWARD); motorFR.run(FORWARD); // TURN LEFT
//          motorBL.run(FORWARD); motorBR.run(FORWARD);
//          break;
//        }
//      }
      delay(20);
      stopp();
    }

    
  }
}

void findFire (void)
{
  //Read sensor on analog
  //Sensor reads from 0 - 1000; 0 being closest, 1000 being farthest
  float flameDistanceReading = analogRead(flameSensor);
  float flameCheckLeft = analogRead(flameDetectLeft);
  float flameCheckRight = analogRead(flameDetectRight);
    Serial.print ("Flame right: " );
    Serial.println (flameCheckRight);
    Serial.print ("Flame left: " );
    Serial.println (flameCheckLeft);

  float fireCloseDistance = 100;  //fire is close
  float fireFarDistance = 600;    //fire is too far, no need to care about it
  
  //Main Principle: find fire, center onto fire and head towards it
  //Robot ignores line tracking while a fire is in sight
  //1. If center is LESS THAN OR EQUAL TO fireCloseDistance, stop robot
  //2. if fire hits the left check AND center is GREATER THAN fireFarDistance, turn left to center
  //3. if fire hits the right check AND center is GREATER THAN fireFarDistance, turn right to center
  //4. if fire hits left check AND center is LESS THAN fireFarDistance, turn left moving forward
  //5. if fire hits right check AND center is LESS THAN fireFarDistance, turn right moving forward
  //6. if both left AND right check is off, && center is GREATER THAN fireCloseDistance, drive forward
  
  //Check if outside sensors (flameCheckLeft, flameCheckRight) see a fire
  //IR Digital Sensors: 
  //if there is no object. 1 if there is an object
  //Notes: If Left check is only one on, make full turn (no movement) [ vice versa]
  //       If Left check and center "on", make small adjustment and be moving foward [ vice versa ]
  
  //1. If center is LESS THAN OR EQUAL TO 300, stop robot
  while (flameDistanceReading <= fireCloseDistance || flameCheckLeft <= fireCloseDistance || flameCheckRight <= fireCloseDistance)
  {
    //Stop Robot
    stopp();
    flameDistanceReading = analogRead(flameSensor);
    flameCheckLeft = analogRead(flameDetectLeft);
    flameCheckRight = analogRead(flameDetectRight);
    Serial.print ("Flame Sensor: " );
    Serial.println (flameDistanceReading);
    Serial.print ("Flame right: " );
    Serial.println (flameCheckRight);
    Serial.print ("Flame left: " );
    Serial.println (flameCheckLeft);
    delay(60);
  }

  //6. If both left AND right check if off && center is GREATER THAN 100, drive forward
  if (flameDistanceReading > fireCloseDistance && flameDistanceReading < fireFarDistance)
  {
    //Robot moves forward
    //Also ignore line tracking
    setMotorSpeed(150);
    forward();
    delay(20);
    setMotorSpeed(60);
  }

  //2. If fire hits the left check AND center is GREATER THAN fireFarDistance, turn left to center
  if (flameCheckLeft < fireFarDistance && flameDistanceReading > fireFarDistance)
  {
    //Stop Robot, turn left to adjust
    setMotorSpeed(150);
    turnLeft();
    delay(50); //big turn to center
    setMotorSpeed(60);
  }
   
  //3. If fire hits the right check, AND center is GREATER THAN fireFarDistance, turn right to center
  if (flameCheckRight < fireFarDistance && flameDistanceReading > fireFarDistance)
  {
    //Stop Robot, turn right to adjust
    setMotorSpeed(150);
    turnRight();
    delay(50); //big turn to center
    setMotorSpeed(50);
  }

  //4. if fire hits left check AND center is LESS THAN fireFarDistance, turn left moving forward
  if (flameCheckLeft < fireFarDistance && flameDistanceReading <= fireFarDistance)
  {
    //Slight adjustment (variable speeds) to adjust to the left
    setMotorSpeed(150);
    turnLeft();
    delay(25); //small turn to center
    setMotorSpeed(50);
  }
  
  //5. if fire hits right check AND center is LESS THAN fireFarDistance, turn right moving forward 
  if (flameCheckRight < fireFarDistance && flameDistanceReading <= fireFarDistance)
  {
    //Slight Adjustment (variable speeds) to adjust to the right
    setMotorSpeed(150);
    turnRight();
    delay(25); //small turn to center
    setMotorSpeed(50);
  }
  
  
}

void bitchImOnLine(void)
{
  
}

void setMotorSpeed(int mSpeed){
   motorFL.setSpeed(mSpeed);
   motorFR.setSpeed(mSpeed);
   motorBL.setSpeed(mSpeed);
   motorBR.setSpeed(mSpeed);
}


float readPing(void) {
  /**************************************************
      ff 55 len idx action device port slot data a
       0  1  2   3   4      5      6    7    8
  ***************************************************/
  float value = 0.0;
//  digitalWrite(FRONT_TRIG,LOW);
//  delay(0.1);
//  digitalWrite(FRONT_TRIG,HIGH);
//  delay(0.1);
//  digitalWrite(FRONT_TRIG,LOW);
//  
//  duration = pulseIn(FRONT_ECHO, HIGH);
//  
//  value = (duration/2) * 0.0343;
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    
    Serial.println(measure.RangeStatus);
    
    value = (measure.RangeMilliMeter / 10);
  } else {
    Serial.println(" out of range ");
    
    Serial.println(measure.RangeStatus);
    value = 100;
  }
  return value;
}
