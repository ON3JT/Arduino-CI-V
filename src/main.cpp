#include <Arduino.h>
#include <AltSoftSerial.h>

// pin for PTT, for test purposes use the builtin LED on port 13, change to your needs
//#define PTT      (2)
#define PTT (13)


int CIV_SPEED = 9600;
int RS232_SPEED = 9600;

AltSoftSerial CAT;     
uint8_t read_buffer[8]; //Read buffer
uint8_t counter = 0;


void TX(bool Active)
{
  if (Active)
  {
    digitalWrite(PTT, HIGH);
  }
  else if (!Active)
  {
    digitalWrite(PTT, LOW);
  }
}

void setup()
{
  pinMode(PTT, OUTPUT);
  digitalWrite(PTT, LOW);
  CAT.begin(CIV_SPEED);
  Serial.begin(RS232_SPEED);
}

void loop()
{
  char sd_host;
  char sd_cat;

  if (Serial.available())
  {
    sd_host = Serial.read();
    if (byte(sd_host) == 0xFD) // if this is the end of the serial sentence, processing starts here
    {
      read_buffer[counter] = 0xFD; // Add this to have a complete sentence
      if (read_buffer[0] == 0xFE && read_buffer[1] == 0XFE && read_buffer[3] == 0XE0)
      {
        if (read_buffer[4] == 0X1C && read_buffer[5] == 0x00)
        {
          if (read_buffer[6] == 0x01)
          {
            TX(1);
          }
          else if (read_buffer[6] == 0x00)
          {
            TX(0);
          }
        }
      }
      counter = 0;
    }
    else
    {
      // Keep filling the buffer
      if (byte(sd_host) != 0xFF) // skip 0xFF in the buffer
      {
        read_buffer[counter] = sd_host;
        counter++;
      }
    }
    // Forward all the received data from the host to the transceiver
    CAT.print(sd_host);
  }

  // Forward all the received data from the transceiver to the host via de Arduino USB port.
  if (CAT.available())
  {
    sd_cat = CAT.read();
    Serial.print(sd_cat);
  }
}