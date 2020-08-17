#include <ESP8266WiFi.h>
#include "RestClient.h"
#include "DHT.h"

const char *ssid =  "MiFibra-F2FE";     // replace with your wifi ssid and wpa2 key
const char *pass =  "G4hp7ngJ";

const int DHTPin = 5;
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPin, DHTTYPE);

WiFiClient client;
RestClient rClient = RestClient("192.168.1.9", 9001);
 
void setup() 
{
    Serial.begin(9600);
    delay(10);
           
    Serial.println("Connecting to ");
    Serial.println(ssid); 
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass); 
    while (WiFi.status() != WL_CONNECTED) 
      {
        delay(500);
        Serial.print(".");
      }
    Serial.println("");
    Serial.println("WiFi connected"); 
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());

    dht.begin();
    
}

String response;
String body;
void loop() 
{      
    
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.println();

    body = "DATA=";
    body.concat(t);
    body.concat(',');
    body.concat(h);
    char bodyData[body.length()];
    body.toCharArray(bodyData, body.length());

    response = "";
    int statusCode = rClient.post("/temp", bodyData, &response);
    Serial.print("Status code from server: ");
    Serial.println(statusCode);
    Serial.print("Response body from server: ");
    Serial.println(response);
    delay(1500);
}
