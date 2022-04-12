/*
  Titre      : Servo Moteur
  Auteur     : Duvalier Tsagmo
  Date       : 12/04/2022
  Description: controle du servo moteur avec un clavier matricielle
  Version    : 0.0.1
*/


#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include "WIFI_NINA_Connector.h"
#include "MQTTConnector.h"

Servo moteur1;
int Angle = 0;
const int PIN_SERVO = 9;
void receiveEvent(int byte);

char boutton;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);

  wifiConnect();                  //Branchement au réseau WIFI
  MQTTConnect();                  //Branchement au broker MQTT

    Wire.begin(7);      // Démarrage du périphérique en tant que périphérique.
    Wire.onReceive(receiveEvent);
   moteur1.attach(PIN_SERVO);
}

void loop() {
  // put your main code here, to run repeatedly:
  	moteur1.write(Angle);     

}

void receiveEvent(int byte){
	boutton = Wire.read();    // read one character from the I2C

	Serial.print("\nValeur obtenue est : ");
	Serial.println(boutton);
	Serial.print("Angle : ");
	Serial.println(Angle);
	switch (boutton)
	{
	case 'A':
		Angle = 180;
		break;
	case 'B':
			if (Angle == 180)
				Angle = 180;
			else
				Angle = Angle + 1;
		break;
	case 'C':
		if (Angle == 0)
				Angle = 0;
			else
				Angle = Angle - 1;
		break;
	case 'D':
		Angle = 0;
		break;
	
	default:
		break;
	}
    appendPayload("Angle", Angle);
    sendPayload();
}