
#include "Quad.h"


float data;
void setup() {

  Serial.begin(19200);

  int res = 0;
  res = quad.Initialize();
  while(!res){
    Serial.print("Initialization failed Error:");
    Serial.println(res);
  }

}

void loop() {

  Serial.println("Success");


}
