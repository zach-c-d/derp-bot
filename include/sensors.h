// bool check_fire()
// {
//     if (check_fire_left() || check_fire_right())
//     {
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }
// bool check_fire_left()
// {

<<<<<<< HEAD
// }
// bool check_fire_right()
// {

// }
void findFire ()
=======
}

bool check_fire_left()
>>>>>>> 49c9f633ecedc198317e02a86ce5512298102078
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

<<<<<<< HEAD
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
=======
bool check_fire_right()
{

}

>>>>>>> 49c9f633ecedc198317e02a86ce5512298102078

bool get_left_ir_sensor(){
    return digitalRead(LEFT_IR_SENSOR);
}

bool get_right_ir_sensor(){
    return digitalRead(RIGHT_IR_SENSOR);
}

bool is_left_or_right_ir_sensor(){
	if(get_left_ir_sensor()){
		leftCorner = true;
	}
	if(get_right_ir_sensor()){
		rightCorner = true;
	}
    return leftCorner || rightCorner;
}

bool front_line_sensor(){

    return digitalRead(FR_LINE_TRACKER_L) || digitalRead(FR_LINE_TRACKER_M) || digitalRead(FR_LINE_TRACKER_R);

}

bool back_line_sensor(){
    return digitalRead(BK_LINE_TRACKER_L) || digitalRead(BK_LINE_TRACKER_M) || digitalRead(BK_LINE_TRACKER_R);
}
 
bool is_back_or_front_line_sensor(){
    return front_line_sensor() || back_line_sensor();
}

float readPing() {
  float value = 0.0;
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
