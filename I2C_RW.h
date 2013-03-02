#ifndef _I2C_RW_H_
#define _I2C_RW_H_

#ifndef TRUE
#define TRUE	(1==1)
#define FALSE	(0==1)
#endif

class I2C_RW {
    public:
        I2C_RW();
        
        static int8_t readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data);
        static int8_t readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);

        static bool writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data);
        static bool writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);

};

#endif /* _I2C_RW_H_ */
