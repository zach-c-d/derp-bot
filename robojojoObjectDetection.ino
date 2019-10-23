#include <AFMotor.h>
#include <Servo.h>

#define  C     131    // 131 Hz
#define  D     147    // 147 Hz
#define  E     165    // 165 Hz
#define  F     175    // 175 Hz
#define  G     196    // 196 Hz
#define  a     220    // 220 Hz
#define  b     247    // 247 Hz
#define  c     262    // 262 Hz
#define  d     294    // 294 Hz
#define  e     330    // 330 Hz
#define  f     349    // 349 Hz
#define  g     392    // 392 Hz

// Define a special note, 'R', to represent a rest
#define  R     0

#define L_EDGE_TRIG 22 
#define L_EDGE_ECHO A9
#define R_EDGE_TRIG 23 
#define R_EDGE_ECHO A8

//IR Sensors
#define LeftIRSensor A10
#define RightIRSensor A12
#define MiddleIRSensor A11 


#define TURN_DIST 20

#define FRONT_TRIG 52 
#define FRONT_ECHO A15

#define SERVO_PIN 10

long duration, cm, cmr;
long lastTurn = millis();

unsigned int S;
unsigned int Sleft;
unsigned int Sright;

int leftDetect;
int rightDetect;
int middleDetect;

AF_DCMotor motorBL(1);
AF_DCMotor motorBR(2);
AF_DCMotor motorFL(3);
AF_DCMotor motorFR(4);


Servo neckControllerServoMotor;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  //Edge detection Ultrasonic setup
   pinMode(L_EDGE_ECHO, INPUT);
   pinMode(L_EDGE_TRIG, OUTPUT);
   pinMode(R_EDGE_ECHO, INPUT);
   pinMode(R_EDGE_TRIG, OUTPUT);

   //Object detection Ultrasonic setup
   pinMode(FRONT_ECHO, INPUT); 
   pinMode(FRONT_TRIG, OUTPUT);

   //Object Detection IR setup
   pinMode(LeftIRSensor, INPUT);
   pinMode(RightIRSensor, INPUT);
   pinMode(MiddleIRSensor, INPUT);
   
   neckControllerServoMotor.attach(SERVO_PIN);
   neckControllerServoMotor.write(75);
   neckControllerServoMotor.detach();
   delay(100);
  
   motorFL.setSpeed(175);
   motorFR.setSpeed(175);
   motorBL.setSpeed(175);
   motorBR.setSpeed(175);

  tone(50, D);
  delay(200);
  tone(50, F);
  delay(200);
  tone(50, a);
  delay(200);
  tone(50, G);
  delay(200);
  tone(50, E);
  delay(200);
  tone(50, D, 400);
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

 //IR SENSOR Stuff
  leftDetect = analogRead(LeftIRSensor);
  rightDetect = analogRead(RightIRSensor);
  middleDetect = analogRead(MiddleIRSensor);

  //IR Sensors
  leftDetect = map(leftDetect, 3, 20,  0, 1000);
  middleDetect = map(middleDetect, 3, 20, 0, 1000);
  rightDetect = map (rightDetect, 3, 20, 0, 1000);

  neckControllerServoMotor.attach(SERVO_PIN);
  neckControllerServoMotor.write(75);
  S = readPing();

  
  Serial.print ("Left IR Sensor: " );
    Serial.println (leftDetect);

     Serial.print ("Middle IR Sensor: " );
    Serial.println (middleDetect);

      Serial.print ("Right IR Sensor: " );
    Serial.println (rightDetect);


  if (S > 0 && S <= TURN_DIST ) {
    turn();
  } 
  
  cm = readLeftSensor();
  cmr = readRightSensor();

  //Check if edge         check if very small object is approaching
  if(cm > 5 || cmr > 5 || cm < 1 || cmr < 1)
  {
    backupAndTurn();  
  }

  if (leftDetect > 0)
  {
    turn(); 
  }

  else if (middleDetect > 0)
  {
    turn(); 
  }

  else if (rightDetect > 0)
  {
    turn(); 
  }
  
  motorFR.run(FORWARD);
  motorFL.run(FORWARD);
  motorBR.run(FORWARD);
  motorBL.run(FORWARD);
  delay(100);
  
  motorFL.run(RELEASE); motorFR.run(RELEASE);
  motorBL.run(RELEASE); motorBR.run(RELEASE);
  delay(100);
  
  
}


