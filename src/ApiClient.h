#include "heltec.h"
#include <ArduinoJson.h>
#include <Wifi.h>
#include <client.h>


class ApiClient{
  private:
	Client* client = NULL;
	DynamicJsonDocument* data = NULL;
	String* host = NULL;
	String* authToken = NULL;

	void parseResult();
    
  public:
	ApiClient(WiFiClient*);
	ApiClient(WiFiClient*, const char*);

	int GET(const char*);
	int POST(const char*, DynamicJsonDocument*);
	int POST(const char*, String);
	int PUT(const char*, DynamicJsonDocument*);
	int DELETE(const char*);
	int PATCH(const char*, DynamicJsonDocument*);

	void setAuthentication(const char*);
	DynamicJsonDocument* getData();
	void clear();

	int connect(const char* urlOrIP);
	int connect(const char* urlOrIP, const int port);
	void disconnet();
	bool isConnected();
	
	~ApiClient();
};
