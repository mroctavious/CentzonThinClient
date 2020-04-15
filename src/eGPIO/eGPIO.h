#ifndef GPIO_EASY
#define GPIO_EASY
#include "../GPIO_core/GPIO_core.h"
#include <string>

/*
	Higher level layer of the GPIO core class
*/
class eGPIO : GPIOClass{
public:
	//Starting GPIO file config
	eGPIO( string pin, string direction );

	//On delete, clean all configurations of the pin
	~eGPIO();

	//Sends a 1 to the pin
	void on( void );

	//Sends a 0 to the pin
	void off( void );

	//Read value in the pin
	bool read( void );

	//Resets to default
	void reset( void );


private:
	//For reading the value of the pin
	string inputstate;
};


#endif
