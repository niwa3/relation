//MakeRelation.h

#ifndef INCLUDED_MY_MAKERELATION
#define INCLUDED_MY_MAKERELATION

#include <iostream>
#include <string>
#include <mutex>
#include <map>
#include "database.h"
#include "type.h"
#include "../client/mySoapClient.h"

class MakeRelation{
  public:
    MakeRelation();
    ~MakeRelation();
    //void run();
    bool auth_user(std::string username, std::string password, std::string &userid);
    bool make_from_node(Consumer);//
    bool make_from_service(Vender);
    bool change_privacy_from_node(Node_ID, Service_ID, int, User_ID);
    //bool change_privacy_from_service(Service_ID, Node_ID, int){};//いるの？
    bool delete_relation(Node_ID, Service_ID, User_ID);
    bool auth_user(AUTH);

  private:
    std::string dbopt;
};

#endif
