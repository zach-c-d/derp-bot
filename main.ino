#include <AFMotor.h>
#include <Servo.h>
#include "Adafruit_VL53L0X.h"
// #include "include/functions.h"

//

int motor_speed = 450;
String last_corner_turn;

void setup()
{

}

void loop()
{
  align_with_line();
  //once bot is aligned with line, move forward one unit
  move_forward(motor_speed);

  //when break
  if(break_in_line())
  {
    if(break_is_corner())
    {
      turn_corner(last_corner_turn);
    }
    else
    {

    }
  }
}
