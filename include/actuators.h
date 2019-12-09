//Front Line Sensor
#define FR_LINE_TRACKER_L 52
#define FR_LINE_TRACKER_M 53
#define FR_LINE_TRACKER_R 51

//Back Line Sensor
#define TURN_DIST 15
#define BK_LINE_TRACKER_L 39
#define BK_LINE_TRACKER_M 35
#define BK_LINE_TRACKER_R 37

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
              digitalRead(FR_LINE_TRACKER_R) == 1) )
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
  return true;
}

bool break_is_corner()
{
  return true;
}
