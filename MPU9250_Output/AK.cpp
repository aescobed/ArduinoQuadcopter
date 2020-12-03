#include "utils/SoftI2CMaster.cpp"
#include "AK.h"

AKClass AK;
const int sdaPin = 11;
const int sclPin = 12;

SoftI2CMaster i2c;

AKClass::AKClass()
{

	// create instance of softi2c communication
	i2c = SoftI2CMaster(sclPin, sdaPin, 0);

}



void AKClass::setup() {

	byte error;
	error = i2c.beginTransmission(MPU9250_ADDRESS);

}