#include "ApiClient.h"
#include <ArduinoJson.h>

ApiClient::ApiClient(const char* ipAddress){

}

ApiClient::ApiClient(Client* client){

}

int ApiClient::GET(const char* apiLink){

}

int ApiClient::POST(const char* apiLink, DynamicJsonDocument* payload){

}

int ApiClient::PUT(const char* apiLink, DynamicJsonDocument* payload){

}

int ApiClient::DELETE(const char* apiLink){

}

int ApiClient::PATCH(const char* apiLink, DynamicJsonDocument* payload){

}

DynamicJsonDocument ApiClient::getData(){

}

void ApiClient::setAuthentication(const char* secrete){

}

void ApiClient::clear(){

}

void ApiClient::isConnected(){

}

void ApiClient::disconnet(){

}

ApiClient::~ApiClient(){

}
