#include <EEPROM.h>
//#include <avr/sleep.h>


//const unsigned long blink = 50000;
const long oneSecond = 1000;  // a second is a thousand milliseconds
const long oneMinute = oneSecond * 60;
const long oneHour   = oneMinute * 60;
const long oneDay    = oneHour * 24;
  unsigned long writeHouerEEprom;


int houersEEPROM = 0;
int houersmillis = 0;
void setup() {
    Serial.begin(9600);
    pinMode(13, OUTPUT);
    pinMode(8, INPUT_PULLUP);

    Serial.println("Starting...");

    EEPROM.get(0, houersEEPROM);
    Serial.print("houersEEPROM = "); Serial.println(houersEEPROM); Serial.println();
    writeHouerEEprom = 0;

    if (digitalRead(8) == LOW) {
      for (int i = 0 ; i < EEPROM.length() ; i++) EEPROM.write(i, 0);
    Serial.println("EEPROM ERASED");
    EEPROM.get(0, houersEEPROM);
    Serial.print("houersEEPROM = "); Serial.println(houersEEPROM); Serial.println();
    }

}

void loop() {
  // put your main code here, to run repeatedly:

// put your setup code here, to run once:
  digitalWrite(13, LOW);  //lamp is OFF
  unsigned long presentMillisBlink = millis();
//  unsigned long writeHouerEEprom;
  while(millis() - presentMillisBlink <= 5000)//3600000UL)
  {
    ;   //do nothing and chcek again
  }
  digitalWrite(13, HIGH);   //lamp is ON
  delay(1000); 

  if (millis() - writeHouerEEprom > oneHour ) {
    writeHouerEEprom = millis();
    houersmillis++;
    EEPROM.get(0, houersEEPROM);
    if (houersEEPROM < houersmillis) {
      EEPROM.write(0, houersmillis);
      Serial.print("Write to EEPROM "); Serial.println(houersmillis);
    } else {
      Serial.print("Houers in EEPROM ("); Serial.print(houersEEPROM); Serial.println(") more then uptime("); Serial.print(houersmillis); Serial.println("). Skeeping... We are rebooting?");
    }
  }
}
