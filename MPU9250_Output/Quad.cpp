#include "Quad.h"


Quad quad;

int Quad::Initialize()
{

	SimpleSPIClass spi;
	
	if (!spi.start())
		return 0;

	SimpleI2CClass i2c;

	i2c.begin();
	
	
	if (!i2c.getAK8963CID())
		return -1;
	
	

	return 1;
}
