#include "TimeClient.h"
#include <ESP8266WiFi.h>

TimeClient timeclient(9);

void setup() {
	Serial.begin(11500);

	if (WiFi.status != WL_CONNECTED) {
		timeclient.updateTime();
	}




}


void loop() {
 
}
