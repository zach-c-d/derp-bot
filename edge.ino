/*
 * created by Rui Santos, https://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
 */
 
int trigPin = 11;    
int echoPin = 12;    
long duration, cm, inches;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  digitalWrite(trigPin, LOW);
  delay(0.1);
  digitalWrite(trigPin, HIGH);
  delay(0.1);
  digitalWrite(trigPin, LOW);
 
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  cm = (duration/2) * 0.0343;    
  inches = (duration/2) * 0.0135; 
  
  if (cm > 5)
  {
    Serial.print("Edge\n");
  }
  Serial.println(String(inches) + "in, " +  String(cm) + " cm");
  Serial.println();
  
  delay(250);
}
