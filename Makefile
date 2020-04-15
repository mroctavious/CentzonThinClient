##Make file 
MKDIR = mkdir -p
PREFIX=.
BUILD_DIR=$(PREFIX)/build
BIN_DIR=$(PREFIX)/bin
LIB_DIR=$(BUILD_DIR)/lib
SRC_DIR = ./src

CC=g++
CFLAGS=-I./include -Wall -std=c++11 -O3 -fPIC

##Extra libraries dependencies,
####wiringPi:Controlling pins with PWM
####BCM2835: For the RDIF module
CLIBS=-lwiringPi -lbcm2835

##Where the module is located
MOD_GPIO_CORE = src/GPIO_core/GPIO_core
MOD_EGPIO = src/eGPIO/eGPIO
MOD_BUZZER = src/Buzzer/Buzzer
MOD_MFRC522 = src/MFRC522/MFRC522
MOD_LED = src/LED/LED
MOD_RFID = src/RFID/RFID

##Main program name
MAIN_PROGRAM=$(BIN_DIR)/Centzoncito

HEADERS = $(MOD_GPIO_CORE).h $(MOD_EGPIO).h $(MOD_BUZZER).h $(MOD_MFRC522).h $(MOD_LED).h $(MOD_RFID).h

#Source code files of the modules
SRCS = $(MOD_GPIO_CORE).cpp $(MOD_EGPIO).cpp $(MOD_BUZZER).cpp $(MOD_MFRC522).cpp $(MOD_LED).cpp $(MOD_RFID).cpp

#Objects to be created
OBJDIR := $(LIB_DIR)
OBJS := $(addprefix $(OBJDIR)/,GPIO_core.o eGPIO.o Buzzer.o MFRC522.o LED.o RFID.o)

##Compiling all objects, using -j4 really haste it up!
$(OBJDIR)/%.o : src/*/%.cpp
	$(CC) $(CFLAGS) -c -o "$@" "$<" $(CLIBS)

##Creating main program
all: $(OBJS)
	$(MKDIR) $(BIN_DIR) 2> /dev/null
	$(CC) $(CFLAGS) test.cpp $(OBJS) -o $(MAIN_PROGRAM) $(CLIBS)

##Creating directory, | is for order-only-prerequisites
$(OBJS): | $(OBJDIR)
$(OBJDIR):
	$(MKDIR) $(LIB_DIR) 2> /dev/null

#Cleaning everything!
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	