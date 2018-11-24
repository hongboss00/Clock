#include "TimeClient.h"
#include <ESP8266WiFi.h>
#include "ssd1306_i2c.h"
#include "font.h"

#define UTC_offset 9
#define I2C 0x3c
#define SDA D6
#define SCL D7
#define BTN_1 D5
#define BTN_2 D1

TimeClient timeclient(UTC_offset);
SSD1306 display(I2C, SDA, SCL);

char SSID[] = "Home";
char PASS[] = "";

boolean readyForUpdate = true;

void setup() {
	Serial.begin(115200);
	display.init();
	display.clear();
  display.flipScreenVertically();

}

void loop() {

	if (readyForUpdate) {
		if (WiFi.status() != WL_CONNECTED) {
			wificonnect();
		}
		if (WiFi.status() == WL_CONNECTED) {
			Serial.println('connected!');
      display.clear();
      display.display();
			timeclient.updateTime();
			readyForUpdate = false;
		}
	}
 
	drawClock(0,0);
}

void drawClock(int x,int y) {

	String A_PM = "AM";

	if (atoi(timeclient.getHours().c_str()) > 11) {
		A_PM = "PM";
	}
	else A_PM = "AM";

	display.clear();
	display.setFontScale2x2(true);
	display.drawString(18 + x, 23 + y, timeclient.getHours() + ":" + timeclient.getMinutes());
	display.setFontScale2x2(false);
	display.drawString(99 + x, 20 + y, A_PM);
	display.drawString(99 + x, 30 + y, timeclient.getSeconds());
	display.display();
	
}

void wificonnect() {

	WiFi.begin(SSID, PASS);

	int counter = 0;

	while (WiFi.status() != WL_CONNECTED) {
    delay(500);
		Serial.print('.');
    display.clear();
		drawSpinner(4, counter % 4);
    display.display();

    counter ++;
	}
}

void drawSpinner(int count, int active) {
	for (int i = 0; i < count; i++) {
		const char *xbm;
		if (active == i) {
			xbm = active_bits;
		} else {
			xbm = inactive_bits;
		}
		display.drawXbm(64 - (12 * count / 2) + 12 * i, 30, 8, 8, xbm);
	}
}
