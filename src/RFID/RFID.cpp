#include "RFID.h"

RFID::RFID(){
    this->MFRC.PCD_Init();
    this->currentState = NO_CARD;
    this->beep = new Buzzer("4");
    this->led = new LED(25,28,29);
}

RFID::~RFID(){
    delete this->beep;
    delete this->led;
}

States RFID::noCard( void ){
    if( ! this->MFRC.PICC_IsNewCardPresent()){
        return NO_CARD;
    }
    if( !this->MFRC.PICC_ReadCardSerial()){
        return NO_CARD;
    }
    for( unsigned char i = 0; i < this->MFRC.uid.size; ++i){
      if( this->MFRC.uid.uidByte[i] < 0x10){
        printf(" 0");
        printf("%X",this->MFRC.uid.uidByte[i]);
      }
      else{
        printf(" ");
        printf("%X", this->MFRC.uid.uidByte[i]);
      }   
    }
    this->beep->okBeep();
    this->led->setColor("green");
    return NEW_CARD;
}
States RFID::newCard( void ){
    //if( ){

    //} //OK_Header,
    return NEW_CARD;
}
States RFID::placed( void ){
    return NEW_CARD;
}
States RFID::removed( void ){
    return NEW_CARD;
}
States RFID::blocked( void ){
    return NEW_CARD;
}
States RFID::notCentzon( void ){
    return NEW_CARD;
}
States RFID::error( void ){
    return NEW_CARD;
}

//This function will set the current status of the RFID module
void RFID::setStatus( States newState ){
    this->currentState=newState;
}

//This function will get the current status of the module
States RFID::getStatus( void ){
    return this->currentState;
}

//This function will read the module and update the current status of the object
void RFID::update( void ){
    std::cout << "Current Status: " << NO_CARD << std::endl;
    this->reset();
    switch(this->currentState){
        case NO_CARD :
            this->currentState = noCard();
            break;

        case NEW_CARD :
            this->currentState = NO_CARD;


        break;
        //case PLACED  : std::cout << "azul\n";  break;
        //case REMOVED : std::cout << "verde\n"; break;
        //case BLOCKED  : std::cout << "azul\n";  break;
        //case NOT_CENTZON : std::cout << "verde\n"; break;
        //case ERROR  : std::cout << "azul\n";  break;
    }

}

void RFID::delay(int ms){
  usleep(ms*1000);
}

//This function will restart the RFID module, it is necesary...
void RFID::reset( void ){
    this->MFRC.PCD_Reset();
    this->MFRC.PCD_Init();
    this->delay(70);
}

