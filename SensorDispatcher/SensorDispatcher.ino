#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9, 10);

bool done = false;

const int payload_size = 8;
unsigned char* sent_message;
bool ok = 0;

const uint64_t pipes[6] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL , 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL, 0xF0F0F0F0A5LL, 0xF0F0F0F006LL};

void setup(void)
{
  sent_message = new unsigned char[payload_size];
  memset(sent_message, 0, payload_size);

  Serial.begin(57600);
  printf_begin();
  radio.begin();

  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);

  radio.setPayloadSize(payload_size);

  radio.openWritingPipe(pipes[0]);

  radio.printDetails();

  sent_message[0] = 0x01;
  sent_message[1] = 0x01;
  sent_message[2] = 0x01;
  sent_message[3] = 0x01;
  sent_message[4] = 0x01;
  sent_message[5] = 0x01;
  sent_message[6] = 0x01;
  sent_message[7] = 0x01;
}

void loop(void)
{
  
  ok = radio.write(sent_message, payload_size);

  if (ok)
    printf("SENT SUCCESSFULLY.\n\r");
  else
    printf("FAILED TO SEND.\n\r");

  delay(500);
}
