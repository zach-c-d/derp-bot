void align_with_line()
{
  int temp = 0, num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0, num6 = 0;
  
  num1 = digitalRead(FR_LINE_TRACKER_L);
  num2 = digitalRead(FR_LINE_TRACKER_M);
  num3 = digitalRead(FR_LINE_TRACKER_R);
  num4 = digitalRead(BK_LINE_TRACKER_L);
  num5 = digitalRead(BK_LINE_TRACKER_M);
  num6 = digitalRead(BK_LINE_TRACKER_R);
  
  if ((num2 == 0 && num5 == 0)) {
    if ( (num1 == 0) && num3 == 1) { //leaning right
      slightLeft();
      
    } else if ((num3 == 0) && (num1 == 1)) { // leaning left
      slightRight();
    }
  } else if(num2 == 0){
    if ( (num1 == 0) && num3 == 1) { //leaning right
      slightLeft();
      
    } else if ((num3 == 0) && (num1 == 1)) { // leaning left
      slightRight();
    }
  } else if(num5 == 0){
    if ( (num4 == 0) && num3 == 6) { //leaning right
      slightLeft();
      
    } else if ((num6 == 0) && (num4 == 1)) { // leaning left
      slightRight();
    }
  } else if(num1 == 0 || num3 == 0){
    if ( (num1 == 1) && num3 == 0 && (num4 == 0 || num6 == 0) { //line is right
      slightRight();
    } else if ((num3 == 1) && (num1 == 0) && (num4 == 0 || num6 == 0)) { // line is left
      slightLeft();
    }
  }
}

void move_forward(int motor_speed)
{
  motorFL.run(FORWARD); motorFR.run(FORWARD);
  motorBL.run(FORWARD); motorBR.run(FORWARD);
	setMotorSpeed(170);
	delay(15);
	setMotorSpeed(60);
	delay(10);
	
}

void slightLeft(){
	motorFL.run(BACKWARD); motorFR.run(FORWARD); // TURN LEFT
  motorBL.run(BACKWARD); motorBR.run(FORWARD);
	delay(10);
	
}

void slightRight()){
	motorFL.run(FORWARD); motorFR.run(BACKWARD); // TURN RIGHT
  motorBL.run(FORWARD); motorBR.run(BACKWARD);
	delay(10);
}

void turn_corner(bool turn_left)
{
  if (turn_left)
  {
	motorFL.run(BACKWARD); motorFR.run(FORWARD); // TURN LEFT
    motorBL.run(BACKWARD); motorBR.run(FORWARD);
	delay(100);
	if (!alined)
	{
		turn_corner(turn_left);
	}else{
		align_with_line();
	}

  }
  else
  {
	motorFL.run(FORWARD); motorFR.run(BACKWARD); // TURN RIGHT
    motorBL.run(FORWARD); motorBR.run(BACKWARD);
	delay(100);
	if (!alined)
	{
		turn_corner(turn_left);
	}else{
		align_with_line();
	}

  }
}

bool break_in_line()
{
  //  FCL        FCR
    //  *          *
    //       FLT
    //    FL|FM|FR
    //       ***
    //
    //       ***
    //    BL|BM|BR
    //       BLT
    //  *          *
    // BCL        BCR

    // (FCL && (FLT || BLT)) --> LCorner
    // (FCR && (FLT || BLT)) --> RCorner
    // (!FLT && BLT) --> FGap
    // (FLT && !BLT) --> BGap

    //if back is aligned
    //return true
    if (digitalRead(BK_LINE_TRACKER_L) == 1 &&
        digitalRead(BK_LINE_TRACKER_M) == 0 &&
        digitalRead(BK_LINE_TRACKER_R) == 1)
        {
          //and if front detects gap
          if (digitalRead(FR_LINE_TRACKER_L) == 1 &&
              digitalRead(FR_LINE_TRACKER_M) == 1 &&
              digitalRead(FR_LINE_TRACKER_R) == 1) 
              {
                return true;
              }
              //else there is no gap
              //go back to the beginning and run align_with_line
              //and move_forward again
              else{
                return false;
              }
        }
        //else if back isn't aligned run align fucntion
        //again you patoot!
        else{
          align_with_line();
        }
}

bool break_is_t_corner()
{
  if(break_in_line() && is_left_or_right_ir_sensor())
    return true;
  return false;
}

bool break_is_corner()
{
  if(break_in_line() && !back_line_sensor() && front_line_sensor() && get_left_ir_sensor())
      return true;
  return false;
}
