#include <AFMotor.h>
#include <Servo.h>
#include "Adafruit_VL53L0X.h"



// Define a special note, 'R', to represent a rest
#define  R     0

//Ultrasonic for Edge Detection
#define L_EDGE_TRIG 23 
#define L_EDGE_ECHO A9
#define R_EDGE_TRIG 22 
#define R_EDGE_ECHO A8

//IR Sensors for Obstacle Avoidance
#define LEFT_IR_SENSOR 48
#define RIGHT_IR_SENSOR 26
//#define MiddleIRSensor A10 

//Front Line Sensor
#define FR_LINE_TRACKER_L 52
#define FR_LINE_TRACKER_M 53
#define FR_LINE_TRACKER_R 51

//Back Line Sensor
#define BK_LINE_TRACKER_L 39
#define BK_LINE_TRACKER_M 35
#define BK_LINE_TRACKER_R 37

//Front Line Sensor
#define LINE_LEFT 52
#define LINE_RIGHT 51
#define LINE_MIDDLE 53

//not sure what this is???
#define TURN_DIST 15

//Flame Sensor and IR Sensors for Flame Sensing
#define FLAME_SENSOR A10
#define FLAME_DETECT_LEFT A12
#define FLAME_DETECT_RIGHT A11

//#define FRONT_TRIG 52 
//#define FRONT_ECHO A15

#define SERVO_PIN 10

#include "include/sensors.h"
#include "include/actuators.h"

int motor_speed = 450;
String last_corner_turn;

//state statuses
bool _navigate = false;
bool _retrieve = false;
bool _deliver = false;


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

void retrieve()
{
  //rotate bot 
}

void setup()
{

}

void loop()
{
  //if all states are false, begin with navigate state again
  if (_navigate == false && _retrieve == false && _deliver == false)
  {
    _navigate = true;
  }
  if(_navigate == true)
  {
    navigate();
  }
  else if (_retrieve == true)
  {
    retrieve();
  }
  else if (_deliver == true)
  {
    deliver();
  }
  else
  {
    Serial.println("No State set you doofus!");
  }
}
