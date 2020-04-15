#include "eGPIO.h"
#include <string>
#include <iostream>

eGPIO::eGPIO( string pin, string direction ):GPIOClass( pin ){
	//Create the file for the specified gpio pin
	this->export_gpio();

	if( direction.compare("r") == 0 )
	{
		//std::cout << "Reading" << std::endl;
		this->setdir_gpio("in");
	}
	else if ( direction.compare("w") == 0 )
	{
		//std::cout << "Writing" << std::endl;
		this->setdir_gpio("out");
		this->setval_gpio("0");
	}
	else{
		std::cout << "Error in parameter 2. Only ''w'' or ''r'' available.\nReading only...\n";
	}
};

eGPIO::~eGPIO(){
	this->reset();
}

void eGPIO::on(){
	this->setval_gpio("1");
	return;
}

void eGPIO::off(){
	this->setval_gpio("0");
	return;
}

void eGPIO::reset(){
	this->setval_gpio("0");
	this->unexport_gpio();
	return;
}

bool eGPIO::read(){
	this->getval_gpio(this->inputstate);
	return this->inputstate == "1" ? true:false;
}