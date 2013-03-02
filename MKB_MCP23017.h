#ifndef _MKB_MCP23017_H_
#define _MKB_MCP23017_H_

#include "I2C_RW.h"

class MKB_MCP23017 {
	public:
		MKB_MCP23017();
		MKB_MCP23017(uint8_t address);
		void begin(uint8_t addr);
		void begin();
		void pinMode(uint8_t pin, uint8_t dir);
		void digitalWrite(uint8_t pin, uint8_t dir);
		uint16_t readGPIOAB();
		void pullUp(uint8_t pin, uint8_t dir);
		void writeGPIOAB(uint16_t data);
		uint8_t digitalRead(uint8_t pin);

	private:
		uint8_t devAddr;
		uint8_t i2caddr;
		bool setAllInputs();
};

#define MCP23017_DEFAULT_ADDRESS	0x20

// registers
#define MCP23017_IODIRA				0x00
#define MCP23017_IPOLA				0x02
#define MCP23017_GPINTENA			0x04
#define MCP23017_DEFVALA			0x06
#define MCP23017_INTCONA			0x08
#define MCP23017_IOCONA				0x0A
#define MCP23017_GPPUA				0x0C
#define MCP23017_INTFA				0x0E
#define MCP23017_INTCAPA			0x10
#define MCP23017_GPIOA				0x12
#define MCP23017_OLATA				0x14


#define MCP23017_IODIRB				0x01
#define MCP23017_IPOLB				0x03
#define MCP23017_GPINTENB			0x05
#define MCP23017_DEFVALB			0x07
#define MCP23017_INTCONB			0x09
#define MCP23017_IOCONB				0x0B
#define MCP23017_GPPUB				0x0D
#define MCP23017_INTFB				0x0F
#define MCP23017_INTCAPB			0x11
#define MCP23017_GPIOB				0x13
#define MCP23017_OLATB				0x15

#endif
