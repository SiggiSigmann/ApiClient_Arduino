#include "ApiClient.h"

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

void ApiClient::setAuthentication(const char*){

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
}
