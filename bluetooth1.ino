


#include <SoftwareSerial.h>   //Software Serial Port

#define RxD         3
#define TxD         4  

#define PINLED      7

#define LEDON()     digitalWrite(PINLED, HIGH)
#define LEDOFF()    digitalWrite(PINLED, LOW)

#define DEBUG_ENABLED  1

SoftwareSerial blueToothSerial(RxD, TxD);

void setup()
{
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(PINLED, OUTPUT);
  LEDOFF();

  setupBlueToothConnection();
}

void loop()
{
  char recvChar;


    if (blueToothSerial.available())
    { //check if there's any data sent from the remote bluetooth shield
      recvChar = blueToothSerial.read();
      Serial.print(recvChar);

      if (recvChar == '1')
      {
        LEDON();
      }
      else if (recvChar == '0')
      {
        LEDOFF();
      }
    }

}




/***************************************************************************
   Function Name: setupBlueToothConnection
   Description:  initilizing bluetooth connction
   Parameters:
   Return:
***************************************************************************/
void setupBlueToothConnection()
{



  blueToothSerial.begin(9600);

  blueToothSerial.print("AT");
  delay(400);

  blueToothSerial.print("AT+DEFAULT");             // Restore all setup value to factory setup
  delay(2000);

  blueToothSerial.print("AT+NAMESeeedBTSlave");    // set the bluetooth name as "SeeedBTSlave" ,the length of bluetooth name must less than 12 characters.
  delay(400);

  blueToothSerial.print("AT+PIN0000");             // set the pair code to connect
  delay(400);

  blueToothSerial.print("AT+AUTH1");             //
  delay(400);

  blueToothSerial.flush();

}
