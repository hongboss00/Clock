#include "TimeClient.h"

TimeClient::TimeClient(int UTC) {
	myUTC = UTC;
}

void TimeClient::updateTime() {
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

	Serial.println("Updating Successful");

	String line;

	int size = 0;
	client.setNoDelay(false);
	while (client.connected()) {
		while ((size = client.available()) > 0) {
			line = client.readStringUntil('\n');
			line.toUpperCase(); 
			// example: 
			if (line.startsWith("DATE: ")) {
				Serial.println(line.substring(23, 25) + ":" + line.substring(26, 28) + ":" + line.substring(29, 31));
				int parsedHours = line.substring(23, 25).toInt();
				int parsedMinutes = line.substring(26, 28).toInt();
				int parsedSeconds = line.substring(29, 31).toInt();
				Serial.println(String(parsedHours) + ":" + String(parsedMinutes) + ":" + String(parsedSeconds));

				Epoch = (parsedHours * 60 * 60 + parsedMinutes * 60 + parsedSeconds);
				Serial.println(Epoch);
				Serial.println(Epoch);
				lastMillis = millis();
			}
		}
	}
}

String TimeClient::getHours() {
	int hours = ((getCurrentEpochWithUtc() % 86400) / 3600) % 24;
	if (hours < 10) {
		return "0" + String(hours);
	}
	return String(hours);
}

String TimeClient::getMinutes() {
	int minutes = ((getCurrentEpochWithUtc() % 3600) / 60);
	if (minutes < 10) {
		return "0" + String(minutes);
	}
 return String(minutes);
}

String TimeClient::getSeconds() {
	int seconds = getCurrentEpochWithUtc() % 60;
	if (seconds < 10) {
		return "0" + String(seconds);
	}
	return String(seconds);
}

long TimeClient::getCurrentEpoch() {

	return Epoch + (millis() - lastMillis) / 1000;

}

long TimeClient::getCurrentEpochWithUtc() {
	return round(getCurrentEpoch() + 3600 * myUTC + 86400L) % 86400L;
}
