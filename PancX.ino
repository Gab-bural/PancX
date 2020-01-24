#include <SoftwareSerial.h>   //Software Serial Port
#include <Servo.h>
#include <TimedAction.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PIN_NTC 0

#define RxD         3
#define TxD         4

#define PINLED      7

#define LEDON()     digitalWrite(PINLED, HIGH)
#define LEDOFF()    digitalWrite(PINLED, LOW)

#define DEBUG_ENABLED  1

SoftwareSerial Bluetooth(RxD, TxD);

Servo serv1;

int PINBUTTON;

double R0 = 1000;
double A = (3.9083*pow(10, -3));
double B = (-5.775*pow(10, -7));
double C = (-4.183*pow(10, -12));



void setup()
{
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(PINLED, OUTPUT);
  LEDOFF();
  
  PINBUTTON = 8;

  serv1.attach(4);
  pinMode(PINBUTTON, INPUT);
  serv1.write(90);
  
  setupBlueToothConnection();
}

void loop()
{
  boolean etatBouton = digitalRead(PINBUTTON);
  int posServo = serv1.read();
  
  if(etatBouton = 1)
  {
    useServo(posServo);
  }
  
  char recvChar;
  if (Bluetooth.available())
  { //check if there's any data sent from the remote bluetooth shield
    recvChar = Bluetooth.read();


    //Pour obtenir temperature de la thermistance:
    //double valeurAnalog = analogRead(PIN_NTC);
    //temp = Thermister(valeurAanalog);
    
    Serial.print(recvChar);
    if (recvChar == '1')
    {
      LEDON();
      Bluetooth.write("Led ON");
    }
    else if (recvChar == '0')
    {
      LEDOFF();
    }
  }
}

/**
TimedAction numberThread = TimedAction(<Delai>,ouvrirValve);
TimedAction textThread = TimedAction(<Delai>,fermerValve);
**/

double Thermister(float RawADC) {
  float R = R0/((1023/RawADC)-1);
  //1/T = A+Bln(R)+C(ln(R))^3
  float Rbuffer = A + B * log(R) + C*pow((log(R)), 3); // result = 1/T
  float T = 1/Rbuffer;
  return T; // Return temperature
}

void useServo(int pos)
{
  if(pos==10)
  {
    serv1.write(90);
  }
  if(pos == 90)
  {
    serv1.write(10);
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



  Bluetooth.begin(9600);

  Bluetooth.print("AT");
  delay(400);

  Bluetooth.print("AT+DEFAULT");             // Restore all setup value to factory setup
  delay(2000);

  Bluetooth.print("AT+NAMESeeedBTSlave");    // set the bluetooth name as "SeeedBTSlave" ,the length of bluetooth name must less than 12 characters.
  delay(400);

  Bluetooth.print("AT+PIN0000");             // set the pair code to connect
  delay(400);

  Bluetooth.print("AT+AUTH1");             //
  delay(400);

  Bluetooth.print("AT+NOTI1");             //
  delay(400);


  Bluetooth.flush();

}
