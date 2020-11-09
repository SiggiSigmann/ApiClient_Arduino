#include <Client.h>
#include <ArduinoJson.h>

class ApiClient{
  private:
    
  public:
    ApiClient(const char*);

	int GET(const char*);
	int POST(const char*, ArduinoJson);
	int PUT(const char*, ArduinoJson);
	int DELETE(const char*);
	int PATCH(const char*, ArduinoJson);

	ArduinoJson getData();

	void setAuthentication(const char*);


	void clear();
	void connected();
	void disconnet();

	~ApiClient();

};
