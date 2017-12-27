#include <RF24_config.h>
#include  <SPI.h>
#include <RF24.h>



int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider

int msg[1];
RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
bool writeSuccess = false;


void setup(void)
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);

  radio.setPALevel(RF24_PA_LOW);

  msg[0] = 1000;


}

void loop(void)
{
  photocellReading = analogRead(photocellPin);

  Serial.println(photocellReading);

  if (photocellReading > 500)
  {
    msg[0] = photocellReading;
    writeSuccess = radio.write(msg, 4);
    if (writeSuccess)
    {
      Serial.println("Data sent.");
    }



  }

  delay(100);


}
