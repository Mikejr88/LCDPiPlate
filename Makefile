
all: main

SRCS		=	main.cpp I2C_RW.h I2C_RW.cpp MKB_MCP23017.h MKB_MCP23017.cpp \
				Adafruit_RGBLCDShield.cpp Adafruit_RGBLCDShield.h
HDRS		=	I2C_RW.h MKB_MCP23017.h Adafruit_RGBLCDShield.h
CMN_OBJS	=	I2C_RW.o MKB_MCP23017.o Adafruit_RGBLCDShield.o
RAW_OBJS	=	main.o

CXXFLAGS	=	-Wall -O

$(CMN_OBJS) $(RAW_OBJS) : $(HDRS)

main: $(CMN_OBJS) $(RAW_OBJS)
	$(CXX) -o $@ $^

clean:
	rm -f $(CMN_OBJS) $(RAW_OBJS) main

#Create tar file
tar: $(SRCS)
	tar -czvf MCP23017.tar $^ Makefile
