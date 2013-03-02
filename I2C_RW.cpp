#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/i2c-dev.h>
#include "I2C_RW.h"

/** Default constructor.
 */
I2C_RW::I2C_RW() {
}

/** Read consecutive bytes of length(length) from 8-bit registers.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param length = number of consecutive bytes to read
 * @param data Container for byte value read from device
 * @return Status of read operation (true = success)
 */
int8_t I2C_RW::readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data) {
    return readBytes(devAddr, regAddr, 1, data);
}

int8_t I2C_RW::readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data) {
    int8_t count = 0;
    int fd = open("/dev/i2c-0", O_RDWR);

    if (fd < 0) {
        fprintf(stderr, "Failed to open device: %s\n", strerror(errno));
        return(-1);
    }
    if (ioctl(fd, I2C_SLAVE, devAddr) < 0) {
        fprintf(stderr, "Failed to select device: %s\n", strerror(errno));
        close(fd);
        return(-1);
    }
    if (write(fd, &regAddr, 1) != 1) {
        fprintf(stderr, "Failed to write reg: %s\n", strerror(errno));
        close(fd);
        return(-1);
    }
    count = read(fd, data, length);
    if (count < 0) {
        fprintf(stderr, "Failed to read device(%d): %s\n", count, ::strerror(errno));
        close(fd);
        return(-1);
    } else if (count != length) {
        fprintf(stderr, "Short read  from device, expected %d, got %d\n", length, count);
        close(fd);
        return(-1);
    }
    close(fd);

    return count;
}

/** Write consecutive bytes of length(length) to 8-bit registers.
 * @param devAddr I2C slave device address
 * @param regAddr Register address to write to
 * @param data New byte value to write
 * @return Status of operation (true = success)
 */
bool I2C_RW::writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t* data) {
    return writeBytes(devAddr, regAddr, 1, data);
}

bool I2C_RW::writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* data) {
    int8_t count = 0;
    uint8_t buf[128];
    int fd;

    if (length > 127) {
        fprintf(stderr, "Byte write count (%d) > 127\n", length);
        return(FALSE);
    }

    fd = open("/dev/i2c-0", O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "Failed to open device: %s\n", strerror(errno));
        return(FALSE);
    }
    if (ioctl(fd, I2C_SLAVE, devAddr) < 0) {
        fprintf(stderr, "Failed to select device: %s\n", strerror(errno));
        close(fd);
        return(FALSE);
    }
    buf[0] = regAddr;
    memcpy(buf+1,data,length);
    count = write(fd, buf, length+1);
    if (count < 0) {
        fprintf(stderr, "Failed to write device(%d): %s\n", count, ::strerror(errno));
        close(fd);
        return(FALSE);
    } else if (count != length+1) {
        fprintf(stderr, "Short write to device, expected %d, got %d\n", length+1, count);
        close(fd);
        return(FALSE);
    }
    close(fd);

    return TRUE;
}


