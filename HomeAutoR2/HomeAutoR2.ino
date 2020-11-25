#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
RF24 radio(10, 9);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)


const char FanOn = 'F';
const char FanOff = 'f';
const char BulbOn = 'B';
const char BulbOff = 'b';
const char TvOn = 'T';
const char TvOff = 't';

int fan = 02;
int bulb = 03;
int tv = 05;

int csn = 9;
int ce = 10;

void setup() {
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
  Serial.begin(9600);

  //pinMode(13,OUTPUT);

  pinMode(fan,OUTPUT);
  pinMode(bulb,OUTPUT);
  pinMode(tv,OUTPUT);

  //digitalWrite(13,LOW);

}

void loop() {
  network.update();
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    char ch;
    Serial.println(ch);
    network.read(header, &ch, sizeof(ch)); // Read the incoming data

    //digitalWrite(13,HIGH);
    switch(ch)
    {
      case FanOn :
      digitalWrite(fan,HIGH);
      break;
      case BulbOn :
      digitalWrite(bulb,HIGH);
      break;
      case TvOn :
      digitalWrite(tv,HIGH);
      break;
      case FanOff :
      digitalWrite(fan,LOW);
      break;
      case BulbOff :
      digitalWrite(bulb,LOW);
      break;
      case TvOff :
      digitalWrite(tv,LOW);
      break;
    }
  }
}
