void align_with_line()
{
  int temp = 0, num1 = 0, num2 = 0, num3 = 0 num4 = 0, num5 = 0, num6 = 0;
  
  num1 = digitalRead(lineLeft);
  num2 = digitalRead(lineMiddle);
  num3 = digitalRead(lineRight);
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

void slightRight){
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
	
}

bool break_is_t_corner()
{
  return true;
}

bool break_is_corner()
{
  return true;
}
