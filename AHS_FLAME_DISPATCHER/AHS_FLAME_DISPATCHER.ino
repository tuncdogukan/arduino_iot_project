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
  radio.begin();

  SET_PA_LEVEL();
  SET_DATA_RATE();
  SET_PAYLOAD_SIZE();

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


  if (range == 0 || range == 1)
  {
    radio.write(msg, 8);
  }


  delay(100);


}
