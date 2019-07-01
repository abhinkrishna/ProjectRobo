
//AutoRobo version v1.7 [ CentroMall,Kodungallur ] : HARK SOLUTIONS
//WARNING
//Basic movements like FRONT,BACK,RIGHT,LEFT are not included in this Program. Check versions 1.2 and 1.5 for that codes
//SpecialProgram to Project Robo for Exhibition @ CentroMall,Kodungallur
//This Robot will check the distance and if distance is less than a particular value 
// robot will give a hand start AKA tata
// and head movement, robot looks right and left
//HeaderFIles
#include <Servo.h>
//Servos
Servo myservo;
Servo servoHand; //Shoulder
Servo servoTata; // palm
//UltraSonic 1 - us1
int us1_echo=7;
int us1_trigr=6;
//Servos
int myservo_pin=5;
int servoHand_pin=4;
int servoTata_pin=3;
//ProgramVariables
int distance=0;
int headAngle=100;
int tataAngle=50;
int handAngle=110;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(us1_trigr, OUTPUT);
  pinMode(us1_echo, INPUT);
  myservo.attach(myservo_pin);
  servoHand.attach(servoHand_pin);
  servoTata.attach(servoTata_pin);  
}
void loop() {
  // put your main code here, to run repeatedly:
//  myservo.write(90);
//  servoHand.write(handAngle);
//  servoTata.write(tataAngle);
//  us1Update();
//  if(distance<50) {
//    Serial.println("Something Found");
//    handStart(2);
//    headMove(7); //Parameter is timedelay or speed of
//  }

  myservo.write(90);
  servoHand.write(0);
  servoTata.write(90);
  handStart(); 
  headMove(15); //Parameter is timedelay or speed of

}
