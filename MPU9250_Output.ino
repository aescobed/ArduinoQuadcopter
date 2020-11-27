
#include "SimpleSPI.h"
#include "utils/twi.h"


float data;
void setup() {

  Serial.begin(19200);

  int checkInit = spi.begin();
  
  if(checkInit>0)
    Serial.println("MPU9250 set");

  // If initialization fails
  else
    while(true)
    {
      Serial.print("Initialization failed with error ");
      Serial.println(checkInit);
    }

}

void loop() {



  data = spi.transfer(0x43);

  Serial.print("ACCEL: ");
  Serial.println(spi.returnVar());


}
