

#include <Arduino.h>



#define BUFFER_LENGTH 32



class SimpleI2CClass {

public:
    void begin();
    
    uint8_t getAK8963CID();
    int writeByte(uint8_t address, uint8_t subAddress, uint8_t data);
    int readByte(uint8_t address, uint8_t subAddress);

private:

    static uint8_t txAddress;
    static uint8_t txBuffer[];
    static uint8_t txBufferIndex;
    static uint8_t txBufferLength;

    static uint8_t rxBuffer[];
    static uint8_t rxBufferIndex;
    static uint8_t rxBufferLength;

    const uint8_t MPU9250_ADDRESS = 0x69;

    const uint8_t AK8963_I2C_ADDR = 0x0C;
    const uint8_t WHO_AM_I_AK8963 = 0x00;
    const uint8_t I2C_SLV0_ADDR = 0x25;
    const uint8_t I2C_SLV0_REG = 0x26;
    const uint8_t I2C_SLV0_CTRL = 0x27;
    const uint8_t I2C_MST_CTRL = 0x24;
    const uint8_t USER_CTRL = 0x6A;  // Bit 7 enable DMP, bit 3 reset DMP
    const uint8_t EXT_SENS_DATA_00 = 0x49;


    static void onRequestService(void);
    static void onReceiveService(uint8_t*, int);
    void onReceive(void (*)(int));
    void onRequest(void (*)(void));
    static void (*user_onRequest)(void);
    static void (*user_onReceive)(int);
    

};

extern SimpleI2CClass i2c;