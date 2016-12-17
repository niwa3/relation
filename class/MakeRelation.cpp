//MakeRelation
#include "MakeRelation.h"
//========MakeRelation========
MakeRelation::MakeRelation(std::mutex* m, std::vector<ACK>* b):database("dbname=test user=testuser password=testpass"){
  mtx=m;
  buffer=b;
}

MakeRelation::~MakeRelation(){}

void MakeRelation::run(){
  int req_success=1;
  UnixDomainSocketServer socket(mtx,buffer,&req_success);
  std::thread th(&UnixDomainSocketServer::run, socket);
  std::vector<ACK>::iterator itr;
  while(1){
    while(buffer->empty()){
      std::this_thread::yield;
    }
    mtx->lock();
    itr=buffer->begin();
    std::cout<<itr->request<<std::endl;
    switch(itr->request){
      case 'n':
        if(make_from_node(itr->nodeid))req_success=0;
        else req_success=2;
        break;
      case 's':
        if(make_from_service(itr->serviceid))req_success=0;
        else req_success=2;
        break;
      case 'c':
        if(change_privacy_from_node(itr->nodeid,itr->serviceid,itr->lvl))req_success=0;
        else req_success=2;
        break;
      case 'd':
        if(delete_relation(itr->nodeid,itr->serviceid))req_success=0;
        else req_success=2;
        break;
      default:
        throw;
        break;
    }
    mtx->unlock();
  }
  th.join();
}

bool MakeRelation::make_from_node(Node_ID newnodeid){
  try{
    std::vector<Consumer> newnode;
    std::vector<Consumer>::iterator itr;
    std::vector<Vender> match_service;
    std::vector<Vender>::iterator sitr;
    std::cout<<"nodeid = " + database.quote(newnodeid)<<std::endl;
    database.selectValue("nodeid = " + database.quote(newnodeid), newnode);
    if(newnode.empty()){
      std::cerr<<"err"<<std::endl;
      throw;}
    itr=newnode.begin();
    database.selectValue("privacy_lvl >= " + std::to_string(itr->getPrivacy_lvl()) + " AND data_type = " + database.quote(itr->getData_Type()) + " AND interval >= " + std::to_string(itr->getinterval()), match_service);

    for(sitr=match_service.begin();sitr!=match_service.end();sitr++){
      Relation tmp;
      tmp.setNode_ID(newnodeid);
      tmp.setService_ID(sitr->getService_ID());
      tmp.setAnonymization("noise");
      tmp.setPrivacy_lvl(sitr->getPrivacy_lvl());
      tmp.setinterval(sitr->getinterval());
      if(database.insertValue(tmp))std::cout<<"exist\n";
    }

    return true;
  }
  catch(...){
    return false;
  }
}

bool MakeRelation::make_from_service(Service_ID newserviceid){
  try{
    std::vector<Vender> newservice;
    std::vector<Vender>::iterator itr;
    std::vector<Consumer> match_node;
    std::vector<Consumer>::iterator nitr;
    std::cout<<"serviceid = " + database.quote(newserviceid)<<std::endl;
    database.selectValue("serviceid = " + database.quote(newserviceid), newservice);
    if(newservice.empty()){
      std::cerr<<"err"<<std::endl;
      throw;
    }
    itr=newservice.begin();
    database.selectValue("privacy_lvl <= " + std::to_string(itr->getPrivacy_lvl()) + " AND data_type = " + database.quote(itr->getData_Type()) + " AND interval <= " + std::to_string(itr->getinterval()), match_node);

    for(nitr=match_node.begin();nitr!=match_node.end();nitr++){
      Relation tmp;
      tmp.setNode_ID(nitr->getNode_ID());
      tmp.setService_ID(newserviceid);
      tmp.setAnonymization("noise");
      tmp.setPrivacy_lvl(itr->getPrivacy_lvl());
      tmp.setinterval(itr->getinterval());
      if(database.insertValue(tmp))std::cout<<"exist\n";
    }
    return true;
  }
  catch(...){
    return false;
  }
}

bool MakeRelation::change_privacy_from_node(Node_ID nodeid, Service_ID serviceid, int req){
  try{
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

bool MakeRelation::delete_relation(Node_ID nodeid, Service_ID serviceid){
  try{
    database.deleteRelation(nodeid, serviceid);
    return true;
  }
  catch(...){
    return false;
  }
}

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
