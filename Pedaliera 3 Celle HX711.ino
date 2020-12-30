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
#include "Joystick.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN1 = 2;
const int LOADCELL_SCK_PIN1 = 3;
const int LOADCELL_DOUT_PIN2 = 4;
const int LOADCELL_SCK_PIN2 = 5;
const int LOADCELL_DOUT_PIN3 = 6;
const int LOADCELL_SCK_PIN3 = 7;
/*
Abilitando il debug, nel monitor seriale verrà riprodotta la seguente stringa:
HX711 reading1: "valore Acceleratore"  HX711 reading2: "valore Freno"  HX711 reading3:  "Valore Frizione"
Premere i pedali, e impostare i valori qui di seguito per tarare il minimo e il massimo della corsa
*/

// Valori Costanti
const long ACCMIN = -32767;
const long ACCMAX = 32767;
const long BRMIN = -32767;
const long BRMAX = 32767;
const long CLMIN = -32767;
const long CLMAX = 32767;

// Fattore di Calibrazione
const long calibration_factor1 = 10;   //Sostituire questo valore di modo che il valore raw della cella sia nel range tra -32767 e 32767
const long calibration_factor2 = 10;  //Sostituire questo valore di modo che il valore raw della cella sia nel range tra -32767 e 32767
const long calibration_factor3 = 10; //Sostituire questo valore di modo che il valore raw della cella sia nel range tra -32767 e 32767


// Dettaglio HID Joystick
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
  Serial.begin(9600); //Decommentare per aprire il debug
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
    Serial.print("Acceleratore: \t");    //Decommentare per aprire il debug
    Serial.print(reading1);     //Decommentare per aprire il debug
    Joystick.setRxAxis(reading1);
    long reading2 = scale2.get_units();
    Serial.print("\t\t Freno: \t");    //Decommentare per aprire il debug
     Serial.print(reading2);      //Decommentare per aprire il debug
    Joystick.setRyAxis(reading2);
    long reading3 = scale3.get_units();
    Serial.print("\t\t Frizione: \t");      //Decommentare per aprire il debug
    Serial.println(reading3);     //Decommentare per aprire il debug
    Joystick.setRzAxis(reading3);
    delay(5);
}
