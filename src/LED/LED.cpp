#include "LED.h"

LED::LED(unsigned char red_pin, unsigned char green_pin, unsigned char blue_pin){
    //Activate WiringPi library
    wiringPiSetup ();

    //Setting the led pins
    this->pin_red=red_pin;
    this->pin_green=green_pin;
    this->pin_blue=blue_pin;

    //Turning on the LED pins
    softPwmCreate(this->pin_red, 0, 256);
    softPwmCreate(this->pin_green, 0, 256);
    softPwmCreate(this->pin_blue, 0, 256);

    //Creating default colors
    Color green_color = { "green", 72, 186, 0 };
    Color yellow_color = { "yellow", 246, 238, 33 };
    Color red_color = { "red", 220, 19, 18 };

    //Default colors
    colors.push_back(green_color);
    colors.push_back(yellow_color);
    colors.push_back(red_color);
}

LED::~LED( void ){
    this->reset();
}

void LED::reset( void ){
    //Default values of the led, all turned off
    this->red=0;
    this->green=0;
    this->blue=0;
    colorChange();
}

void LED::colorChange( void ){
    //Changing the color of the led
    softPwmWrite(this->pin_red, this->red);
    softPwmWrite(this->pin_green, this->green);
    softPwmWrite(this->pin_blue, this->blue);
}

void LED::colorChange( unsigned char r, unsigned char g, unsigned char b ){
    setColor( r, g, b );
    colorChange();
}

void LED::colorChange( Color newColor ){
    colorChange( newColor.r, newColor.g, newColor.b );
}

void LED::setColor( unsigned char r, unsigned char g, unsigned char b ){
    this->red=r;
    this->green=g;
    this->blue=b;
}

void LED::setColor( const char *newColorName ){
    //We are gonna lookup for the newColorName arg in the vector if exists
    std::vector<Color>::iterator ptr; 
    for (ptr = colors.begin(); ptr < colors.end(); ptr++){
        if( strcmp(ptr->name, newColorName) == 0 )
            return colorChange(ptr->r, ptr->g, ptr->b);
    }
    return setColor("red");
}
