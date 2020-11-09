#include "ApiClient.h"
ApiClient::ApiClient() {}
ApiClient::ApiClient(WiFiClient*){}
ApiClient::ApiClient(WiFiClient*, const char*){}

int ApiClient::GET(const char*){}
int ApiClient::POST(const char*, DynamicJsonDocument*){}
int ApiClient::PUT(const char*, DynamicJsonDocument*){}
int ApiClient::DELETE(const char*){}
int ApiClient::PATCH(const char*, DynamicJsonDocument*){}

void ApiClient::setAuthentication(const char*){}
DynamicJsonDocument* ApiClient::getData(){}
void ApiClient::clear(){}

void ApiClient::connect(const char*){}
void ApiClient::disconnet(){}
void ApiClient::isConnected(){}

ApiClient::~ApiClient(){}