//Edge case detection (needs to backup and then go
void backupAndTurn()
{
  //Needs to stop, backup and then turn
  //SHit needs consistency
  //turns are too large (any way to change) 
  //Backup
//  leftMotor1.run(5); motorFL.run(5);//5-> stop
//  motorBR.run(5); motorBL.run(5);
//  delay(400);
    
  if(lastTurn < millis()){
    
    motorFL.run(BACKWARD); motorFR.run(BACKWARD);
    motorBL.run(BACKWARD); motorBR.run(BACKWARD);
    delay(100);
  }
//   //Stop moving
//   motorFR.run(5); motorFL.run(5);//5-> stop
//  motorBR.run(5); motorBL.run(5);
//  motorFR.setSpeed(0); motorFL.setSpeed(0);
//  motorBR.setSpeed(0); motorBL.setSpeed(0);
  //neckControllerServoMotor.write(150);
//  delay(300);
  //Turn left
    motorFL.run(BACKWARD); motorFR.run(FORWARD); // TURN LEFT
    motorBL.run(BACKWARD); motorBR.run(FORWARD);
    
    
    cm = readLeftSensor();
    cmr = readRightSensor();
    S = readPing();
    
    while(cm > 5 || cmr > 5 || cm < 2 || cmr < 2){
      cm = readLeftSensor();
      cmr = readRightSensor();
      S = readPing();
      Serial.print("left sensor: ");
      Serial.println(cm);
      Serial.print("right sensor: ");
      Serial.println(cmr);
      Serial.print("front sensor: ");
      Serial.println(S);
      delay(25);
    }
    delay(random(150, 250));
    lastTurn = millis() + 500;
}

//Turn on obstacle avoidance
void turn() {
  Serial.print("left sensor: ");
      Serial.println(cm);
      Serial.print("right sensor: ");
      Serial.println(cmr);
      Serial.print("front sensor: ");
      Serial.println(S);
  motorFL.run(RELEASE); motorFR.run(RELEASE);
  motorBL.run(RELEASE); motorBR.run(RELEASE);
  leftDetect = readIRleft();
  middleDetect = readIRmiddle();
  rightDetect = readIRright();
  while(leftDetect > 0){
    
    motorFL.run(FORWARD); motorFR.run(BACKWARD); // TURN RIGHT
    motorBL.run(FORWARD); motorBR.run(BACKWARD);
    leftDetect = readIRleft();
    delay(5);
  }
  while(middleDetect > 0){
    
    motorFL.run(FORWARD); motorFR.run(BACKWARD); // TURN RIGHT
    motorBL.run(FORWARD); motorBR.run(BACKWARD);
    middleDetect = readIRmiddle();
    delay(5);
  }
  while(rightDetect > 0){
    
    motorFL.run(BACKWARD); motorFR.run(FORWARD); // TURN LEFT
    motorBL.run(BACKWARD); motorBR.run(FORWARD);
    rightDetect = readIRright();
    delay(5);
  }
//  neckControllerServoMotor.write(150);

  motorFL.run(BACKWARD); motorFR.run(FORWARD); // TURN LEFT
  motorBL.run(BACKWARD); motorBR.run(FORWARD);
  delay(100);
  motorFL.run(RELEASE); motorFR.run(RELEASE);
  motorBL.run(RELEASE); motorBR.run(RELEASE);
  delay(100);
  S = readPing();
  Sleft = S;
  
  delay(300);
//  neckControllerServoMotor.write(75);
    motorFL.run(FORWARD); motorFR.run(BACKWARD); // TURN RIGHT
    motorBL.run(FORWARD); motorBR.run(BACKWARD);
  delay(200);
  motorFL.run(RELEASE); motorFR.run(RELEASE);
  motorBL.run(RELEASE); motorBR.run(RELEASE);
//  neckControllerServoMotor.write(15);
//  delay(300);
  S = readPing();
  Sright = S;
  delay(100);
//  neckControllerServoMotor.write(75);
  motorFL.run(BACKWARD); motorFR.run(FORWARD); // TURN LEFT
  motorBL.run(BACKWARD); motorBR.run(FORWARD);
  delay(100);
  motorFL.run(RELEASE); motorFR.run(RELEASE);
  motorBL.run(RELEASE); motorBR.run(RELEASE);
  delay(300);
  if (Sleft <= TURN_DIST && Sright <= TURN_DIST) {

    motorFL.run(BACKWARD); motorFR.run(BACKWARD);
    motorBL.run(BACKWARD); motorBR.run(BACKWARD);
    delay(100);
    //    int x = random(1);
    //    if (x = 0) {
    //      motorFR.run(4); motorFL.run(4);//4-> right
    //      motorBR.run(4); motorBL.run(4);//4-> right
    //      motorFR.setSpeed(50); motorFL.setSpeed(50);
    //      motorBR.setSpeed(50); motorBL.setSpeed(50);
    //    }
    //    else {
    motorFL.run(BACKWARD); motorFR.run(FORWARD); // TURN LEFT
    motorBL.run(BACKWARD); motorBR.run(FORWARD);
    //    }
    delay(200);
  } else {
    if (Sleft >= Sright) {
    motorFL.run(BACKWARD); motorFR.run(FORWARD); // TURN LEFT
    motorBL.run(BACKWARD); motorBR.run(FORWARD);
    } else {
    motorFL.run(FORWARD); motorFR.run(BACKWARD); // TURN RIGHT
    motorBL.run(FORWARD); motorBR.run(BACKWARD);
    }
    delay(200);
  }
}

