/*


███████╗░█████╗░    ░██████╗██╗███╗░░░███╗    ██████╗░░█████╗░░█████╗░██╗███╗░░██╗░██████╗░
██╔════╝██╔══██╗    ██╔════╝██║████╗░████║    ██╔══██╗██╔══██╗██╔══██╗██║████╗░██║██╔════╝░
█████╗░░██║░░╚═╝    ╚█████╗░██║██╔████╔██║    ██████╔╝███████║██║░░╚═╝██║██╔██╗██║██║░░██╗░
██╔══╝░░██║░░██╗    ░╚═══██╗██║██║╚██╔╝██║    ██╔══██╗██╔══██║██║░░██╗██║██║╚████║██║░░╚██╗
███████╗╚█████╔╝    ██████╔╝██║██║░╚═╝░██║    ██║░░██║██║░░██║╚█████╔╝██║██║░╚███║╚██████╔╝
╚══════╝░╚════╝░    ╚═════╝░╚═╝╚═╝░░░░░╚═╝    ╚═╝░░╚═╝╚═╝░░╚═╝░╚════╝░╚═╝╚═╝░░╚══╝░╚═════╝░

██████╗░██╗░░██╗  ██╗░░░░░░█████╗░░█████╗░██████╗░░█████╗░███████╗██╗░░░░░██╗░░░░░
╚════██╗╚██╗██╔╝  ██║░░░░░██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔════╝██║░░░░░██║░░░░░
░█████╔╝░╚███╔╝░  ██║░░░░░██║░░██║███████║██║░░██║██║░░╚═╝█████╗░░██║░░░░░██║░░░░░
░╚═══██╗░██╔██╗░  ██║░░░░░██║░░██║██╔══██║██║░░██║██║░░██╗██╔══╝░░██║░░░░░██║░░░░░
██████╔╝██╔╝╚██╗  ███████╗╚█████╔╝██║░░██║██████╔╝╚█████╔╝███████╗███████╗███████╗
╚═════╝░╚═╝░░╚═╝  ╚══════╝░╚════╝░╚═╝░░╚═╝╚═════╝░░╚════╝░╚══════╝╚══════╝╚══════╝

██████╗░███████╗██████╗░░█████╗░██╗░░░░░░██████╗
██╔══██╗██╔════╝██╔══██╗██╔══██╗██║░░░░░██╔════╝
██████╔╝█████╗░░██║░░██║███████║██║░░░░░╚█████╗░
██╔═══╝░██╔══╝░░██║░░██║██╔══██║██║░░░░░░╚═══██╗
██║░░░░░███████╗██████╔╝██║░░██║███████╗██████╔╝
╚═╝░░░░░╚══════╝╚═════╝░╚═╝░░╚═╝╚══════╝╚═════╝░

Version 1.0
Copyright (c) 2020 Eugenio Ciullo


Questo sketch è stato creato da Eugenio Ciullo

Installare nella Documents/Arduino directory la libreria ArduinoJoystickLibrary creata da MHeironimus reperibile al seguente link:
https://github.com/MHeironimus/ArduinoJoystickLibrary


Lo sketch per la Pedaliera è stato configurato per ricevere il segnale da 3 amplificatori HX711 per loadcell

*/



// Includere le librerie HX711.h e Joystick.h

#include "HX711.h"
#include "Joystick.h"


// HX711 Collegamenti
const int LOADCELL1_DOUT_PIN = 2;
const int LOADCELL1_SCK_PIN = 3;
const int LOADCELL2_DOUT_PIN = 4;
const int LOADCELL2_SCK_PIN = 5;
const int LOADCELL3_DOUT_PIN = 6;
const int LOADCELL3_SCK_PIN = 7;

// dichiarazione delle celle di carico
HX711 cella_acceleratore;
HX711 cella_freno;
HX711 cella_frizione;

//dichiarazione variabili
long raw_acceleratore = 0;
long raw_freno = 0;
long raw_frizione = 0;
int acceleratore = 0;
int freno = 0;
int frizione = 0;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Numero Punsanti, Numero Hat Switch
  false, false, false,     // assi X, Y, e Z
  true, true, true,   // assi Rx, Ry, e Rz
  false, false,          // rudder e throttle
  false, false, false);  // Acceleratpre, Freno, e Sterzo
  
const bool initAutoSendState = true; 



void setup() {

//apertura seriale
  Serial.begin(57600);
  
// inializzazione controller  
  Joystick.begin();

  
//dichiarazione celle di carico e assegnazione pin
  cella_acceleratore.begin(LOADCELL1_DOUT_PIN, LOADCELL1_SCK_PIN);
  cella_freno.begin(LOADCELL2_DOUT_PIN, LOADCELL2_SCK_PIN);
  cella_frizione.begin(LOADCELL3_DOUT_PIN, LOADCELL3_SCK_PIN);

}

void loop() {
  
//Loop Acceleratore
    raw_acceleratore = cella_acceleratore.read();
    Serial.print("HX711 cella_acceleratore: ");//Stampiamo a video il valore raw della cella, in formato long
    Serial.print(raw_acceleratore);
    Serial.print("  ||   Valore Acceleratore: ");
    acceleratore = map(raw_acceleratore,0,800000,0,1024); //qui convertiamo il valore long in intero, e lo mappiamo in base alle nostre esigenze la modalità è map(valore, valore_in_min, valore_in_max, valore_out_min, valore_out_max)
    Serial.print(acceleratore);
  Joystick.setRxAxis(acceleratore);
  
//Loop Freno
    raw_freno = cella_freno.read();
    Serial.print("  ||  HX711 cella_freno: ");
    Serial.print(raw_freno);
    Serial.print("  ||   Valore Freno: ");
    freno = map(raw_freno,0,800000,0,1024); //qui convertiamo il valore long in intero, e lo mappiamo in base alle nostre esigenze la modalità è map(valore, valore_in_min, valore_in_max, valore_out_min, valore_out_max)
    Serial.print(freno);
  Joystick.setRyAxis(freno);

  
//Loop Frizione
    raw_frizione = cella_frizione.read();
    Serial.print("  ||  HX711 cella_frizione: ");
    Serial.print(raw_frizione);
    Serial.print("  ||   Valore Frizione: ");
    frizione = map(raw_frizione,0,800000,0,1024); //qui convertiamo il valore long in intero, e lo mappiamo in base alle nostre esigenze la modalità è map(valore, valore_in_min, valore_in_max, valore_out_min, valore_out_max)
    Serial.println(frizione);
  Joystick.setRzAxis(frizione);
  
 delay(1);  
} 
