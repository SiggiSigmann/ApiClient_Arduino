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

	int parseResult();
    
  public:
	ApiClient(WiFiClient*);
	ApiClient(WiFiClient*, String);

	int GET(String);
	int POST(String, DynamicJsonDocument*);
	int POST(String, String);
	int PUT(String, DynamicJsonDocument*);
	int DELETE(String);
	int PATCH(String, DynamicJsonDocument*);

	void setAuthentication(String);
	DynamicJsonDocument* getData();
	void clear();

	int connect(String urlOrIP);
	int connect(String urlOrIP, const int port);
	void disconnet();
	bool isConnected();
	
	~ApiClient();
};
