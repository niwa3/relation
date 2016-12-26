//MakeRelation
#ifndef _MAKE_RELATION_CPP_
#define _MAKE_RELATION_CPP_
#include "MakeRelation.h"
//========MakeRelation========
MakeRelation::MakeRelation(std::mutex* m, std::vector<ACK>* b){
  dbopt="dbname=test user=testuser password=testpass";
  mtx=m;
  buffer=b;
}

MakeRelation::~MakeRelation(){}

//void MakeRelation::run(){
//}

bool MakeRelation::auth_user(std::string username, std::string password, std::string &userid){
  try{
    DataBase database(dbopt);
    if(database.authUser(username, password, userid)){
      return true;
    }else return false;
  }
  catch(...){
    return false;
  }
}

bool MakeRelation::make_from_node(Consumer newnode){
  try{
    DataBase database(dbopt);
    std::vector<Vender> match_service;
    std::vector<Vender>::iterator sitr;
    if(newnode.getNode_ID().empty()){
      std::cerr<<"err"<<std::endl;
      return false;
    }else{
      std::cout<<"insert newnode"<<std::endl;
      if(database.insertValue(newnode)!=0){
        return false;
      }
    }
    database.selectValue("privacy_lvl >= " + std::to_string(newnode.getPrivacy_lvl()) + " AND data_type = " + database.quote(newnode.getData_Type()) + " AND interval >= " + std::to_string(newnode.getinterval()), match_service);

    std::vector<Relation> rv;
    for(sitr=match_service.begin();sitr!=match_service.end();sitr++){
      std::cout<<"match_service:"<<sitr->getService_ID()<<std::endl;
      Relation tmp;
      tmp.setNode_ID(newnode.getNode_ID());
      tmp.setService_ID(sitr->getService_ID());
      tmp.setAnonymization("noise");
      tmp.setPrivacy_lvl(sitr->getPrivacy_lvl());
      tmp.setinterval(sitr->getinterval());
      rv.push_back(tmp);
      if(database.insertValue(tmp))std::cout<<"exist\n";
    }
    mySoapClient msclient;
    msclient.sendRelation("https://10.0.0.2/cgi-bin/server.cgi",rv);

    return true;
  }
  catch(...){
    return false;
  }
}

bool MakeRelation::make_from_service(Vender newservice){
  try{
    DataBase database(dbopt);
    std::vector<Consumer> match_node;
    std::vector<Consumer>::iterator nitr;
    if(newservice.getService_ID().empty()){
      std::cerr<<"err"<<std::endl;
      throw;
    }else{
      database.insertValue(newservice);
    }
    database.selectValue("privacy_lvl <= " + std::to_string(newservice.getPrivacy_lvl()) + " AND data_type = " + database.quote(newservice.getData_Type()) + " AND interval <= " + std::to_string(newservice.getinterval()), match_node);

    for(nitr=match_node.begin();nitr!=match_node.end();nitr++){
      Relation tmp;
      tmp.setNode_ID(nitr->getNode_ID());
      tmp.setService_ID(newservice.getService_ID());
      tmp.setAnonymization("noise");
      tmp.setPrivacy_lvl(newservice.getPrivacy_lvl());
      tmp.setinterval(newservice.getinterval());
      if(database.insertValue(tmp))std::cout<<"exist\n";
    }
    return true;
  }
  catch(...){
    return false;
  }
}

bool MakeRelation::change_privacy_from_node(Node_ID nodeid, Service_ID serviceid, int req, User_ID id){
  try{
    DataBase database(dbopt);
    std::vector<Relation> relation;
    std::vector<Relation>::iterator iitr;
    database.selectValue("serviceid = " + database.quote(serviceid) + " AND nodeid = " + database.quote(nodeid), relation);
    if(relation.empty()){
      throw;
    }
    database.updataRelationPrivacy(nodeid,serviceid,req);
    return true;
  }
  catch(...){
    return false;
  }
}

bool MakeRelation::delete_relation(Node_ID nodeid, Service_ID serviceid, User_ID id){
  try{
    DataBase database(dbopt);
    database.deleteRelation(nodeid, serviceid);
    return true;
  }
  catch(...){
    return false;
  }
}

#endif
//int main(){
//  try{
//  std::mutex *m=new std::mutex();
//  std::vector<std::string> *buffer=new std::vector<std::string>();
//  MakeRelation make(m,buffer);
//  make.make_from_node("http://GW/sensor1");
//  make.make_from_node("http://GW/sensor2");
//  make.make_from_node("http://GW/sensor3");
//  make.make_from_service("http://service/dummy1");
//  make.make_from_service("http://service/dummy2");
//  make.change_privacy_from_node("http://GW/sensor1","http://service/dummy4",1);
//  make.delete_relation("http://GW/sensor3", "http://service/dummy4");
//  delete(m);
//  delete(buffer);
//  return 0;
//  }
//  catch(...){
//    std::cerr<<"err"<<std::endl;
//    return 1;
//  }
//}
