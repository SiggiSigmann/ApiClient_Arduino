#include <Client.h>
#include <ArduinoJson.h>

class ApiClient{
  private:
    
  public:
    ApiClient(const char*);
	ApiClient(Client*);

	int GET(const char*);
	int POST(const char*, DynamicJsonDocument*);
	int PUT(const char*, DynamicJsonDocument*);
	int DELETE(const char*);
	int PATCH(const char*, DynamicJsonDocument*);

	DynamicJsonDocument getData();

	void setAuthentication(const char*);


	void clear();
	void isConnected();
	void disconnet();

	~ApiClient();

};
