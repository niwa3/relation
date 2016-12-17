//File:RelationManager server.cpp
#include "soapH.h"
#include "RManager.nsmap"
#include "wsseapi.h"
#include <iostream>

int main(){
  struct soap *soap;
  soap=soap_new1(SOAP_XML_CANONICAL);
  soap_wsse_add_Security(soap);
  soap_register_plugin(soap, soap_wsse);
  return soap_serve(soap);
}

int ns1__data(struct soap *soap, _ns1__dataRQ req, _ns1__dataRS res){
  return SOAP_OK;
}
