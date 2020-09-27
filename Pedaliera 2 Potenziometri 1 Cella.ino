/*
Questo sketch è stato creato da Eugenio Ciullo

Per la corretta compilazione installare le librerire ufficiali HX711 + HX711_ADC

Installare inoltre nella Documents/Arduino directory la libreria ArduinoJoystickLibrary creata da MHeironimus reperibile al seguente link:
https://github.com/MHeironimus/ArduinoJoystickLibrary


Lo sketch per la Pedaliera è stato configurato con LoadCell per il Freno amplificata da HX711 (collegare Clock sul pin 3 e data sul pin 2),
Potenziometro Acceleratore A0, e Potenziometro Frizione A1...

*/


#include <Joystick.h>
#include <HX711_ADC.h>
#include <EEPROM.h>

//pins:
const int HX711_dout = 2; //Collegare il Data Out della HX711 al pin 2
const int HX711_sck = 3; //Collegare il Clock Out della HX711 al pin 3

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
long t;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Numero Punsanti, Numero Hat Switch
  false, false, false,     // assi X, Y, e Z
  true, true, true,   // assi Rx, Ry, e Rz
  false, false,          // rudder e throttle
  false, false, false);  // Acceleratpre, Freno, e Sterzo
  
int RxAxis_ = 0;
int RyAxis_ = 0;
int RzAxis_ = 0;
const bool initAutoSendState = true; 

void setup() {
  Joystick.begin();
  Serial.begin(57600); delay(10);
  Serial.println();
  Serial.println("Starting...");

  LoadCell.begin();
  float calibrationValue;
  calibrationValue = 696.0; // uncomment this if you want to set the calibration value in the sketch
#if defined(ESP8266)|| defined(ESP32)
  //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
#endif
  //EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

  long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.println("Startup is complete");
  }
}

void loop() {
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      float i = LoadCell.getData();
      Serial.print("Load_cell output val: ");
      Serial.println(i);
      newDataReady = 0;
      t = millis();
    }
  }

  // receive command from serial terminal, send 't' to initiate tare operation:
  if (Serial.available() > 0) {
    float i;
    char inByte = Serial.read();
    if (inByte == 't') LoadCell.tareNoDelay();
  }

  // check if last tare operation is complete:
  if (LoadCell.getTareStatus() == true) {
    Serial.println("Tare complete");
  }
RxAxis_ = analogRead(A0);
 RxAxis_ = map(RxAxis_,0,32768,0,32768);
 Joystick.setRxAxis(RxAxis_);
RyAxis_ = LoadCell.getData();
 RyAxis_ = map(RyAxis_,0,32768,0,32768);
 Joystick.setRyAxis(RyAxis_);
RzAxis_ = analogRead(A1);
 RzAxis_ = map(RzAxis_,0,32768,0,32768);
 Joystick.setRzAxis(RzAxis_);
  delay(1);
}
