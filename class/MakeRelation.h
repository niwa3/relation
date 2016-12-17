//MakeRelation.h

#ifndef INCLUDED_MAKERELATION
#define INCLUDED_MAKERELATION

#include <iostream>
#include <string>
#include <mutex>
#include "database.h"

class MakeRelation{
  public:
    MakeRelation(std::mutex*, std::vector<std::string>*);
    ~MakeRelation();
    void run();
    bool make_from_node(Node_ID);//
    bool make_from_service(Service_ID);
    bool change_privacy_from_node(Node_ID, Service_ID, int);
    //bool change_privacy_from_service(Service_ID, Node_ID, int){};//いるの？
    bool delete_relation(Node_ID, Service_ID);

  private:
    std::mutex *mtx;
    std::vector<std::string> *buffer;
    DataBase database;
};

#endif
