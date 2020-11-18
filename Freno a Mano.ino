/*

███████╗░█████╗░    ░██████╗██╗███╗░░░███╗    ██████╗░░█████╗░░█████╗░██╗███╗░░██╗░██████╗░
██╔════╝██╔══██╗    ██╔════╝██║████╗░████║    ██╔══██╗██╔══██╗██╔══██╗██║████╗░██║██╔════╝░
█████╗░░██║░░╚═╝    ╚█████╗░██║██╔████╔██║    ██████╔╝███████║██║░░╚═╝██║██╔██╗██║██║░░██╗░
██╔══╝░░██║░░██╗    ░╚═══██╗██║██║╚██╔╝██║    ██╔══██╗██╔══██║██║░░██╗██║██║╚████║██║░░╚██╗
███████╗╚█████╔╝    ██████╔╝██║██║░╚═╝░██║    ██║░░██║██║░░██║╚█████╔╝██║██║░╚███║╚██████╔╝
╚══════╝░╚════╝░    ╚═════╝░╚═╝╚═╝░░░░░╚═╝    ╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚═╝╚═╝░░╚══╝░╚═════╝░




██╗░░██╗░█████╗░███╗░░██╗██████╗░██████╗░██████╗░░█████╗░██╗░░██╗███████╗
██║░░██║██╔══██╗████╗░██║██╔══██╗██╔══██╗██╔══██╗██╔══██╗██║░██╔╝██╔════╝
███████║███████║██╔██╗██║██║░░██║██████╦╝██████╔╝███████║█████═╝░█████╗░░
██╔══██║██╔══██║██║╚████║██║░░██║██╔══██╗██╔══██╗██╔══██║██╔═██╗░██╔══╝░░
██║░░██║██║░░██║██║░╚███║██████╔╝██████╦╝██║░░██║██║░░██║██║░╚██╗███████╗
╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═════╝░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝

Version 1.0
Copyright (c) 2020 Eugenio Ciullo


Questo sketch è stato creato da Eugenio Ciullo

Installare nella Documents/Arduino directory la libreria ArduinoJoystickLibrary creata da MHeironimus reperibile al seguente link:
https://github.com/MHeironimus/ArduinoJoystickLibrary


Lo sketch per il freno a mano è stato configurato per utilizzare un potenziometro collegato sugli estremi a GND e VCC e il pin centrale su A0

*/


#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Numero Punsanti, Numero Hat Switch
  false, false, false,     // assi X, Y, e Z
  false, false, false,   // assi Rx, Ry, e Rz
  false, false,          // rudder e throttle
  false, true, false);  // Acceleratore, Freno, e Sterzo
 


// Modificare i valori minpotenziometro e maxpotenziometro in base ai valori prelevati dal monitor seriale

const long minpotenziometro = 0;
const long maxpotenziometro = 1023;
const long minjoybrake = -32768;
const long maxjoybrake = 32768;
const long handbrake = 0;

const bool initAutoSendState = true; 

void setup() {
  Joystick.begin();
  
  Serial.begin(57600); delay(10);   //Commentare con doppie // per disabilitare il debug
  
  Joystick.setBrakeRange(minjoybrake, maxjoybrake);
  pinMode(A0, INPUT_PULLUP);
}

void loop() {

	handbrake = analogRead(A0);
	handbrake = map(handbrake,minpotenziometro,maxpotenziometro, minjoybrake, maxjoybrake);

    Serial.print("Valore Potenziometro: \t");    //Commentare con doppie // per disabilitare il debug
    Serial.print(handbrake);     //Commentare con doppie // per disabilitare il debug

	Joystick.setBrake(handbrake);

  delay(5);
}