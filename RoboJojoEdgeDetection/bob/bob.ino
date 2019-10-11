#include <UCMotor.h>

#define FD_SPEED 100
#define BK_SPEED 100
#define LT_SPEED 200
#define RT_SPEED 200


#define TRIG_PIN A2
#define ECHO_PIN A3

#define OUT3  13
#define OUT2  A1
#define OUT1  A0

#define ULTRASONIC_SENSOR 55

UC_DCMotor leftMotor1(3, MOTOR34_64KHZ);
UC_DCMotor rightMotor1(4, MOTOR34_64KHZ);
UC_DCMotor leftMotor2(1, MOTOR34_64KHZ);
UC_DCMotor rightMotor2(2, MOTOR34_64KHZ);

char buffer[52];
union {
  byte byteVal[4];
  float floatVal;
  long longVal;
} val;


struct {
  int fd = 1;
  int bk = 2;
  int lt = 3;
  int rt = 4;
  int st = 5;
}Move;

long duration, cm;

void setup() {
  // put your setup code here, to run once:
  pinMode(ECHO_PIN, INPUT); //Set the connection pin output mode Echo pin
  pinMode(TRIG_PIN, OUTPUT);//Set the connection pin output mode trog pin
  
  // Obsticle Avoidance  
  pinMode(OUT3, INPUT);
  pinMode(OUT2, INPUT);
  pinMode(OUT1, INPUT);
  
  Serial.begin(115200);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  /*==========EDGE DETECTION==========*/
  cm = readPing();
  Serial.print("sensor: ");
  Serial.println(cm);

  if(cm > 10){
//      fdBk(Move.st);
//      for (int i=0; i < 20; i++){
//        fdBk(Move.bk);
//     }
      
      fdBk(Move.bk);
      fdBk(Move.rt);
//     if(random(1,2) == 1)
//      fdBk(Move.lt);
//     else fdBk(Move.rt);
         
    }else{
//      fdBk(Move.fd);

    // Obsticle Avoidance
    int detect3 = digitalRead(OUT3);
    int detect2 = analogRead(OUT2);
    int detect1 = analogRead(OUT1);
    detect2 = map(detect2, 3, 20, 0, 1000);
    detect3 = map(detect3, 1, 20, 0, 500);
    detect1 = map(detect1, 3, 20, 0, 1000);
    Serial.println(detect3);
    if(detect3 <0 || detect2 >0 || detect1 >0){
        Serial.println("Obsticle");
        fdBk(Move.rt);
      }
      
     else{
        Serial.println("void");
        fdBk(Move.fd);  
      }
    }  
    
      
    delay(300);     
     
}


inline void sSpeed(int s){
  leftMotor1.setSpeed(s); rightMotor1.setSpeed(s);
  leftMotor2.setSpeed(s); rightMotor2.setSpeed(s);
    
}

inline void setRun(int c){
  leftMotor1.run(c); rightMotor1.run(c);
  leftMotor2.run(c); rightMotor2.run(c);  
}

void fdBk(int cond){
  setRun(cond);
  switch(cond){
    case 1://1-->forward
        sSpeed(FD_SPEED);break;
    case 2://2 --> backward
        sSpeed(BK_SPEED);break;
    case 3://3 --> left
        sSpeed(LT_SPEED);break;
    case 4:
        sSpeed(RT_SPEED);break;
    case 0:
        sSpeed(0);break;
    }
  
    delay(30);
}
        


///////////////////////////////////////////////////

unsigned char readBuffer(int index) {
  return buffer[index];
}
void writeBuffer(int index, unsigned char c) {
   buffer[index] = c;
  
}

void writeSerial(unsigned char c) {
  Serial.write(c);
#if defined(__AVR_ATmega32U4__)
  Serial1.write(c);
#endif
}

void sendFloat(float value) {
  writeSerial(0x2);
  val.floatVal = value;
  writeSerial(val.byteVal[0]);
  writeSerial(val.byteVal[1]);
  writeSerial(val.byteVal[2]);
  writeSerial(val.byteVal[3]);
}
void readSensor(int device) {
  /**************************************************
      ff 55 len idx action device port slot data a
       0  1  2   3   4      5      6    7    8
  ***************************************************/
  float value = 0.0;
  int port, slot, pin;
  port = readBuffer(6);
  pin = port;
  switch (device) {
    case ULTRASONIC_SENSOR: {
        value = readPing();
        sendFloat(value);
      }
      break;
  }
}

int getUltrasonicVal(void)
{
  unsigned char cnt = 0;
  long cm, beginTime, stopTime;
  long waitCount = 0;
  pinMode(TRIG_PIN, OUTPUT); pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(5);
  digitalWrite(TRIG_PIN, LOW);  waitCount = 0;
  while (!(digitalRead(ECHO_PIN) == 1)) {
    if (++waitCount >= 30000)
      break;
  }
  beginTime = micros(); waitCount = 0;
  while (!(digitalRead(ECHO_PIN) == 0)) {
    if (++waitCount >= 30000)
      break;
  }
  stopTime = micros();
  cm  = (float)(stopTime - beginTime) / 1000000 * 34000 / 2;
  return cm;
}

int readPing(void)
{
  int Res[3];
  int res;
  int maxvalue;
  int minvalue;

  for (int i = 0; i < 3; i++)
  {
    Res[i] = getUltrasonicVal();
    delay(10);
  }
  maxvalue = Res[0] >= Res[1] ? Res[0] : Res[1];
  maxvalue = maxvalue >= Res[2] ? maxvalue : Res[2];
  minvalue = Res[0] <= Res[1] ? Res[0] : Res[1];
  minvalue = minvalue <= Res[2] ? minvalue : Res[2];
  res = Res[0] + Res[1] + Res[2] - maxvalue - minvalue;
  return res;
}
