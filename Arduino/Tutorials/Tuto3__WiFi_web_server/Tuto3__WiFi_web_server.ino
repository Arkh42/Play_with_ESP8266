/**
 * \file      Tuto3__WiFi_web_server.ino
 * \brief     Tutorial -- ESP8266 WiFi WEB server
 * \details   Learning ESP8266 features: WiFi WEB server.
 *            ESP connects to an existing Access Point (AP) to receive an IP address and send it through serial port.
 *            Then, ESP starts a WEB server which can be used to interact with LEDs or any circuitry.
 * \author    Alexandre QUENON
 * \date      2018-03-29
 * \copyright GNU Public License V3.0
 */


// Libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


// Global variables
const int long serial_speed = 115200;

const char* ssid = "********";
const char* password = "********";

const int led = D7;
const int led_graph = D8;

ESP8266WebServer server(80);


// Functions prototypes
void init_serial( int long baud_rate );

void config_as_station();

void connect_to_access_point( const char* ssid_AP, const char* password_AP );
void display_param_WiFi_connection();

void handleRoot();
void handleNotFound();
void handleLed();
void handleGraphLed();

String getHtmlPage();


// Arduino base functions
void setup()
{
  pinMode( led, OUTPUT );
  digitalWrite( led, LOW );

  pinMode( led_graph, OUTPUT );
  digitalWrite( led_graph, LOW );

  
  init_serial( serial_speed );

  config_as_station();
  connect_to_access_point( ssid, password );
  display_param_WiFi_connection();


  server.on( "/", handleRoot );
  server.on( "/inline", [](){ server.send(200, "text/plain", "this works as well"); } );
  server.on( "/gpio", handleLed );
  server.on( "/graph", handleGraphLed );
  server.on( "/graphON", [](){ 
    server.send( 200, "text/html", getHtmlPage() );
    digitalWrite( led_graph, HIGH );
  } );
  server.on( "/graphOFF", [](){ 
    server.send( 200, "text/html", getHtmlPage() );
    digitalWrite( led_graph, LOW );
  } );
  server.onNotFound( handleNotFound );

  server.begin();
  Serial.println( "HTTP server started.\n" );
}

void loop()
{
  server.handleClient();
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


void handleRoot()
{
  server.send(200, "text/plain", "Hello from esp8266!");
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  
  message += "URI: ";
  message += server.uri();
  
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  
  for( auto i = 0; i < server.args(); ++i )
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    
  server.send(404, "text/plain", message);
}

void handleLed()
{
  if( server.hasArg( "val" ) )
  {
    auto val = server.arg( "val" ).toInt();
    if( val == 0  ||  val == 1 )
    {
      String html_page = "<!DOCTYPE html><html lang=en-UK>";
      html_page       += "  <head>";
      html_page       += "    <meta http-equiv='refresh' content='5'/>";
      html_page       += "    <title>ESP8266 Demo from Arkh42</title>";
      html_page       += "  </head>";
      html_page       += "  <body>";
      html_page       += "    <hl>ESP8266 is now under your control...</hl>";
      html_page       += "    <p>GPIO ";
      html_page       +=              String( led );
      html_page       +=                          " is ";
      html_page       +=                                (val) ? "high" : "low";
      html_page       +=                                                      ".</p>";
      html_page       += "  </body>";
      html_page       += "</html>";
      (val) ? digitalWrite( led, HIGH ) : digitalWrite( led, LOW );
      server.send( 200, "text/html", html_page );
    }
    else
      server.send(200, "text/plain", "Bad argument value! Valid values are: 0, 1");
  }
  else
    server.send(200, "text/plain", "Bad argument name! Valid argument is: val");
}


void handleGraphLed()
{
  if( server.arg( "val" ) == "off" )
  {
    digitalWrite( led_graph, LOW );
    server.send ( 200, "text/html", getHtmlPage() );
  }
  else if( server.arg( "val" ) == "on" )
  {
    digitalWrite( led_graph, HIGH );
    server.send ( 200, "text/html", getHtmlPage() );
  }
  else
    server.send ( 200, "text/html", getHtmlPage() );
}


String getHtmlPage()
{
  String html_page = "<!DOCTYPE html><html lang=en-UK>";
  html_page       += "  <head>";
  html_page       += "    <meta http-equiv='refresh' content='5'/>";
  html_page       += "    <title>ESP8266 Demo from Arkh42</title>";
  html_page       += "  </head>";
  html_page       += "  <body>";
  html_page       += "    <hl>ESP8266 is now under your control...</hl>";
  html_page       += "    <p>GPIO ";
  html_page       +=                String( led_graph );
  html_page       +=                                    "<a href=\"graphON\"><button>ON</button></a>&nbsp;<a href=\"graphOFF\"><button>OFF</button></a></p>";
  html_page       += "  </body>";
  html_page       += "</html>";

  return html_page;
}

