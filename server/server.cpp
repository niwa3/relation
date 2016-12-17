//File:RelationManager server.cpp
#include "soapRManagerService.h"
#include "RManager.nsmap"
#include <iostream>

int main(){
  RManagerService *server;
  server=new RManagerService(SOAP_XML_CANONICAL);
  server->serve();
  server->destroy();
  return 0;
}

int RManagerService::data(_ns1__dataRQ *req, _ns1__dataRS &res){
  return SOAP_OK;
}
