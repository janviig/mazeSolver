#include <Wire.h>
#include <ZumoShield.h>

ZumoMotors motorsRobot;
ZumoBuzzer buzz;
Pushbutton calibrateButton (ZUMO_BUTTON);

//stopping the motors
void stop_speed()
{
  motorsRobot.setSpeeds(0, 0);
  buzz.play(">>a32");
}

void setup()
{
  buzz.play(">g32>>c32");
  motorsRobot.flipLeftMotor(true);
  motorsRobot.flipRightMotor(true);

  //calibrate button 
  calibrateButton.waitForButton();
  calibrateButton.waitForRelease();
  buzz.play("L16 cdegreg4");
}

void loop()
{
  //execute path for maze
  motorsRobot.setSpeeds(-100, -100);
  delay(6000);

  //turning left and moving forward
  motorsRobot.setSpeeds(70, -80);
  delay(3000);
  motorsRobot.setSpeeds(-100, -100);
  delay(4000);

  //turning right and moving forward
  motorsRobot.setSpeeds(-90, 100);
  delay(2000);
  motorsRobot.setSpeeds(-100, -100);
  delay(2000);

  //move backwards, turn right & move forward
  motorsRobot.setSpeeds(100, 100);
  delay(3000);

  motorsRobot.setSpeeds(-90, 100);
  delay(2000);

  motorsRobot.setSpeeds(-100, -100);
  delay(4000);

  //turn left and move forwards
  motorsRobot.setSpeeds(90, -90);
  delay(2000);
  motorsRobot.setSpeeds(-100, -100);
  delay(9000);

  //turn left and move forwards
  motorsRobot.setSpeeds(70, -80);
  delay(3000);
  motorsRobot.setSpeeds(-100, -100);
  delay(2000);

  //move backwards, turn left and move forwards to exit maze
  motorsRobot.setSpeeds(100, 100);
  delay(3000);
  motorsRobot.setSpeeds(70, -80);
  delay(1000);
  motorsRobot.setSpeeds(-100, -100);
  delay(10000);
  
  stop_speed();
}
