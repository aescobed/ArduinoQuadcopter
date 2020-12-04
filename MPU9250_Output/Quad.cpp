#include "Quad.h"


Quad quad;

int Quad::Initialize()
{
	/*
	SimpleSPIClass spi;
	
	if (!spi.start())
		return 0;

	
	
	AKClass AK;

	AK.setup();

	*/
	SimpleI2CClass i2c;

	i2c.begin();


	return 1;
	
}
