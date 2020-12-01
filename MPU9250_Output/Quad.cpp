#include "Quad.h"


Quad quad;

int Quad::Initialize()
{

	SimpleSPIClass spi;
	
	if (!spi.start())
		return 0;

	SimpleI2CClass i2c;

	i2c.begin();

	i2c.InitAK8963();
	
	int AKID = i2c.getAK8963CID();

	return AKID;
	
}
