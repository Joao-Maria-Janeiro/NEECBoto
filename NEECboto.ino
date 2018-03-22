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

//Global variables
int leftDistance, rightDistance; //distances on either side
int curDist = 0;
int angle;
int up;

//-------------------------------------------- SETUP LOOP ----------------------------------------------------------------------------
void setup() {
  left_servo.attach(11); 
  right_servo.attach(10);
  reader.attach(9);
  reader.write(90);
  delay(100); // delay for one seconds
  angle=90;
  up=1;
 }
//------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
void loop() {

  if(angle<130 and up==1){
    angle=angle+10;
  } else if (angle>50 and up==0){
    angle=angle-10;
  } else if (angle>=125){
    up=0;
  } else  if (angle<=55) {
    up=1;
  }
  
  reader.write(angle);  // move eyes forward
  
  if (readPing() < COLL_DIST) {
    reader.write(90);
    changePath();
  }  // if forward is blocked change direction
  else {
    moveForward();  // move forward
  }
  //delay(500);
 }
//-----------------------------------------------------------//Deciding which side to go//------------------------------------------------------------------------

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
  if (leftDistance>rightDistance  and leftDistance>30) //if left is less obstructed 
  {
    turnLeft();
  }
  else if (rightDistance>leftDistance and rightDistance>30) //if right is less obstructed
  {
    turnRight();
  }
   else  if (leftDistance<30 and rightDistance<30 and leftDistance>15 and rightDistance>15) //if they are equally obstructed
  {
    
    turnAround();
  } else {

    moveBackward();
    delay(500);
    changePath();
    
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
  right_servo.write(45);
  left_servo.write(135);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void moveBackward() {
    right_servo.write(135);
    left_servo.write(45);
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnRight() {
  left_servo.write(140);
  right_servo.write(140);
  delay(150); // run motors this way for 1500        

   right_servo.write(0); //Set motors back to forward
   left_servo.write(180); 
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnLeft() {
  left_servo.write(40);
  right_servo.write(40);
  delay(150); // run motors this way for 1500     
  right_servo.write(0); //Set motors back to forward
  left_servo.write(180); 
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnAround() {
  left_servo.write(140);
  right_servo.write(140);
  delay(600); // run motors this way for 1700        

  right_servo.write(0); //Set motors back to forward
  left_servo.write(180); 
}  
//--------------------------------------------------------------------------------------------------------------------------------------
//void 
