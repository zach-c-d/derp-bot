x`bool check_fire()
{

}

bool check_fire_left()
{

}

bool check_fire_right()
{

}


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
