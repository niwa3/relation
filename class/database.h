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

class DataBase{
  private:
    std::unique_ptr<pqxx::connection> conn;
    std::unique_ptr<pqxx::work> T;
  public:
    DataBase(std::string call);
    int insertValue(Consumer c);
    int insertValue(Vender v);
    int insertValue(Relation r);
    int deleteValue(std::string kind, std::string id);
    int deleteRelation(Node_ID, Service_ID);
    int selectValue(std::string req, std::vector<Consumer> &c_res);
    int selectValue(std::string req, std::vector<Vender> &v_res);
    int selectValue(std::string req, std::vector<Relation> &r_res);
    int checkValue(Consumer c){};
    int checkValue(Vender v){};
    int checkValue(Relation r){};
    int updataRelationPrivacy(Node_ID, Service_ID, int);
    std::string quote(std::string);
    ~DataBase();
}; 

std::vector<std::string> splitarray(std::string str);
std::vector<std::string> split(const std::string &str, char sep);

#endif
