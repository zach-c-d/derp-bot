x`bool check_fire()
{

}
bool check_fire_left()
{

}


bool get_left_ir_sensor(){
    return digitalRead(LEFT_IR_SENSOR);
}

bool get_right_ir_sensor(){
    return digitalRead(RIGHT_IR_SENSOR);
}

bool is_left_or_right_ir_sensor(){
    return get_left_ir_sensor() || get_right_ir_sensor();
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
