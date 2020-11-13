#include "ApiClient.h"

ApiClient::ApiClient(WiFiClient* wifiClient){
	this->client = wifiClient;
}
ApiClient::ApiClient(WiFiClient* wifiClient, const char* urlOrIP){
	this->client = wifiClient;
	this->connect(urlOrIP);
}

int ApiClient::GET(const char* url){
	String request= String("GET ") + url + " HTTP/1.1\n" +
					"Host: " + *this->host + "\r\n" +
					(this->authToken? ("Authorization: Basic " + *this->authToken + "\n" ):"")+
					"Cache-Control: no-cache\n" +
					"Content-Type: application/json\n" + 
					"Connection: close\n\n" ;
	Serial.println(request);
	
	//this->client->println(request);
}
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
}
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
}
int ApiClient::DELETE(const char* url){
	String request= String("DELETE ") + url + " HTTP/1.1\n" +
					"Host: " + *this->host + "\r\n" +
					(this->authToken? ("Authorization: Basic " + *this->authToken + "\n" ):"")+
					"Cache-Control: no-cache\n" +
					"Connection: close\n\n" ;
	Serial.println(request);
}
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
DynamicJsonDocument* ApiClient::getData(){
	return this->data;
}

/*###########################################
delete data from last query
############################################*/
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
