//WARNING MUST READ
//AutoRobo version v1.5 : HARK SOLUTIONS
//Warning : pin 0 and 1 is reserved for Bluetooth.
//Bluetooth code added in 4/4/2018 6:40PM, Not tested because of lack of arduino.
//So if any unsolvable problem occurs.. please replace this code 
/*
void loop() {
    autoMode();
}
// loop funtion only need autoMode() to work like this
// Checks for any obstacles in front
// If any obstacle is found in less than 50cm 
// Look right and scan distance
// Look left and scan distance
// compare both distances and find the largest distance
// Turn the robot to the side with long distance and again 
// Move forward and check for any obstacles if found.. Repeat :D :D 
*/
//Hand Code Added on 7/4/2018 Tested and working. All bug fixed.
//HeaderFIles
#include <Servo.h>
Servo myservo;
Servo servoHand;
Servo servoTata;
//pin declaration
//LED
int led=13;
//Motor
int t1=11;
int t2=10;
int t3=9;
int t4=8;
//UltraSonic 1 - us1
int us1_echo=7;
int us1_trigr=6;
//Servos
int myservo_pin=5;
int servoHand_pin=4;
int servoTata_pin=3;

//program variables
int distance=0;
int distanceRight=0;
int distanceLeft=0;
char Direction='a';
boolean AutoMode=false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(t4,OUTPUT);
  pinMode(t3,OUTPUT);
  pinMode(t2,OUTPUT);
  pinMode(t1,OUTPUT);
  pinMode(us1_trigr, OUTPUT);
  pinMode(us1_echo, INPUT);
  pinMode(led,OUTPUT);
  myservo.attach(myservo_pin);
  servoHand.attach(servoHand_pin);
  servoTata.attach(servoTata_pin);
}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(90);
  servoHand.write(100);
  delay(10);
  servoTata.write(90);
  if(Serial.available()>0) {
    btControl();
  }
  else {
    AutoMode=true;
    autoMode();
  }
}
void autoMode() {
    myservo.write(90);
    us1Update();
    delay(100);
    if(distance>50) {
      digitalWrite(led,HIGH);
      front();
    }
    else {
      digitalWrite(led,LOW);
      Stop();
      handStart(2);
      delay(1000);
      checkSides();
      selectPath();
    }
}
void handStart(int times) {
  handUp();
  handTata(times);
  delay(2000);
  servoHand.write(100);
}
void handUp() {
  servoHand.write(180);
  delay(2000);
}
void handTata(int times) {
  for(int i=0;i<times;i++) {
    servoTata.write(45);
    delay(500);
    servoTata.write(135);
    delay(500);
    servoTata.write(90);
  }
  for(int i=180;i>=100;i--) {
    servoHand.write(i);
    delay(10);
  }
}
void btControl() {
    if(AutoMode=false) {
        switch(Serial.read()) {
          case 'A'  :  front();
                       break;
          case 'B'  :  back(0);
                       break;
          case 'C'  : left(0);
                      break;
          case 'D' :  right(0);
                       break;
          case 'E' :  Stop();
                       break;
          case 'F' :  handStart(3);
                      break;
          case 'G' :  AutoMode=true;
                      break;
        }
    }
    else {
          autoMode();
    }
}

void selectPath() {
  if(distanceLeft>distanceRight) {
    Serial.println("Direction : LEFT SELECTED");
    left(7500);
  }
  else {
    Serial.println("Direction : RIGHT SELECTED");
    right(7500);
  }
}
void lookRight() {
  myservo.write(0);
 delay(2000);
  us1UpdateRight();
  delay(50);
}
void lookLeft() {
  myservo.write(180);
  delay(2000);
  us1UpdateLeft();
  delay(50);
}
void checkSides() {
  lookRight();
  delay(2000);
  lookLeft();
}

void us1Update() {
  delay(100);
  digitalWrite(us1_trigr, LOW);
  delayMicroseconds(2);
  digitalWrite(us1_trigr, HIGH);
  delayMicroseconds(10);
  digitalWrite(us1_trigr, LOW);
  long duration = pulseIn(us1_echo, HIGH);
  distance = (duration * 0.034 / 2);
  Serial.print("Distance : ");
  Serial.println(distance);
  delay(200);
}
void us1UpdateLeft() {
  digitalWrite(us1_trigr, LOW);
  delayMicroseconds(2);
  digitalWrite(us1_trigr, HIGH);
  delayMicroseconds(10);
  digitalWrite(us1_trigr, LOW);
  long durationLeft = pulseIn(us1_echo, HIGH);
  distanceLeft = (durationLeft * 0.034 / 2);
  Serial.print("Distance Left : ");
  Serial.println(distanceLeft);
  delay(200);
}
void us1UpdateRight() {
  digitalWrite(us1_trigr, LOW);
  delayMicroseconds(2);
  digitalWrite(us1_trigr, HIGH);
  delayMicroseconds(10);
  digitalWrite(us1_trigr, LOW);
  long durationRight = pulseIn(us1_echo, HIGH);
  distanceRight = (durationRight * 0.034 / 2);
  Serial.print("Distance Right : ");
  Serial.println(distanceRight);
  delay(200);
}
void front() {
  Serial.println("FRONT");
  digitalWrite(t4,LOW);
  digitalWrite(t3,HIGH);
  digitalWrite(t2,LOW); //FRONT
  digitalWrite(t1,HIGH);
}
void back(int time) {
  if(time!=0) { 
    Serial.println("BACK");
    digitalWrite(t4,HIGH);
    digitalWrite(t3,LOW);
    digitalWrite(t2,HIGH);   //BACK
    digitalWrite(t1,LOW);
    delay(time);
  }
  else {
    Serial.println("BACK_NoTimeLimit");
    digitalWrite(t4,HIGH);
    digitalWrite(t3,LOW);
    digitalWrite(t2,HIGH);   //BACK
    digitalWrite(t1,LOW);
  }
}
void left(int time) {
  if(time!=0) { 
    Serial.println("LEFT");
    digitalWrite(t4,HIGH);
    digitalWrite(t3,LOW);
    digitalWrite(t2,LOW);  //LEFT
    digitalWrite(t1,HIGH);
    delay(time);
  }
  else {
    Serial.println("Left_NoTimeLimit");
    digitalWrite(t4,HIGH);
    digitalWrite(t3,LOW);
    digitalWrite(t2,LOW);  //LEFT
    digitalWrite(t1,HIGH);
  }
}
void right(int time) {
  if(time!=0) {
    Serial.println("Right");
    digitalWrite(t4,LOW);
    digitalWrite(t3,HIGH);
    digitalWrite(t2,HIGH);  // Right
    digitalWrite(t1,LOW);
    delay(time);
  }
  else {
    Serial.println("Right_NoTimeLimit");
    digitalWrite(t4,LOW);
    digitalWrite(t3,HIGH);
    digitalWrite(t2,HIGH);  // RIGHT
    digitalWrite(t1,LOW);
  }
}
void Stop() {
  Serial.println("STOP");
  digitalWrite(t4,LOW);
  digitalWrite(t3,LOW);
  digitalWrite(t2,LOW);  // STOP
  digitalWrite(t1,LOW);
}
