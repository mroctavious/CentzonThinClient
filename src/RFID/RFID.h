#ifndef CENTZON_RFID
#define CENTZON_RFID
#include <chrono>
#include <ctime>
#include "../MFRC522/MFRC522.h"
#include <iostream>
#include <unistd.h>
#include "../Buzzer/Buzzer.h"
#include "../LED/LED.h"

/*
  Main controller of the module
      +-----------+----------+-------------+
      |           | MFRC522  | Raspberry Pi|
      +-----------+----------+-------------+
      | Signal    | Pin      | Pin         |
      +===========+==========+=============+
      | RST/Reset | RST      | 22          |
      +-----------+----------+-------------+
      | SPI SS    | SDA      | 24          |
      +-----------+----------+-------------+
      | SPI MOSI  | MOSI     | 19          |
      +-----------+----------+-------------+
      | SPI MISO  | MISO     | 21          |
      +-----------+----------+-------------+
      | SPI SCK   | SCK      | 23          |
      +-----------+----------+-------------+
      | 3V        | 3v       | 1           |
      +-----------+----------+-------------+
      | GND       | GND      | 25          |
      +-----------+----------+-------------+
     
*/
typedef enum{
        NO_CARD, //When the module has not detected a card
        NEW_CARD, //When a new card is placed
        PLACED, //When Successful login
        REMOVED, //When the user removes the card
        BLOCKED, //When the RFID card is blocked
        NOT_CENTZON, //When cannot read RFID card because it does not recognize header
        ERROR, //When anything else happens
        LENGTH //This is the last element of this enum, its kinda a "length()"
} States;

/*This class is the controller responsible of 
getting all the information from the RFID card*/
class RFID{
public:
    MFRC522 MFRC;
    States currentState;
    /*

    */
    RFID();
    ~RFID();

    //This function will get the current status of the module
    States getStatus( void );


    //This function will read the module and update the current status of the object
    void update( void );

    //This function will restart the RFID module, it is necesary...
    void reset( void );

    void delay(int ms);


private:
    //This function will set the current status of the RFID module
    void setStatus( States newState );


    //The current ID
    byte id[16];

    Buzzer *beep;
    LED *led;


    //State machine functions
    States noCard( void );
    States newCard( void );
    States placed( void );
    States removed( void );
    States blocked( void );
    States notCentzon( void );
    States error( void );

};


#endif