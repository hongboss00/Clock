#include <ESP8266WiFi.h>

class TimeClient {

private:
	int myUTC = 0;

	long myEpoch = 0;
	long Epoch = 0;



public:

	TimeClient(int myUTC); 
	void updateTime();

	String getHours();
	String getMinutes();
	String getSeconds();
	long getCurrentEpoch();
	long getCurrentEpochWithUtcOffset();

};

