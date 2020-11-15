#include "ApiClient.h"

ApiClient::ApiClient(WiFiClient* wifiClient){
	this->client = wifiClient;
}
ApiClient::ApiClient(WiFiClient* wifiClient, String urlOrIP){
	this->client = wifiClient;
	this->connect(urlOrIP);
}

//todo errorhandling
int ApiClient::parseResult(){
	Serial.println("parseResult");
	if(this->data){
		delete this->data;
		Serial.println("renew data");
	}
	this->data = new DynamicJsonDocument(2048);

	uint16_t bufLen = 1024;
	unsigned char buf[bufLen];
	boolean isBody = false;
	char c = ' ';
	String resp; 

	uint16_t size = 0;
	// while(client.connected()) {
	uint16_t httpCode = 0;
	Serial.println("startpars");
	while(this->client->available()) {
		while((size = this->client->available()) > 0) {
			if (isBody) {
				uint16_t len = min(bufLen, size);
				c = this->client->readBytes(buf, len);
				for (uint16_t i = 0; i < len; i++) {
					resp += (char)buf[i];
				}
			} else {
				String line = this->client->readStringUntil('\r');
				Serial.println(line);
				if (line.startsWith("HTTP/1.")) {
					httpCode = line.substring(9, line.indexOf(' ', 9)).toInt();
					Serial.printf("HTTP Code: %d\n", httpCode); 
				}
				if (line == "\r" || line == "\n" || line == "") {
					Serial.println("Body starts now");
					isBody = true;
				}
			}
		}
	}

	if (httpCode == 204) {
		//no resource found
		
		return 204;
	}

	Serial.println(resp);
	// Parse JSON object
	DeserializationError error = deserializeJson(*this->data, resp);
	if (error) {
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.f_str());
	}
	return 200;
}

int ApiClient::GET(String url){
	String request= String("GET ") + url + " HTTP/1.1\n" +
					"Host: " + *this->host + "\n" +
					(this->authToken? ("Authorization: " + *this->authToken + "\n" ):"")+
					"Content-Length: 0\n" +
					"Connection: close\n\n" ;
	Serial.println(request);
	this->client->println(request);
	
	while(!this->client->available()) {	
    	delay(10);
  	}
	Serial.println("ansere");

	this->parseResult();

	return 0;
}
/*
//untested
int ApiClient::POST(String url, DynamicJsonDocument* payload){
	String strPayload;
	serializeJson(*payload, strPayload);
	String request= String("POST ") + url + " HTTP/1.1\n" +
					"Host: " + *this->host + "\r\n" +
					(this->authToken? ("Authorization:" + *this->authToken + "\n" ):"")+
					"Cache-Control: no-cache\n" +
					"Content-Type: application/json\n" + 
					strPayload + "\n" +
					"Connection: close\n\n" ;
	Serial.println(request);
	return 0;
}*/

//todo: errorhandling
int ApiClient::POST(String url, String payload){
	String request= String("POST ") + url + " HTTP/1.1\n"
					+ "Host: " + *this->host + "\n"
					+ (this->authToken? ("Authorization: " + *this->authToken + "\n" ):"")
					+ "Content-Length: " + String(payload.length()) + "\n"
					+ "Content-Type: application/x-www-form-urlencoded\n"
					+ "Connection: close\n\n" 
					+ payload;
	this->client->print(request);
	Serial.println(request);
	//wait vor answere
	while(!this->client->available()) {	
    	delay(10);
  	}

	this->parseResult();

	return 0;
}

/*
//untested
int ApiClient::PUT(String url, DynamicJsonDocument* payload){
	String strPayload;
	serializeJson(*payload, strPayload);
	String request= String("PUT ") + url + " HTTP/1.1\n" +
					"Host: " + *this->host + "\r\n" +
					(this->authToken? ("Authorization: " + *this->authToken + "\n" ):"")+
					"Cache-Control: no-cache\n" +
					"Content-Type: application/json\n" + 
					strPayload + "\n" +
					"Connection: close\n\n" ;
	Serial.println(request);
	return 0;
}
//untested
int ApiClient::DELETE(String url){
	String request= String("DELETE ") + url + " HTTP/1.1\n" +
					"Host: " + *this->host + "\r\n" +
					(this->authToken? ("Authorization: Basic " + *this->authToken + "\n" ):"")+
					"Cache-Control: no-cache\n" +
					"Connection: close\n\n" ;
	Serial.println(request);
	return 0;
}
//untested
int ApiClient::PATCH(String url, DynamicJsonDocument* payload){
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
}*/


void ApiClient::setAuthentication(String token){

	if(this->authToken){
		delete this->authToken;
	}
	this->authToken = new String(token);
}

/*###########################################
return data
############################################*/

DynamicJsonDocument* ApiClient::getData(){
	return this->data;
}

/*###########################################
delete data from last query
############################################*/
//untested
/*
void ApiClient::clear(){
	if(this->data){
		delete this->data;
	}
}*/

/*###########################################
connect to API server
SUCCESS 1
TIMED_OUT -1
INVALID_SERVER -2
TRUNCATED -3
INVALID_RESPONSE -4 
############################################*/
int ApiClient::connect(String urlOrIP){
	if(this->host){
		delete this->host;
	}
	this->host = new String(urlOrIP);
	return this->client->connect(urlOrIP.c_str(), 80);
}

int ApiClient::connect(String urlOrIP, const int port){
	if(this->host){
		delete this->host;
	}
	this->host = new String(urlOrIP);
	return this->client->connect(urlOrIP.c_str(), port);
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
