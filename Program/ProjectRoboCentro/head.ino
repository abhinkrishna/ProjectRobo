void headMove(int time) {
  for(int i=90;i<=145;i++) {
    myservo.write(i);
    delay(time);
  }
  for(int i=145;i>=90;i--) {
    myservo.write(i);
    delay(time);
  }
  delay(100);
  for(int i=90;i>=35;i--) {
    myservo.write(i);
    delay(time);
  }
  for(int i=35;i<=90;i++) {
    myservo.write(i);
    delay(time);
  }
}

