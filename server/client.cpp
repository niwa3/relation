#include "soapRManagerProxy.h"
#include "RManager.nsmap"
#include "iostream"
#include "ctime"

int main(int argc, char* argv[]){
  currentTimeProxy* service = new currentTimeProxy("https://10.0.0.2/cgi-bin/server.cgi");
  soap_ssl_init();
  if(soap_ssl_client_context(service,
        SOAP_SSL_DEFAULT | SOAP_SSL_SKIP_HOST_CHECK,
        "./client.pem",
        NULL,
        "./cacert.pem",
        NULL,
        NULL))
  {
    soap_print_fault(service, stderr);
    exit(1);
  }

  time_t result;
  if(service->currentTime(result)==SOAP_OK){
    std::cout<<std::ctime(&result)<<std::endl;
  }
  else soap_print_fault(service, stderr);
  service->destroy();
}
