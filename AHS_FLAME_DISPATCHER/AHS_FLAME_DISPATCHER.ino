#include <RF24.h>

#include <AHSHeaders.h>

const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

int sensorReading = 0;
int range = 0;

const uint64_t pipe = EVENT_FIRE;
bool writeSuccess = false;


void setup(void)
{
  Serial.begin(9600);
  
  radio.begin();

  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setPayloadSize(8);
  
  radio.openWritingPipe(pipe);

  

  msg[0] = 'I';
  msg[1] = EVENT_FIRE;
  msg[2] = 0x00;
  msg[3] = 0x00;
  msg[4] = 0x00;
  msg[5] = 0x00;
  msg[6] = 0x00;
  msg[7] = 0x00;


}

void loop(void)
{
  sensorReading = analogRead(A0);
  range = map(sensorReading, sensorMin, sensorMax, 0, 3);


   // range value:
  switch (range) 
  {
  case 0:    // A fire closer than 1.5 feet away.
    Serial.println("** Close Fire **");
    msg[2] = 0x01;
    break;
  case 1:    // A fire between 1-3 feet away.
    Serial.println("** Distant Fire **");
    msg[2] = 0x01;
    break;
  case 2:    // No fire detected.
    Serial.println("No Fire");
    msg[2] = 0x00;
    break;
  }

  
  /*msg[3] = (gas_value_int >> 24) & 0x000000FF;
  msg[4] = (gas_value_int >> 16) & 0x000000FF;
  msg[5] = (gas_value_int >> 8) & 0x000000FF;
  msg[6] = (gas_value_int) & 0x000000FF;*/


  writeSuccess = radio.write(msg, 8);

  if (writeSuccess)
    Serial.println("Data sent.");
  else
    Serial.println("Data could not be sent.");


  delay(100);


}
