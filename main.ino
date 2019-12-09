#include <AFMotor.h>
#include <Servo.h>
#include "Adafruit_VL53L0X.h"

#include "include/sensors.h"
#include "include/actuators.h"



int motor_speed = 450;
String last_corner_turn;


void navigate(){
  //make sure dis bot is frickin aligned!!!
  //do not leave this function until you very very sure!
  align_with_line();
  //once bot is aligned with line, move forward one unit
  move_forward(motor_speed);

  //when break in line is found
  if(break_in_line())
  {
    //check to see if its de t-corner
    if(break_is_t_corner())
    {
      //if last turn was left, go right. else go left
      //if can't go left, go right
      //if can't go right, go left
      turn_corner(if_last_turn_left);
    }
    //else, check to see if it's a regular old corner
    else if(break_is_corner())
    {

    }
    //else it must be a ball container
    else
    {
      if (check_fire()){
        //a fire at a containment! It must be the ball!
        //engage ball retrieve!!
        ball_retrieve = true;
      }

    }
  }
}

void setup()
{

}

void loop()
{
  if(_navigate == true)
  {
    navigate();
  }
  else if (_retrieve == true)
  {
    retrieve();
  }
}
