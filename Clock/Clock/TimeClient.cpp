#include "TimeClient.h"

TimeClient::TimeClient(int UTC) {
	myUTC = UTC;
}

void updateTime() {
	WiFiClient client;
	const int httpPort = 80;
	if (!client.connect("www.google.com", httpPort)) {
		Serial.println("connection failed");
		return;
	}

	//HTTP request
	client.print(String("GET / HTTP/1.1\r\n") +
		String("Host: www.google.com\r\n") +
		String("Connection: close\r\n\r\n"));
	int repeatCounter = 0;
	while (!client.available() && repeatCounter < 10) {
		delay(1000);
		Serial.println(".");
		repeatCounter++;
	}

	String line;

	int size = 0;
	client.setNoDelay(false);
	while (client.connected()) {
		while ((size = client.available()) > 0) {
			line = client.readStringUntil('\n');
			line.toUpperCase(); //대문자로 변경
			// example: 
			// date: Thu, 19 Nov 2015 20:25:40 GMT
			if (line.startsWith("DATE: ")) {
				Serial.println(line.substring(23, 25) + ":" + line.substring(26, 28) + ":" + line.substring(29, 31));
				int parsedHours = line.substring(23, 25).toInt();
				int parsedMinutes = line.substring(26, 28).toInt();
				int parsedSeconds = line.substring(29, 31).toInt();
				Serial.println(String(parsedHours) + ":" + String(parsedMinutes) + ":" + String(parsedSeconds));

				Epoch = (parsedHours * 60 * 60 + parsedMinutes * 60 + parsedSeconds);
				Serial.println(Epoch);
				localMillisAtUpdate = millis();
			}
		}
	}
}

String getHours() {

}

String getMinutes() {

}

String getSeconds() {


}