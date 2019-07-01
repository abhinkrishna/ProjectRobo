void handStart() {
  Serial.println("HandStarted");
  handUp();
  handTata(2);
  delay(750);
  handDown();
//  delay(2000);
//  servoHand.write(handAngle);
}
int i=0;
void handUp() {
  Serial.println("HandsUp");
  for(i=0;i<40;i++) {
   servoHand.write(i);
   delay(10);
  }
}
void handDown() {
  Serial.println("HandsDown");
  for(i=40;i>0;i--) {
   servoHand.write(i);
   delay(10);
  }
  delay(2000);
}
void handTata(int times) {
  Serial.println("Hand Tata");
  for(int i=0;i<times;i++) {
    servoTata.write(135);
    delay(500);
    servoTata.write(45);
    delay(500);
    servoTata.write(90);
  }
}
