#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <Adafruit_SSD1306.h>


#include "RF24.h"


uint8_t msg[8];
RF24 radio(9, 10);
int cnt = 0;
bool done;

const uint64_t pipe = 0xE8E8F0F0E1LL;



#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


void setup()
{
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_1MBPS);
  radio.setPayloadSize(8);
  radio.openReadingPipe(1, pipe);


  radio.startListening();


  radio.printDetails();


  writeSingleLine("Started reading...");

}

void loop()
{      

  if ( radio.available() )
    {
      bool done = false;
      
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &msg, 8 );
        
        delay(20);
      }

      writeSingleLine("MESSAGE RECEIVED.");
      
 
      if (msg[2] == 0x01)
      {
        int payload = 0;

        payload |= ((((int)msg[3])<<24) & 0xFF000000);
        payload |= ((((int)msg[4])<<16) & 0x00FF0000);
        payload |= ((((int)msg[5])<<8) & 0x0000FF00);
        payload |= (((int)msg[6]) & 0x000000FF);
        
        cnt++;
        Serial.print(" - Message No: ");
        Serial.print(cnt);
        Serial.print(" - Payload:");
        Serial.print(payload);
        Serial.println("");

        
        display.print("Payload: ");
        display.println(payload);
        display.print("Msg Count: ");
        display.print(cnt);
        display.display();
      
      }


      delay(100);
    }
}



void writeSingleMessage(char* msg)
{
  display.print(msg);
  display.display();
}

void writeSingleLine(char* msg)
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(msg);
  display.display();
}




