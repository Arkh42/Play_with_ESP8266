/**
 * \file      Tuto1__LED_blinking.ino
 * \brief     Tutorial -- ESP8266 basics: LED blinking
 * \details   Learning ESP8266 basics: LED, digital output (based on Arduino "Blink" example).
 *            The built-in led is used, as well as an LED connected to pin 7 of ESP8266.
 * \author    Alexandre QUENON
 * \date      2018-03-12
 * \copyright GNU Public License V3.0
 */


// Libraries
#include <Arduino.h>


// Global variables
const int pin_led_a = D7;
const int pin_led_b = LED_BUILTIN;

const unsigned half_period_led_a = 1000;
const unsigned half_period_led_b = 200;


// Functions prototypes
void make_blink( int pin, unsigned long half_period );


// Arduino base functions
void setup()
{
  pinMode( pin_led_a, OUTPUT );
  pinMode( pin_led_b, OUTPUT );
}

void loop()
{
  for( auto i = 0; i < 5; ++i )
    make_blink( pin_led_a, half_period_led_a );

  for( auto i = 0; i < 20; ++i )
    make_blink( pin_led_b, half_period_led_b );
}


// Functions implementations
void make_blink( int pin, unsigned long half_period )
{
  digitalWrite( pin, HIGH );
  delay( half_period );

  digitalWrite( pin, LOW );
  delay( half_period );
}

