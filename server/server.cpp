//File:RelationManager server.cpp
#include "soapRManagerService.h"
#include "RManager.nsmap"
#include <iostream>
#include <thread>
#include <fstream>
#include <memory>
#include <pqxx/pqxx>

class writefile{
  public:
    writefile(ns1__transport *request){
      req=request;
    };
    ~writefile(){};
    void run(){
      std::vector<ns1__relation>::iterator itr;
      std::unique_ptr<pqxx::connection> conn(new pqxx::connection("dbname=test user=testuser password=testpass"));
      std::unique_ptr<pqxx::work> T(new pqxx::work(*conn));
      for(itr=req->body.relation.begin(); itr!=req->body.relation.end();itr++){
        T.get()->exec(
            "INSERT INTO server "
            "VALUES ("+std::to_string(itr->relation_id)
            +","+T.get()->quote(itr->service_id)
            +","+T.get()->quote(itr->node_id)
            +","+std::to_string(itr->privacy_lvl)
            +","+T.get()->quote(itr->anonymous_method)
            +","+std::to_string(itr->interval)+")");
      }
      T.get()->commit();
    };

  private:
    ns1__transport *req;
};

int main(){
  RManagerService server(SOAP_XML_CANONICAL);
  server.serve();
  server.destroy();
}

int RManagerService::data(ns1__transport *req, ns1__transport &res){
  res=*req;
  writefile w(req);
  std::thread th(&writefile::run,w);
  th.join();
    return SOAP_OK;
}
