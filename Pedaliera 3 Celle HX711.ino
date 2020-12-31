/*


╭━━━╮╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭━━━╮╱╱╱╭╮╭╮
┃╭━━╯╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱┃╭━╮┃╱╱╱┃┃┃┃
┃╰━━┳╮╭┳━━┳━━┳━╮╭┳━━╮┃┃╱╰╋┳╮╭┫┃┃┃╭━━╮
┃╭━━┫┃┃┃╭╮┃┃━┫╭╮╋┫╭╮┃┃┃╱╭╋┫┃┃┃┃┃┃┃╭╮┃
┃╰━━┫╰╯┃╰╯┃┃━┫┃┃┃┃╰╯┃┃╰━╯┃┃╰╯┃╰┫╰┫╰╯┃
╰━━━┻━━┻━╮┣━━┻╯╰┻┻━━╯╰━━━┻┻━━┻━┻━┻━━╯
╱╱╱╱╱╱╱╭━╯┃
╱╱╱╱╱╱╱╰━━╯


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

Collegare come segue:
Cella Acceleratore:
VCC -> VCC
GND -> GND
DOUT -> PIN2
Clock -> PIN3

Cella Freno:
VCC -> VCC
GND -> GND
DOUT -> PIN4
Clock -> PIN5

Cella Frizione:
VCC -> VCC
GND -> GND
DOUT -> PIN6
Clock -> PIN7

*/

#include "HX711.h"
#include <Joystick.h>

const int LOADCELL_DOUT_PIN1 = 2;
const int LOADCELL_SCK_PIN1 = 3;
const int LOADCELL_DOUT_PIN2 = 4;
const int LOADCELL_SCK_PIN2 = 5;
const int LOADCELL_DOUT_PIN3 = 6;
const int LOADCELL_SCK_PIN3 = 7;



long Acceleratore = 0;
long Freno = 0;
long Frizione = 0;


// Se volete calibrare il range degli assi, sostituire i seguenti valori
const long ZonainferioreAcceleratore = -32767;
const long ZonasuperioreAcceleratore = 32767;
const long ZonainferioreFreno = -32767;
const long ZonasuperioreFreno = 32767;
const long ZonainferioreFrizione = -32767;
const long ZonasuperioreFrizione = 32767;

const long calibration_factor1 = 10;
const long calibration_factor2 = 10;
const long calibration_factor3 = 10;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  true, true, true,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

HX711 scale1;
HX711 scale2;
HX711 scale3;


void setup() {
  scale1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);
  scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);
  scale3.begin(LOADCELL_DOUT_PIN3, LOADCELL_SCK_PIN3);
  scale1.set_scale(calibration_factor1);
  scale2.set_scale(calibration_factor2);
  scale3.set_scale(calibration_factor3);  
  Joystick.begin();
  Joystick.setRxAxisRange(ZonainferioreAcceleratore, ZonasuperioreAcceleratore);
  Joystick.setRyAxisRange(ZonainferioreFreno, ZonasuperioreFreno);
  Joystick.setRzAxisRange(ZonainferioreFrizione, ZonasuperioreFrizione);
 
//decommentare il prossimo valore se si vuole aprire la seriale
   Serial.begin(9600);
    }
const bool initAutoSendState = true;


void loop() {
  Acceleratore = scale1.get_units();
  Freno = scale2.get_units();
  Frizione = scale3.get_units();
  Joystick.setRxAxis(Acceleratore);
  Joystick.setRyAxis(Freno);
  Joystick.setRzAxis(Frizione);
  
// Decommentare le seriali eliminando /* e */ alla fine dei Serial.print
 
    Serial.print("Acceleratore : \t");
    Serial.print(Acceleratore);
    Serial.print("\t \t Freno: \t");
    Serial.print(Freno);
    Serial.print("\t Frizione : \t");
    Serial.println(Frizione);  

  delay(5);
}
