#include "ApiClient.h"

ApiClient::ApiClient(WiFiClient* wifiClient){
	this->client = wifiClient;
}
ApiClient::ApiClient(WiFiClient* wifiClient, const char* urlOrIP){
	this->client = wifiClient;
	this->connect(urlOrIP);
}

//todo errorhandling
void ApiClient::parseResult(){
	if(this->data){
		delete this->data;
	}
	this->data = new DynamicJsonDocument(2048);

	String resp;
	char c;
	bool isBody=false;
	while(this->client->available()) {	
    	c = this->client->read();
		
		if (c == '{' || c == '[') {
			isBody = true;
			}
			if (isBody) {
				resp += c;
				Serial.print(c);
			} else {
				Serial.print(c);
			}
  	}

	// Parse JSON object
	DeserializationError error = deserializeJson(*this->data, resp);
	if (error) {
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.f_str());
	}
	
}
//untested
int ApiClient::GET(const char* url){
	String request= String("GET ") + url + " HTTP/1.1\n" +
					"Host: " + *this->host + "\r\n" +
					(this->authToken? ("Authorization: Basic " + *this->authToken + "\n" ):"")+
					"Cache-Control: no-cache\n" +
					"Content-Type: application/json\n" + 
					"Connection: close\n\n" ;
	//Serial.println(request);
	return 0;
	//this->client->println(request);
}
//untested
int ApiClient::POST(const char* url, DynamicJsonDocument* payload){
	String strPayload;
	serializeJson(*payload, strPayload);
	String request= String("POST ") + url + " HTTP/1.1\n" +
					"Host: " + *this->host + "\r\n" +
					(this->authToken? ("Authorization: Basic " + *this->authToken + "\n" ):"")+
					"Cache-Control: no-cache\n" +
					"Content-Type: application/json\n" + 
					strPayload + "\n" +
					"Connection: close\n\n" ;
	Serial.println(request);
	return 0;
}

//todo: errorhandling
int ApiClient::POST(const char* url, String payload){
	String request= String("POST ") + url + " HTTP/1.1\n"
					+ "Host: " + *this->host + "\n"
					+ (this->authToken? ("Authorization: Basic " + *this->authToken + "\n" ):"")
					+ "Cache-Control: no-cache\n"
					+ "Content-Length: " + String(payload.length()) + "\n"
					+ "Content-Type: application/x-www-form-urlencoded\n"
					+ "Connection: close\n\n" 
					+ payload;
	this->client->print(request);

	//wait vor answere
	while(!this->client->available()) {	
    	delay(10);
  	}

	this->parseResult();

	return 0;
}
//untested
int ApiClient::PUT(const char* url, DynamicJsonDocument* payload){
	String strPayload;
	serializeJson(*payload, strPayload);
	String request= String("PUT ") + url + " HTTP/1.1\n" +
					"Host: " + *this->host + "\r\n" +
					(this->authToken? ("Authorization: Basic " + *this->authToken + "\n" ):"")+
					"Cache-Control: no-cache\n" +
					"Content-Type: application/json\n" + 
					strPayload + "\n" +
					"Connection: close\n\n" ;
	Serial.println(request);
	return 0;
}
//untested
int ApiClient::DELETE(const char* url){
	String request= String("DELETE ") + url + " HTTP/1.1\n" +
					"Host: " + *this->host + "\r\n" +
					(this->authToken? ("Authorization: Basic " + *this->authToken + "\n" ):"")+
					"Cache-Control: no-cache\n" +
					"Connection: close\n\n" ;
	Serial.println(request);
	return 0;
}
//untested
int ApiClient::PATCH(const char* url, DynamicJsonDocument* payload){
	String strPayload;
	serializeJson(*payload, strPayload);
	String request= String("PUT ") + url + " HTTP/1.1\n" +
					"Host: " + *this->host + "\r\n" +
					//"Authorization: Basic " + authorization + "\n" +
					"Cache-Control: no-cache\n" +
					"Content-Type: application/json\n" + 
					strPayload + "\n" +
					"Connection: close\n\n" ;
	Serial.println(request);
	return 0;
}


void ApiClient::setAuthentication(const char* token){

	if(this->authToken){
		Serial.println("error");
		delete this->authToken;
	}
	this->authToken = new String(token);
}

/*###########################################
return data
############################################*/
//untested
DynamicJsonDocument* ApiClient::getData(){
	return this->data;
}

/*###########################################
delete data from last query
############################################*/
//untested
void ApiClient::clear(){
	if(this->data){
		delete this->data;
	}
}

/*###########################################
connect to API server
SUCCESS 1
TIMED_OUT -1
INVALID_SERVER -2
TRUNCATED -3
INVALID_RESPONSE -4 
############################################*/
int ApiClient::connect(const char* urlOrIP){
	if(this->host){
		delete this->host;
	}
	this->host = new String(urlOrIP);
	return this->client->connect(urlOrIP, 80);
}

int ApiClient::connect(const char* urlOrIP, const int port){
	if(this->host){
		delete this->host;
	}
	this->host = new String(urlOrIP);
	return this->client->connect(urlOrIP, port);
}
/*###########################################
disconect from API server
############################################*/
void ApiClient::disconnet(){
	this->client->stop();
}

/*###########################################
return if connected
############################################*/
bool ApiClient::isConnected(){
	return this->client->connected();
}

ApiClient::~ApiClient(){
	if(this->data){
		delete this->data;
	}
	if(this->host){
		delete this->host;
	}
}
