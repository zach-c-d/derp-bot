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
  //make sure dis bot is frickin aligned!!!
  //do not leave this function until you very very sure!
  align_with_line();
  //once bot is aligned with line, move forward one unit
  move_forward(motor_speed);

  //when break in line is found
  if(break_in_line())
  {
    //check to see if its de corner
    if(break_is_corner())
    {
      turn_corner(last_corner_turn);
    }
    //if break is not corner, it must be a ball container
    else
    {
      //check to see if there is a candle lit in the ball containment area
      if(check_fire_right())
      {

      }
      else if(check_fire_left())
      {
        
      }
    }
  }
}