float readLeftSensor(void) {
  /**************************************************
      ff 55 len idx action device port slot data a
       0  1  2   3   4      5      6    7    8
  ***************************************************/
  float value = 0.0;
  digitalWrite(L_EDGE_TRIG,LOW);
  delay(0.1);
  digitalWrite(L_EDGE_TRIG,HIGH);
  delay(0.1);
  digitalWrite(L_EDGE_TRIG,LOW);
  
  duration = pulseIn(L_EDGE_ECHO, HIGH);
  
  value = (duration/2) * 0.0343;
  return value;
}

int readIRleft(void) {
  leftDetect = analogRead(LeftIRSensor);

  //IR Sensors
  leftDetect = map(leftDetect, 3, 20,  0, 1000);
  return leftDetect;
}
int readIRright(void) {
  rightDetect = analogRead(RightIRSensor);

  //IR Sensors
  rightDetect = map(rightDetect, 3, 20,  0, 1000);
  return rightDetect;
}
int readIRmiddle(void) {
  middleDetect = analogRead(MiddleIRSensor);

  //IR Sensors
  middleDetect = map(middleDetect, 3, 20,  0, 1000);
  return middleDetect;
}


float readRightSensor(void) {
  /**************************************************
      ff 55 len idx action device port slot data a
       0  1  2   3   4      5      6    7    8
  ***************************************************/
  float value = 0.0;
  digitalWrite(R_EDGE_TRIG,LOW);
  delay(0.1);
  digitalWrite(R_EDGE_TRIG,HIGH);
  delay(0.1);
  digitalWrite(R_EDGE_TRIG,LOW);
  
  duration = pulseIn(R_EDGE_ECHO, HIGH);
  
  value = (duration/2) * 0.0343;
  return value;
}

float readPing(void) {
  /**************************************************
      ff 55 len idx action device port slot data a
       0  1  2   3   4      5      6    7    8
  ***************************************************/
  float value = 0.0;
  digitalWrite(FRONT_TRIG,LOW);
  delay(0.1);
  digitalWrite(FRONT_TRIG,HIGH);
  delay(0.1);
  digitalWrite(FRONT_TRIG,LOW);
  
  duration = pulseIn(FRONT_ECHO, HIGH);
  
  value = (duration/2) * 0.0343;
  return value;
}
