void align_with_line()
{
	
}

void move_forward(int motor_speed)
{
	
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
  if(is_left_or_right_ir_sensor() && is_back_or_front_line_sensor())
    return true;
  else 
    return false;
}

bool break_is_corner()
{
  return true;
}
