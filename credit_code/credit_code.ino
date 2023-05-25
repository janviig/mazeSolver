#include <Wire.h>
#include <ZumoShield.h>

ZumoMotors motorsRobot;
Pushbutton calibrateButton (ZUMO_BUTTON);

//robot moving backwards method
void move_backwards()
{
  motorsRobot.setSpeeds(100, 100);
  delay(3000);
  motorsRobot.setSpeeds(0, 0);
}

//robot moving right method
void move_right()
{
  motorsRobot.setSpeeds(-100, 100);
  delay(2000);
  motorsRobot.setSpeeds(0, 0);
}

//robot moving right method
void backwards_move_right()
{
  motorsRobot.setSpeeds(-90, 90);
  delay(2000);
  motorsRobot.setSpeeds(0, 0);
}

//robot moving left method
void move_left()
{
  //left motor, right motor
  motorsRobot.setSpeeds(100, -100);
  delay(1000);
  motorsRobot.setSpeeds(0, 0);
}

//robot moving forward method
void move_forward()
{
  motorsRobot.setSpeeds(-100, -100);
  delay(6000);
  motorsRobot.setSpeeds(0, 0);
}

//robot moving forward right method
void move_forward_right()
{
  motorsRobot.setSpeeds(-100, -100);
  //delay is less than move_forward method
  delay(3000);
  motorsRobot.setSpeeds(0, 0);
}

//stopping the motors
void stop_speed()
{
  motorsRobot.setSpeeds(0, 0);
}

void setup()
{
  motorsRobot.flipLeftMotor(true);
  motorsRobot.flipRightMotor(true);

  //calibrate button 
  calibrateButton.waitForButton();
  calibrateButton.waitForRelease();
}

void loop()
{
  //execute path for maze

  move_forward();
  delay(2000);

  //turning left and moving forward
  move_left();
  delay(2000);
  move_forward();
  delay(2000);

  //turning right and moving forward
  move_right();
  delay(2000);
  move_forward_right();
  delay(2000);

  //move backwards, turn right & move forward
  move_backwards();
  delay(2000);
  backwards_move_right();
  delay(2000);
  move_forward();
  delay(1000);

  //turn left and move forwards
  move_left();
  delay(2000);
  move_forward();
  delay(3000);

  move_left();
  delay(2000);
  
  move_forward_right();
  delay(2000);
  
  stop_speed();
}
