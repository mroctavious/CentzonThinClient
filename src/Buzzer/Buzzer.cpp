#include "Buzzer.h"
#include <string>
#include <iostream>
#include <unistd.h>

Buzzer::Buzzer( string pin ):eGPIO( pin, "w" ){
    this->current_beep = &Buzzer::okBeep;
};

void Buzzer::okBeep( void ){
    this->on();
    usleep(500000);
    this->off();
}

void Buzzer::errorBeep( void ){
    this->on();
    usleep(200000);
    this->off();
    usleep(100000);
    this->on();
    usleep(200000);
    this->off();
    usleep(100000);
    this->on();
    usleep(200000);
    this->off();
}

void Buzzer::cautionBeep( void ){
    this->on();
    usleep(400000);
    this->off();
    usleep(100000);
    this->on();
    usleep(400000);
    this->off();
}

void Buzzer::execute( void ){
    (*this.*current_beep)();
    return;
}

Buzzer::~Buzzer(){
    this->reset();
}
