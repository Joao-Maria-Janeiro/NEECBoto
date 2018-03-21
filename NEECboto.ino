#include <Servo.h>        //add Servo Motor library            
#include <NewPing.h>      //add Ultrasonic sensor library

#define TRIG_PIN 7 
#define ECHO_PIN 6 
#define MAX_DISTANCE 300 // sets maximum useable sensor measuring distance to 300cm
#define COLL_DIST 30 // sets distance at which robot stops and reverses to 30cm
#define TURN_DIST COLL_DIST+20 // sets distance at which robot veers away from object

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // sets up sensor library to use the correct pins to measure distance.

Servo left_servo;  // create servo object to control servos
Servo right_servo;
Servo reader;

int leftDistance, rightDistance; //distances on either side
int curDist = 0;
String motorSet = "";
int speedSet = 0;

//-------------------------------------------- SETUP LOOP ----------------------------------------------------------------------------
void setup() {
  left_servo.attach(11); 
  right_servo.attach(10);
  reader.attach(9);
  reader.write(90);
  delay(1000); // delay for one seconds
 }
//------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
void loop() {
  reader.write(90);  // move eyes forward
  delay(90);
  curDist = readPing();   // read distance
  if (curDist < COLL_DIST) {changePath();}  // if forward is blocked change direction
  moveForward();  // move forward
  delay(500);
 }
//-----------------------------------------------------------//Deciding wich side to go//------------------------------------------------------------------------

void changePath() {
  moveStop();   // stop forward movement
    reader.write(36);  // check distance to the right
    delay(500);
    rightDistance = readPing(); //set right distance
    delay(500);
    reader.write(144);  // check distace to the left
    delay(700);
    leftDistance = readPing(); //set left distance
    delay(500);
    reader.write(90); //return to center
    delay(100);
    compareDistance();
  }

  
void compareDistance()   // find the longest distance
{
  if (leftDistance>rightDistance) //if left is less obstructed 
  {
    turnLeft();
  }
  else if (rightDistance>leftDistance) //if right is less obstructed
  {
    turnRight();
  }
   else //if they are equally obstructed
  {
    turnAround();
  }
}


//--------------------------------------------//Reading the distance//-------------------------------------------------------------------------------------

int readPing() { // read the ultrasonic sensor distance
  delay(70);   
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}
//------------------------------------------------//movement---------------------------------------------------------------------------------
void moveStop() { right_servo.write(90); left_servo.write(90);}  // stop the motors.
//-------------------------------------------------------------------------------------------------------------------------------------
void moveForward() {
  right_servo.write(180);
  left_servo.write(180);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void moveBackward() {
    right_servo.write(0);
    left_servo.write(0);
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnRight() {
  left_servo.write(140);
  right_servo.write(0);
  delay(1500); // run motors this way for 1500        

   right_servo.write(180); //Set motors back to forward
   left_servo.write(180); 
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnLeft() {
  left_servo.write(0);
  right_servo.write(140);
  delay(1500); // run motors this way for 1500     
  right_servo.write(180); //Set motors back to forward
  left_servo.write(180); 
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnAround() {
  left_servo.write(180);
  right_servo.write(0);
  delay(1700); // run motors this way for 1700        

  right_servo.write(180); //Set motors back to forward
  left_servo.write(180); 
}  
