#include <FlexCAN.h>
static CAN_message_t msg, rxmsg;
IntervalTimer TX_timer;
String CANStr("");
int led = 13;

uint8_t no_data1 = 0;   // No data counter for Data 1
uint8_t no_data2 = 0;   // No data counter for Data 2

IntervalTimer data_timer;
unsigned char data[4];

void setup()
{
  Can0.begin(500000); //CAN speed is 500kbps
  delay(1000);
  pinMode(led, OUTPUT);
  Serial.println(F("CAN Bus Rx test ver.3"));
  delay(1000);

  msg.rtr = 0 ;
  data_timer.begin(data_count, 1000000);   // Start no data interrupt counter
}

/* From Timer Interrupt */
void data_count(void)
{
  no_data1++;
  no_data2++;
}

void loop()
{

  while (Can0.read(rxmsg))
  {
    String CANStr("");
    for (int i = 0; i < 8; i++) {

      CANStr += String(rxmsg.buf[i], HEX);
      CANStr += (" ") ;
    }

    if (rxmsg.id == 0x700)
    {
      digitalWrite(led, HIGH);
      data[0] = rxmsg.buf[0];
      data[1] = rxmsg.buf[1];
      data[2] = rxmsg.buf[2];
      data[3] = rxmsg.buf[3];

      Serial.print(rxmsg.id, HEX);
      Serial.print(' ');
      Serial.print(rxmsg.len, HEX);
      Serial.print(' ');
      Serial.print(CANStr);

      Serial.print("Data 1 : ");
      Serial.println(data[0]);
      no_data1 = 0;
    }

    if (rxmsg.id == 0x701)
    {
      digitalWrite(led, HIGH);
      data[0] = rxmsg.buf[0];
      data[1] = rxmsg.buf[1];
      data[2] = rxmsg.buf[2];
      data[3] = rxmsg.buf[3];

      Serial.print(rxmsg.id, HEX);
      Serial.print(' ');
      Serial.print(rxmsg.len, HEX);
      Serial.print(' ');
      Serial.print(CANStr);

      Serial.print("Data 2 : ");
      Serial.println(data[0]);
      tone (5, data[0]);
      no_data2 = 0;
    }
  }

  digitalWrite(led, LOW);

  if (no_data1 > 2) //Check data still coming in within 2 second
  {
    Serial.println("------");
    no_data1 = 3;  // Prevent counter rollover
  }

  if (no_data2 > 2) //Check data still coming in within 2 second
  {
    Serial.println("------");
    no_data2 = 3;  // Prevent counter rollover
  }
}
