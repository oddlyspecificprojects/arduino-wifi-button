#include <string>

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "secrets.h"

std::string request = "POST /trigger/" IFTTT_EVENT_NAME "/json/with/key/" IFTTT_KEY " HTTP/1.1\r\nHost: maker.ifttt.com\r\n\r\n";

void setup()
{
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(F("."));
	}
	Serial.println(WiFi.localIP());
	WiFiClient client;
	Serial.println(client.connect("maker.ifttt.com", 80));
	Serial.println(client.print(request.c_str()));
	Serial.println(client.readString());
}

void loop()
{

}
