#include <string>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "secrets.h"

// getVCC returns in milllivolts, around 2.5VCC seems to be good enough
#define LOW_BATTERY (2500)
#define MQTT_CLIENT_SUBJECT ("subject")

ADC_MODE(ADC_VCC)

const String client_id = "ESP8266-" + WiFi.macAddress();
WiFiClient wifi_conn;
PubSubClient mqtt(wifi_conn);
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
	mqtt.setServer(MQTT_SERVER, MQTT_PORT);
	mqtt.connect(client_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD);
	Serial.print("Client state ");
	Serial.println(mqtt.state());
	Serial.print("Publishing to server: ");
	String data(ESP.getVcc());
	Serial.println(mqtt.publish(MQTT_CLIENT_SUBJECT, data.c_str()));
	
}

void loop()
{
	//ESP.deepSleep(ESP.deepSleepMax(), RF_DISABLED);
}
