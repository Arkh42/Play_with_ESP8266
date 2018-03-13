# Tutorial 2: WiFi scan and connection



## Aims

The aims of this tutorial consist in:
* learning the WiFi bases with the ESP8266 microcontroller;
* sending information about WiFi through the serial port;
* discovering a few C++11 features.



## Tools

The current tutorial has been done under the Arduino IDE environment.



## ESP8266 WiFi bases

### The ESP8266WiFi library

On of the libraries which is used the most to code the ESP8266 with the Arduino "language" is the *ESP8266WiFi* library.
To start using it:

	#include <ESP8266WiFi.h>
	

### Initialisation of serial communication

In order to send data through the serial port, serial communication must be initialised.
This is really easy with Arduino language: `Serial.begin( int long )`.
Initialisation is performed in the `setup()` function, as it must be done only once.

Some advices for good practice:
1. create an initilisation function, especially if you wan to pass some information at serial initilisation (cf. `void init_serial( int long baud_rate )`);
2. use a constant global variable to define the communication speed at one line to improve maintainability (cf. `const int long serial_speed`).


### WiFi scan

Scan of available WiFi access points.


### WiFi connection

Connection to the chosen WiFi access point if it has been detected by prior scan.

**Possible issues**:
* infinite loop when trying to connect because we only go out of the `while` if the `WL_CONNECTED` status is returned.

	
### C++11 features

#### The `auto` type

**Auto-typing** is an interesting feature of *modern C++*.
By declaring a variable `auto`, C++ will derive the variable type automatically for its initialisation.

Pros:
* level of abstraction is raised, which is the philosophy of C++;
* subtle mistakes can be avoided, especially when going through containers.

Cons:
* auto-type deduction mechanism must be well understood;
* "shocking", especially for people who follow the C mind spirit.



## References

References for WiFi scan:
* https://arduino-esp8266.readthedocs.io/en/2.4.1/esp8266wifi/scan-class.html
* https://arduino-esp8266.readthedocs.io/en/2.4.1/esp8266wifi/scan-examples.html
* https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/examples/WiFiScan

References for Wifi connection:
* https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/examples/WiFiClient