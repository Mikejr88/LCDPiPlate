#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "MKB_MCP23017.h"

/** Default constructor, uses default I2C address.
 * @see MCP23017_DEFAULT_ADDRESS
 */
MKB_MCP23017::MKB_MCP23017() {
    devAddr = MCP23017_DEFAULT_ADDRESS;
    //setAllInputs();
}

/** Specific address constructor.
 * @param address I2C address
 * @see MCP23017_DEFAULT_ADDRESS
 */
MKB_MCP23017::MKB_MCP23017(uint8_t address) {
    devAddr = address;
    //setAllInputs();
}

void MKB_MCP23017::begin(uint8_t addr) {
	if (addr > 7) {
		addr = 7;
	}
	i2caddr = addr;

	// set defaults!
	setAllInputs();
}

void MKB_MCP23017::begin() {
  begin(0);
}

/** Set IODIR to inputs
 *  Safe startup
 */
bool MKB_MCP23017::setAllInputs(){
	uint8_t dataWrite[] = {0xFF, 0xFF};
	
	if(!I2C_RW::writeBytes(devAddr, MCP23017_IODIRA, 2, &dataWrite[0])){
		printf("Setup failed");
		return false;
	}
	/*if(!I2C_RW::writeByte(devAddr, MCP23017_IODIRB, &dataWrite)){
		printf("Setup failed");
		return false;
	}*/
	return true;
}

void MKB_MCP23017::pinMode(uint8_t pin, uint8_t dir) {
	uint8_t iodir;
	uint8_t iodiraddr;

	// only 16 bits!
	if (pin > 15)
		return;

	if (pin < 8)
		iodiraddr = MCP23017_IODIRA;
	else {
		iodiraddr = MCP23017_IODIRB;
		pin -= 8;
	}

	// read the current IODIR
	I2C_RW::readByte(devAddr, iodiraddr, &iodir);

	// set the pin and direction
	if (dir == 1) {
		iodir |= 1 << pin; 
	} else {
		iodir &= ~(1 << pin);
	}

	// write the new IODIR
	I2C_RW::writeByte(devAddr, iodiraddr, &iodir);
}

uint16_t MKB_MCP23017::readGPIOAB(){
	uint8_t dataRead[2];
	uint16_t readBits = 0;
	
	I2C_RW::readBytes(devAddr, MCP23017_GPIOA, 2, &dataRead[0]);
	readBits = dataRead[1] << 8;
	readBits = readBits | dataRead[0];
	
	return readBits;	
}

void MKB_MCP23017::writeGPIOAB(uint16_t data){
	uint8_t dataWrite[2];
	dataWrite[0] = data & 0xff;
	dataWrite[1] = data >> 8;
	
	// write the new GPIO
	I2C_RW::writeBytes(devAddr, MCP23017_GPIOA, 2, &dataWrite[0]);
}

void MKB_MCP23017::digitalWrite(uint8_t pin, uint8_t dir) {
	uint8_t gpio;
	uint8_t gpioaddr, olataddr;

	// only 16 bits!
	if (pin > 15)
		return;

	if (pin < 8) {
		olataddr = MCP23017_OLATA;
		gpioaddr = MCP23017_GPIOA;
	} else {
		olataddr = MCP23017_OLATB;
		gpioaddr = MCP23017_GPIOB;
		pin -= 8;
	}

	// read the current GPIO output latches
	I2C_RW::readByte(devAddr, olataddr, &gpio);
	
	// set the pin and direction
	if (dir == 1) {
		gpio |= 1 << pin; 
	} else {
		gpio &= ~(1 << pin);
	}

	// write the new GPIO
	I2C_RW::writeByte(devAddr, gpioaddr, &gpio);
}

void MKB_MCP23017::pullUp(uint8_t pin, uint8_t dir){
	uint8_t gppu, gppuaddr;
	
	// only 16 bits!
	if (pin > 15)
		return;

	if (pin < 8)
		gppuaddr = MCP23017_GPPUA;
	else {
		gppuaddr = MCP23017_GPPUB;
		pin -= 8;
	}

	// read the current pullup resistor set
	I2C_RW::readByte(devAddr, gppuaddr, &gppu);
	
	// set the pin and direction
	if (dir == 1) {
		gppu |= 1 << pin; 
	} else {
		gppu &= ~(1 << pin);
	}

	// write the new GPIO
	I2C_RW::writeByte(devAddr, gppuaddr, &gppu);
}

uint8_t MKB_MCP23017::digitalRead(uint8_t pin) {
	uint8_t gpioaddr, gpio;

	// only 16 bits!
	if (pin > 15)
		return 0;

	if (pin < 8)
		gpioaddr = MCP23017_GPIOA;
	else {
		gpioaddr = MCP23017_GPIOB;
		pin -= 8;
	}

	// read the current GPIO
	I2C_RW::readByte(devAddr, gpioaddr, &gpio);
  
	return (gpio >> pin) & 0x1;
}
