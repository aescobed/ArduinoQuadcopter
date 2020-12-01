
#include "utils/twi.c"

#include "SimpleI2C.h"


SimpleI2CClass i2c;

uint8_t SimpleI2CClass::rxBuffer[BUFFER_LENGTH];
uint8_t SimpleI2CClass::rxBufferIndex = 0;
uint8_t SimpleI2CClass::rxBufferLength = 0;

uint8_t SimpleI2CClass::txAddress = 0;
uint8_t SimpleI2CClass::txBuffer[BUFFER_LENGTH];
uint8_t SimpleI2CClass::txBufferIndex = 0;
uint8_t SimpleI2CClass::txBufferLength = 0;

void (*SimpleI2CClass::user_onRequest)(void);
void (*SimpleI2CClass::user_onReceive)(int);

void SimpleI2CClass::begin() {
	// Begin I2C communication
	twi_init();
	twi_attachSlaveTxEvent(onRequestService); // default callback must exist
	twi_attachSlaveRxEvent(onReceiveService); // default callback must exist
}


uint8_t SimpleI2CClass::getAK8963CID()
{
	//  uint8_t c = readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);  // Read WHO_AM_I register for MPU-9250
	writeByte(MPU9250_ADDRESS, USER_CTRL, 0x20);    // Enable I2C Master mode  
	writeByte(MPU9250_ADDRESS, I2C_MST_CTRL, 0x0D); // I2C configuration multi-master I2C 400KHz

	writeByte(MPU9250_ADDRESS, I2C_SLV0_ADDR, AK8963_I2C_ADDR | 0x80);    // Set the I2C slave address of AK8963 and set for read.
	writeByte(MPU9250_ADDRESS, I2C_SLV0_REG, WHO_AM_I_AK8963);           // I2C slave 0 register address from where to begin data transfer
	writeByte(MPU9250_ADDRESS, I2C_SLV0_CTRL, 0x81);                     // Enable I2C and transfer 1 byte
	delay(10);

	// WRONG PLACE
	uint8_t c = readByte(MPU9250_ADDRESS, EXT_SENS_DATA_00);             // Read the WHO_AM_I byte
	return c;
}





int SimpleI2CClass::writeByte(uint8_t address, uint8_t subAddress, uint8_t data) {


	txAddress = address;

	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;

	// in master transmitter mode
  // don't bother if buffer is full
	if (txBufferLength >= BUFFER_LENGTH) {
		return 0;
	}
	// put byte in tx buffer
	txBuffer[txBufferIndex] = subAddress;
	++txBufferIndex;
	// update amount in buffer   
	txBufferLength = txBufferIndex;

	// don't bother if buffer is full
	if (txBufferLength >= BUFFER_LENGTH) {
		return 0;
	}
	// put byte in tx buffer
	txBuffer[txBufferIndex] = data;
	++txBufferIndex;

	// update amount in buffer   
	txBufferLength = txBufferIndex;

	// transmit buffer (blocking)
	uint8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, true);
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;

	return ret;

}

int SimpleI2CClass::readByte(uint8_t address, uint8_t subAddress) {

	uint8_t data = 0;

	txAddress = AK8963_I2C_ADDR;

	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;

	// in master transmitter mode
// don't bother if buffer is full
	if (txBufferLength >= BUFFER_LENGTH) {
		return 0;
	}
	// put byte in tx buffer
	txBuffer[txBufferIndex] = subAddress;
	++txBufferIndex;
	// update amount in buffer   
	txBufferLength = txBufferIndex;

	// send tx buffer
	int8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, false);
	txBufferIndex = 0;
	txBufferLength = 0;

	// request from the MPU9250
	size_t size = 1;

	if (1 > BUFFER_LENGTH)
	{
		size = BUFFER_LENGTH;
	}

	size_t read = (twi_readFrom(AK8963_I2C_ADDR, rxBuffer, size) == 0) ? size : 0;
	rxBufferIndex = 0;
	rxBufferLength = read;

	// read the value
	int value = -1;
	if (rxBufferIndex < rxBufferLength)
	{
		value = rxBuffer[rxBufferIndex];
		++rxBufferIndex;
	}
	data = value;

	return data;

	/*
	uint8_t data = 0;                        // `data` will store the register data
  Wire.beginTransmission(address);         // Initialize the Tx buffer
  Wire.write(subAddress);                  // Put slave register address in Tx buffer
  Wire.endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
  Wire.requestFrom(address, 1);            // Read two bytes from slave register address on MPU9250
  data = Wire.read();                      // Fill Rx buffer with result
  return data;                             // Return data read from slave register
  */

}



// behind the scenes function that is called when data is requested
void SimpleI2CClass::onRequestService(void)
{
	// don't bother if user hasn't registered a callback
	if (!user_onRequest) {
		return;
	}
	// reset tx buffer iterator vars
	// !!! this will kill any pending pre-master sendTo() activity
	txBufferIndex = 0;
	txBufferLength = 0;
	// alert user program
	user_onRequest();
}




// behind the scenes function that is called when data is received
void SimpleI2CClass::onReceiveService(uint8_t* inBytes, int numBytes)
{
	// don't bother if user hasn't registered a callback
	if (!user_onReceive) {
		return;
	}
	// don't bother if rx buffer is in use by a master requestFrom() op
	// i know this drops data, but it allows for slight stupidity
	// meaning, they may not have read all the master requestFrom() data yet
	if (rxBufferIndex < rxBufferLength) {
		return;
	}
	// copy twi rx buffer into local read buffer
	// this enables new reads to happen in parallel
	for (uint8_t i = 0; i < numBytes; ++i) {
		rxBuffer[i] = inBytes[i];
	}
	// set rx iterator vars
	rxBufferIndex = 0;
	rxBufferLength = numBytes;
	// alert user program
	user_onReceive(numBytes);
}

// sets function called on slave write
void SimpleI2CClass::onReceive(void (*function)(int))
{
	user_onReceive = function;
}

// sets function called on slave read
void SimpleI2CClass::onRequest(void (*function)(void))
{
	user_onRequest = function;
}