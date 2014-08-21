#include <SD.h>

const int pin_card_select{10}; //Must be 10, the shield requires it
const int pin_chip_select{4};
const int pin_thermistor{A0};
const int pin_humidity{A1};

void setup() 
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("SD card: ");
  delay(10);
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(pin_card_select, OUTPUT);
 
  // see if the card is present and can be initialized:
  if (!SD.begin(pin_chip_select)) {
    Serial.println("FAIL");
    delay(10);
    // don't do anything more:
    return;
  }
  Serial.println("OK");
  delay(10);
  
  pinMode(pin_thermistor,INPUT);
  pinMode(pin_humidity,INPUT);
  Serial.begin(9600);
}

void loop() 
{
  const int temperature{analogRead(pin_thermistor)}; 
  const int humidity{analogRead(pin_humidity)}; 
  
  const String s 
    = String(millis() / 1000)
    + ","
    + String(temperature)
    + ","
    + String(humidity)
  ;
  File file = SD.open("jb_tth.txt", FILE_WRITE);

  if (file) 
  {
    file.println(s);
    file.close();
    Serial.println(s);
  }  
  else 
  {
    Serial.println("error opening file");
  }
  delay(1000);
}

