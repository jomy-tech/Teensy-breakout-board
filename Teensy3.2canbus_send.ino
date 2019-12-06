#include <FlexCAN.h>
static CAN_message_t txmsg;
unsigned int txdata;
uint8_t bytes[sizeof(float)];
int led = 13;

void setup()
{
  Can0.begin(500000); //CAN speed is 500kbps
  delay(1000);
  pinMode(led, OUTPUT);
  Serial.println(F("CAN Bus Tx test ver.3"));
  delay(1000);
}

void loop()
{
  digitalWrite(led, HIGH);

  txdata = 80;                             //Get first data from somewhere
  memcpy(bytes, &txdata, sizeof (txdata)); //Convert txdata into 4 bytes
  Serial.print(txdata);
  Serial.print(" ");
  txmsg.len = 8;
  txmsg.id = 0x700;
  txmsg.buf[0] = bytes[0];
  txmsg.buf[1] = bytes[1];
  txmsg.buf[2] = bytes[2];
  txmsg.buf[3] = bytes[3];
  txmsg.buf[4] = 0;
  txmsg.buf[5] = 0;
  txmsg.buf[6] = 0;
  txmsg.buf[7] = 0;
  Can0.write(txmsg);                       //Transmit first CAN data

  txdata = 90;                             //Get next data from somewhere
  memcpy(bytes, &txdata, sizeof (txdata)); //Convert txdata into 4 bytes
  Serial.print(txdata);
  txmsg.len = 8;
  txmsg.id = 0x701;
  txmsg.buf[0] = bytes[0];
  txmsg.buf[1] = bytes[1];
  txmsg.buf[2] = bytes[2];
  txmsg.buf[3] = bytes[3];
  txmsg.buf[4] = 0;
  txmsg.buf[5] = 0;
  txmsg.buf[6] = 0;
  txmsg.buf[7] = 0;
  Can0.write(txmsg);                       //Transmit next CAN data
  
  Serial.println(" ");
  digitalWrite(led, LOW);
  delay(1000);                             //Send CAN data every 1 sec

}
