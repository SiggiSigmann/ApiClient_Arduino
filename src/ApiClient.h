#include "heltec.h"
#include <ArduinoJson.h>
#include <Wifi.h>
#include <client.h>


class ApiClient{
  private:
	Client* client;
    
  public:
  	ApiClient();
	ApiClient(WiFiClient*);
	ApiClient(WiFiClient*, const char*);

	int GET(const char*);
	int POST(const char*, DynamicJsonDocument*);
	int PUT(const char*, DynamicJsonDocument*);
	int DELETE(const char*);
	int PATCH(const char*, DynamicJsonDocument*);

	void setAuthentication(const char*);
	DynamicJsonDocument* getData();
	void clear();

	int connect(const char* urlOrIP);
	void disconnet();
	bool isConnected();
	
	~ApiClient();
};
