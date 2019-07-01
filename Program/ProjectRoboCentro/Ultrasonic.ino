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
