#include "ApiClient.h"
ApiClient::ApiClient() {}
ApiClient::ApiClient(WiFiClient* wifiClient){
	this->client = wifiClient;
}
ApiClient::ApiClient(WiFiClient* wifiClient, const char* urlOrIP){
	this->client = wifiClient;
	this->connect(urlOrIP);
}

int ApiClient::GET(const char*){}
int ApiClient::POST(const char*, DynamicJsonDocument*){}
int ApiClient::PUT(const char*, DynamicJsonDocument*){}
int ApiClient::DELETE(const char*){}
int ApiClient::PATCH(const char*, DynamicJsonDocument*){}

void ApiClient::setAuthentication(const char*){}
DynamicJsonDocument* ApiClient::getData(){}
void ApiClient::clear(){}

/*###########################################
SUCCESS 1
TIMED_OUT -1
INVALID_SERVER -2
TRUNCATED -3
INVALID_RESPONSE -4 
############################################*/
int ApiClient::connect(const char* urlOrIP){
	return this->client->connect(this->urlOrIP->c_str(), 80);
}
void ApiClient::disconnet(){
	this->client->stop();
}

bool ApiClient::isConnected(){
	return this->client->connected();
}


ApiClient::~ApiClient(){

}
