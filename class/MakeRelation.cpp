//MakeRelation
#ifndef MAKE_RELATION_CPP
#define MAKE_RELATION_CPP
#include "MakeRelation.h"
//========MakeRelation========
MakeRelation::MakeRelation(){
  dbopt="dbname=test user=testuser password=testpass";
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
      if(!database.insertValue(newnode)){
        return false;
      }
    }
    /* ここで登録されたノードとサービスのマッチングを行う
     * どのようにマッチングをするべきかは要研究
     * 現在は，
     * データタイプが一致し，
     * 要求プライバシがプライバシ基準を上回っているもの
     * データ要求間隔が，データ取得間隔よりも長いもの
     * をマッチングさせている．
     */
    database.selectValue("privacy_lvl >= " + std::to_string(newnode.getPrivacy_lvl()) + " AND data_type = " + database.quote(newnode.getData_Type()) + " AND interval >= " + std::to_string(newnode.getinterval()), match_service);
    std::cout<<"matching service\n";

    std::map<std::string, std::vector<Relation> > m_rv;
    for(sitr=match_service.begin();sitr!=match_service.end();sitr++){
      Relation tmp;
      tmp.setNode_ID(newnode.getNode_ID());
      tmp.setService_ID(sitr->getService_ID());
      tmp.setAnonymization("noise");
      tmp.setPrivacy_lvl(sitr->getPrivacy_lvl());
      tmp.setinterval(sitr->getinterval());
      tmp.setlocation(newnode.getlocation());
      if(!database.insertValue(tmp))
        std::cerr<<"exist\n";
      database.selectValue("nodeid = " + database.quote(newnode.getNode_ID()) + " AND serviceid = " + database.quote(sitr->getService_ID()), m_rv[tmp.getlocation()]);
    }
    mySoapClient msclient;
    for(auto m_itr=m_rv.begin(); m_itr!=m_rv.end(); m_itr++){
      msclient.sendRelation(m_itr->first,m_itr->second);
    }
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
      return false;
    }else{
      if(!database.insertValue(newservice))
        return false;
    }
    database.selectValue("privacy_lvl <= " + std::to_string(newservice.getPrivacy_lvl()) + " AND data_type = " + database.quote(newservice.getData_Type()) + " AND interval <= " + std::to_string(newservice.getinterval()), match_node);
    std::cout<<"matching node\n";

    std::map<std::string, std::vector<Relation> > m_rv;
    for(nitr=match_node.begin();nitr!=match_node.end();nitr++){
      Relation tmp;
      tmp.setNode_ID(nitr->getNode_ID());
      tmp.setService_ID(newservice.getService_ID());
      tmp.setAnonymization("noise");
      tmp.setPrivacy_lvl(newservice.getPrivacy_lvl());
      tmp.setinterval(newservice.getinterval());
      tmp.setlocation(nitr->getlocation());
      if(!database.insertValue(tmp))std::cout<<"exist\n";
      database.selectValue("nodeid = " + database.quote(nitr->getNode_ID()) + " AND serviceid = " + database.quote(newservice.getService_ID()), m_rv[tmp.getlocation()]);
    }
    mySoapClient msclient;
    for(auto m_itr=m_rv.begin(); m_itr!=m_rv.end(); m_itr++){
      msclient.sendRelation(m_itr->first,m_itr->second);
    }
    return true;
  }
  catch(...){
    return false;
  }
}

bool MakeRelation::change_privacy_from_node(Service_ID serviceid, Node_ID nodeid, int req){
  try{
    DataBase database(dbopt);
    std::vector<Relation> relation;
    database.selectValue("serviceid = " + database.quote(serviceid) + " AND nodeid = " + database.quote(nodeid), relation);
    std::cout<<relation.empty()<<std::endl;
    if(relation.empty()){
      throw;
    }
    database.updataRelationPrivacy(nodeid,serviceid,req);
    relation.begin()->setPrivacy_lvl(req);
    mySoapClient msclient;
    msclient.changeRelation(relation.begin()->getlocation(),relation);
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
//  MakeRelation make;
  //Consumer c;
  //c.setNode_ID("http");
  //c.setUser_ID("u00001");
  //c.setData_Type("power");
  //c.setNode_Type("sensor");
  //c.setPrivacy_lvl(2);
  //c.setinterval(60);
  //c.setlocation("http:");
  //make.make_from_node(c);
  //Vender v;
  //v.setService_ID("http");
  //v.setVender_ID("v0001");
  //v.setData_Type("power");
  //v.setPrivacy_lvl(2);
  //v.setinterval(60);
  //make.make_from_service(v);
  //make.change_privacy_from_node("http://GW/sensor1","http://service/dummy4",1);
  //make.delete_relation("http://GW/sensor3", "http://service/dummy4");
//  return 0;
//  }
//  catch(...){
//    std::cerr<<"err"<<std::endl;
//    return 1;
//  }
//}
