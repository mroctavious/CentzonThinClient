#ifndef CENTZON_BUZZER
#define CENTZON_BUZZER
#include "../eGPIO/eGPIO.h"

/*
	Higher level layer of the GPIO core class
*/
class Buzzer : eGPIO{
public:
	//Starting GPIO file config
	Buzzer( string pin );

	//On delete, clean all configurations of the pin
	~Buzzer( void );

    void okBeep( void );
	void cautionBeep( void );
	void errorBeep( void );

    void execute( void );

private:
	void (Buzzer::*current_beep)( void );
};


#endif
