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

Leggi lo sketch in modo da capire come fare la taratura

Alla fine della taratura commentare le linee Serial

*/


#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Numero Punsanti, Numero Hat Switch
  false, false, false,     // assi X, Y, e Z
  false, false, false,   // assi Rx, Ry, e Rz
  false, false,          // rudder e throttle
  false, true, false);  // Acceleratore, Freno, e Sterzo
 


// Modificare i valori minpotenziometro e maxpotenziometro in base ai valori prelevati dal monitor seriale

long minpotenziometro = 0;
long maxpotenziometro = 1023;
long minjoybrake = 0;
long maxjoybrake = 1023;

//se hai collegato al contrario il potenziometro, inverti i valori mapmin e mapmax
long mapmin = 0;      // inserire 1023
long mapmax = 1023;	// inserire 0


const bool initAutoSendState = true; 

void setup() {
  Joystick.begin();
 // Serial.begin(57600); delay(10);   //Commentare con doppie // per disabilitare il debug
  
  Joystick.setBrakeRange(minjoybrake, maxjoybrake);
  pinMode(A0, INPUT_PULLUP);
}

void loop() {

	long valpotenziometro = analogRead(A0);
	long handbrake = map(valpotenziometro,minpotenziometro,maxpotenziometro, mapmin, mapmax);

  //  Serial.print("Valore Potenziometro: \t");    //Commentare con doppie // per disabilitare il debug
  //  Serial.print(valpotenziometro);     			//Commentare con doppie // per disabilitare il debug
  //  Serial.print("\t\t Valore joy: \t");   		 //Commentare con doppie // per disabilitare il debug
  //  Serial.println(handbrake);     				//Commentare con doppie // per disabilitare il debug

	Joystick.setBrake(handbrake);

  delay(5); (questo è un piccolo ritardo temporale, aumenta la stabilità del segnale)
}
