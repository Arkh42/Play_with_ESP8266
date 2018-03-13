/**
 * \file      Tuto2__WiFi_scan_and_connect.ino
 * \brief     Tutorial -- ESP8266 basics: WiFi use
 * \details   Learning ESP8266 basics: WiFi connection.
 *            A scan of available WiFi access points is done and information is displayed through Serial port.
 *            Then, ESP connects to the chosen AP if it was detected during the scan and displays information through Serial port.
 * \author    Alexandre QUENON
 * \date      2018-03-13
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
void display_param_access_point( int index_AP );
bool is_defined_WiFi_access_point( int index_AP );

void connect_to_access_point( const char* ssid_AP, const char* password_AP );
void display_param_WiFi_connection();


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
    if( is_defined_WiFi_access_point( i ) )
    {
      ssid_detected = true;
      break;
    }
  }

  if( ssid_detected )
  {
    Serial.printf( "Access point of SSID %s has been detected.\n", ssid );
    connect_to_access_point( ssid, password );
    display_param_WiFi_connection();

    while( true )// Infinite loop
    {
      delay( 10000 );
      if( WiFi.isConnected() )
        Serial.println( "WiFi connection still alive! :)" );
      else
        Serial.println( "WiFi connection is dead! :(" );
    }
  }
  else
  {
    Serial.printf( "Access point of SSID %s has not been detected.\n", ssid );
    Serial.println( "Restart scanning in awhile...\n" );
  }
  

  delay( 5000 );
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
  WiFi.mode( WIFI_STA );// mode can be: WIFI_OFF, WIFI_STA, WIFI_AP, WIFI_AP_STA
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
void display_param_access_point( int index_AP )
{
  Serial.printf( "%d: %s (%d dBm)\n", index_AP+1, WiFi.SSID( index_AP ).c_str(), WiFi.RSSI( index_AP ) );
}

bool is_defined_WiFi_access_point( int index_AP )
{
  return String( ssid ) == WiFi.SSID( index_AP );
}


void connect_to_access_point( const char* ssid_AP, const char* password_AP )
{
  Serial.printf( "Trying to connect to %s...", ssid_AP );
  
  WiFi.begin( ssid_AP, password_AP );

  while ( WiFi.status() != WL_CONNECTED ) // status() can return: WL_CONNECTED, WL_NO_SSID_AVAIL, WL_CONNECT_FAILED, WL_IDLE_STATUS, WL_DISCONNECTED
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println( "\t connected!\n" );
}

void display_param_WiFi_connection()
{
  Serial.println( "WiFi connection's parameters:" );
  
  Serial.print( "- IP address: " );
  Serial.println( WiFi.localIP() );

  Serial.print( "- MAC address: " );
  Serial.println( WiFi.macAddress() );

  Serial.print( "- subnet mask address: " );
  Serial.println( WiFi.subnetMask() );

  Serial.print( "- gateway IP address: " );
  Serial.println( WiFi.gatewayIP() );

  Serial.print( "- DNS server IP address: " );
  Serial.println( WiFi.dnsIP() );

  Serial.print( "- host name: " );
  Serial.println( WiFi.hostname() );

  Serial.print( "\n" );
}

