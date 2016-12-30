//detabase.h
#ifndef INCLUDED_MYDATABASE
#define INCLUDED_MYDATABASE

#include <iostream>
#include <string>
#include <sstream>
#include <pqxx/pqxx>
#include <memory>
#include <vector>
#include "type.h"
#include "sha256.h"

class DataBase{
  private:
    std::unique_ptr<pqxx::connection> conn;
    std::unique_ptr<pqxx::work> T;
  public:
    DataBase(std::string call);
    bool insertValue(Consumer c);
    bool insertValue(Vender v);
    bool insertValue(Relation r);

    bool deleteValue(std::string kind, std::string id);
    bool deleteRelation(Node_ID, Service_ID);

    bool selectValue(std::string req, std::vector<Consumer> &c_res);
    bool selectValue(std::string req, std::vector<Vender> &v_res);
    bool selectValue(std::string req, std::vector<Relation> &r_res);

    bool checkValue(Consumer c){};
    bool checkValue(Vender v){};
    bool checkValue(Relation r){};

    bool updataRelationPrivacy(Node_ID, Service_ID, int);

    bool authUser(std::string username,std::string password, std::string &userid);
    bool authVender(std::string vendername,std::string password, std::string &venderid);
    bool insertUser(std::string username, std::string password);

    std::string quote(std::string);
    ~DataBase();
}; 

std::vector<std::string> splitarray(std::string str);
std::vector<std::string> split(const std::string &str, char sep);

#endif
