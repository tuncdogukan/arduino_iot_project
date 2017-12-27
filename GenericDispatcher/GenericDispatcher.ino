#include <RF24.h>

float sensor = A0;
float gas_value;

uint8_t msg[8];
RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
bool writeSuccess = false;


void setup(void)
{
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  radio.begin();

  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.setPayloadSize(8);
  
  radio.openWritingPipe(pipe);

  

  msg[0] = 'I';
  msg[1] = 'E';
  msg[2] = 0x01;
  msg[3] = 0x00;
  msg[4] = 0x00;
  msg[5] = 0x00;
  msg[6] = 0x00;
  msg[7] = 0x00;


}

void loop(void)
{
  gas_value = analogRead(sensor);
  Serial.println(gas_value);

  int gas_value_int = (int)gas_value;

  msg[3] = (gas_value_int >> 24) & 0x000000FF;
  msg[4] = (gas_value_int >> 16) & 0x000000FF;
  msg[5] = (gas_value_int >> 8) & 0x000000FF;
  msg[6] = (gas_value_int) & 0x000000FF;


  writeSuccess = radio.write(msg, 8);

  if (writeSuccess)
    Serial.println("Data sent.");
  else
    Serial.println("Data could not be sent.");


  delay(100);


}
