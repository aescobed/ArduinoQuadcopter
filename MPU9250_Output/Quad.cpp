#include "Quad.h"

Quad quad;

int Quad::Initialize()
{

	SimpleSPIClass spi;
	
	if (!spi.start())
		return 0;

	


	return 1;
}
