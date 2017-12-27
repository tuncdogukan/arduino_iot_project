#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9, 10);

const int led_1 = 4;
const int led_2 = 7;
const int led_3 = 6;


bool done = false;

const int payload_size = 8;
unsigned char* received_message;

const uint64_t pipes[6] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL , 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL, 0xF0F0F0F0A5LL, 0xF0F0F0F006LL};

void setup(void)
{
  received_message = new unsigned char[payload_size];
  memset(received_message, 0, payload_size);

  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);

  Serial.begin(57600);
  printf_begin();
  radio.begin();

  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);

  radio.setPayloadSize(payload_size);


  radio.openReadingPipe(1, pipes[0]);

  radio.startListening();

  radio.printDetails();
}

void loop(void)
{
  if ( radio.available())
  {
    done = radio.read(received_message, payload_size );

    printf("Received the message.\n\r");

    if (received_message[0] == 0x01)
      digitalWrite(led_1, HIGH);
    else if (received_message[0] == 0x02)
      digitalWrite(led_2, HIGH);
    else if (received_message[0] == 0x03)
      digitalWrite(led_3, HIGH);



    delay(1000);
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
    delay(1000);
  }
}
