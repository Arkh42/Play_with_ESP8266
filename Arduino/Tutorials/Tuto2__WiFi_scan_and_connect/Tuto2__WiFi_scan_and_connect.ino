/**
 * \file      Tuto2__WiFi_scan_and_connect.ino
 * \brief     Tutorial -- ESP8266 basics: WiFi use
 * \details   Learning ESP8266 basics: WiFi connection.
 *            A scan of available WiFi access points is done and information is displayed through Serial port.
 *            Then, ESP connects to the chosen AP.
 * \author    Alexandre QUENON
 * \date      2018-03-12
 * \copyright GNU Public License V3.0
 */


// Libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>


// Global variables
const int long serial_speed = 115200;

const char* ssid = "********";
const char* password = "********";


// Functions prototypes
void init_serial( int long baud_rate );

void config_as_station();

int scan_WiFi_access_points();
void display_param_access_point( int number );
bool WiFi_access_point_is_found( const char* ssid );


// Arduino base functions
void setup()
{
  init_serial( serial_speed );

  config_as_station();
}

void loop()
{
  auto nb_found_AP = scan_WiFi_access_points();

  Serial.println( "--List of access points --" );
  for( auto i = 0; i < nb_found_AP; ++i )
    display_param_access_point( i );
  Serial.println( "------------------------\n" );


  auto ssid_detected = false;
  for( auto i = 0; i < nb_found_AP; ++i )
  {
    if( WiFi_access_point_is_found( i ) )
    {
      ssid_detected = true;
      break;
    }
  }

  if( ssid_detected )
  {
    //
  }
  else
  {
    Serial.printf( "Access point of SSID %s has not been detected.\n", ssid );
    Serial.println( "Restart scanning in awhile...\n" );
  }
  

  delay(5000);
}


// Functions implementations
void init_serial( int long baud_rate )
{
  Serial.begin( baud_rate );
  
  Serial.print( "\nESP8266's serial communication is set at " );
  Serial.print( baud_rate );
  Serial.println( " bauds.\n" );
}

void config_as_station()
{
  WiFi.mode( WIFI_STA );
  WiFi.disconnect();

  delay( 100 );
}

int scan_WiFi_access_points()
{
  Serial.println( "Start scanning available WiFi access points..." );

  int nb_access_points = WiFi.scanNetworks();

  Serial.printf( "Scan done: %d access point(s) found.\n\n", nb_access_points);

  return nb_access_points;
}
void display_param_access_point( int number )
{
  Serial.printf( "%d: %s (%d dBm)\n", number+1, WiFi.SSID( number ).c_str(), WiFi.RSSI( number ) );
}

bool WiFi_access_point_is_found( int index_AP )
{
  return ssid == WiFi.SSID( index_AP ).c_str();
}

