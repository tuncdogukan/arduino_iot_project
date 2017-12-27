#include <RF24.h>


int msg[1];
RF24 radio(9, 10);
int cnt = 0;
bool done;
const int buzzerPin = 2;

const uint64_t pipe = 0xE8E8F0F0E1LL;


void setup()
{
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);


  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1, pipe);

  radio.startListening();

}

void loop()
{
  if (radio.available())
  {
    radio.read(msg, 2);

    if (done)
    {
      Serial.print(msg[0]);

      tone(buzzerPin, 1000, 100);

      cnt++;
      Serial.print(" - Message No: ");
      Serial.print(cnt);
      Serial.println("");
    }
    else
    {
      Serial.println("No data...");
    }
  }
  else
  {
    Serial.println("Radio is not available...");
  }

  delay(100);
}

