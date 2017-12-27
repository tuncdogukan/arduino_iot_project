int tempPin = A0;
int val;
void setup() {
  
  Serial.begin(9600);

}

void loop() {

   val = analogRead(tempPin);
  float cel = val * 0.48828125;

  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print(" C");
  Serial.println();
  delay(1000);

}
