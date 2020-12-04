#include "utils/SoftI2CMaster.cpp"


#include "AK.h"

AKClass AK;
const int sdaPin = 11;
const int sclPin = 12;

SoftI2CMaster softi2c;

AKClass::AKClass()
{

	// create instance of softi2c communication
	softi2c = SoftI2CMaster(sclPin, sdaPin, 0);

}



void AKClass::setup() {

	byte error;
	error = softi2c.beginTransmission(AK8963_I2C_ADDR);



}


