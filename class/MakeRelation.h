//MakeRelation.h

#ifndef INCLUDED_MAKERELATION
#define INCLUDED_MAKERELATION

#include <iostream>
#include <string>
#include <mutex>
#include "database.h"
#include "type.h"

class MakeRelation{
  public:
    MakeRelation(std::mutex*, std::vector<ACK>*);
    ~MakeRelation();
    //void run();
    bool auth_user(std::string username, std::string password, std::string &userid);
    bool make_from_node(Consumer,User_ID);//
    bool make_from_service(Vender,Vender_ID);
    bool change_privacy_from_node(Node_ID, Service_ID, int, User_ID);
    //bool change_privacy_from_service(Service_ID, Node_ID, int){};//いるの？
    bool delete_relation(Node_ID, Service_ID, User_ID);
    bool auth_user(AUTH);

  private:
    std::mutex *mtx;
    std::vector<ACK> *buffer;
    std::string dbopt;
};

#endif
