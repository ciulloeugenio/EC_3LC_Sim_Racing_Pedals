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

#include "HX711.h"
#include "Joystick.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN1 = 2;
const int LOADCELL_SCK_PIN1 = 3;
const int LOADCELL_DOUT_PIN2 = 4;
const int LOADCELL_SCK_PIN2 = 5;
const int LOADCELL_DOUT_PIN3 = 6;
const int LOADCELL_SCK_PIN3 = 7;

const long ACCMIN = -3585;
const long ACCMAX = 4174;
const long BRMIN = 3204;
const long BRMAX = 23678;
const long CLMIN = 5628;
const long CLMAX = 7638;

const double calibration_factor1 = 5;
const double calibration_factor2 = 100;
const double calibration_factor3 = 25;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Numero Punsanti, Numero Hat Switch
  false, false, false,     // assi X, Y, e Z
  true, true, true,   // assi Rx, Ry, e Rz
  false, false,          // rudder e throttle
  false, false, false);  // Acceleratpre, Freno, e Sterzo
  
const bool initAutoSendState = true; 


HX711 scale1;
HX711 scale2;
HX711 scale3;

void setup() {
//  Serial.begin(57600);
  scale1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);
  scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);
  scale3.begin(LOADCELL_DOUT_PIN3, LOADCELL_SCK_PIN3);
  scale1.set_scale(calibration_factor1);
  scale2.set_scale(calibration_factor2);
  scale3.set_scale(calibration_factor3);
  Joystick.begin();
  Joystick.setRxAxisRange(ACCMIN,ACCMAX);
  Joystick.setRyAxisRange(BRMIN,BRMAX);
  Joystick.setRzAxisRange(CLMIN,CLMAX);
}

void loop() {
    long reading1 = scale1.get_units();
//    Serial.print("HX711 reading1: \t");
//    Serial.print(reading1);
    Joystick.setRxAxis(reading1);
    long reading2 = scale2.get_units();
//    Serial.print("\t\t HX711 reading2: \t");
//     Serial.print(reading2);
    Joystick.setRyAxis(reading2);
    long reading3 = scale3.get_units();
//    Serial.print("\t\t HX711 reading3: \t");
//    Serial.println(reading3);
    Joystick.setRzAxis(reading3);
    delay(5);
}
