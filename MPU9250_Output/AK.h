


class AKClass {

public:

	AKClass();

	void setup();

private:

	const uint8_t MPU9250_ADDRESS = 0x69;

    const uint8_t AK8963_I2C_ADDR = 0x0C;
    const uint8_t WHO_AM_I_AK8963 = 0x00;
    const uint8_t I2C_SLV0_ADDR = 0x25;
    const uint8_t I2C_SLV0_REG = 0x26;
    const uint8_t I2C_SLV0_CTRL = 0x27;
    const uint8_t I2C_MST_CTRL = 0x24;
    const uint8_t AK8963_CNTL = 0x0A;
    const uint8_t USER_CTRL = 0x6A;  // Bit 7 enable DMP, bit 3 reset DMP
    const uint8_t EXT_SENS_DATA_00 = 0x49;


};

extern AKClass AK;