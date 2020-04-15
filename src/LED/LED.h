#ifndef CENTZON_LED
#define CENTZON_LED

#include <wiringPi.h>
#include <softPwm.h>
#include <vector>
#include <string.h>

/*This Module will control the RGB Led indicating the current status of the RFID*/
class LED {
public:
    //Create object with the selected pins
    LED( unsigned char red_pin, unsigned char green_pin, unsigned char blue_pin );
    ~LED();
    
    //Structura de color
    struct Color{
        const char *name;
        unsigned char r;
        unsigned char g;
        unsigned char b;
    };

    std::vector<Color> colors;

    //Current color of the led
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    //Pins to connected to the color
    unsigned char pin_red;
    unsigned char pin_green;
    unsigned char pin_blue;

    //Changing the color of the led
    void setColor( unsigned char r, unsigned char g, unsigned char b );
    void setColor( const char *color );

    //Change color with the current values of the object
    void colorChange( void );

    //Change color given a RGB code
    void colorChange( unsigned char r, unsigned char g, unsigned char b );

    //Change color given a Color struct
    void colorChange( Color );

    void reset( void );


};

#endif