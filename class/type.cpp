//type.cpp
#ifndef _MY_TYPE_CPP_
#define _MY_TYPE_CPP_
#include <iostream>
#include "type.h"

//==========class Consumer=============
Consumer::Consumer(){
  Consumer::privacy_lvl=MAXLVL;
  Consumer::node_type=Node_Type::NONE;
  Consumer::data_type=Data_Type::NONE;
  Consumer::interval=0;
}

Consumer::~Consumer(){
}

int Consumer::setUser_ID(User_ID id){
  if(id.size()<=63){
    Consumer::user_id=id;
    return 0;
  }
  else throw "user_id size error";
}

int Consumer::setNode_ID(Node_ID id){
  if(id.size()<=63){
    Consumer::node_id=id;
    return 0;
  }
  else throw "node_id size error";
}

int Consumer::setPrivacy_lvl(int lv){
//  if(dp=="high") Consumer::privacy_lvl=Privacy::HIGH;
//  else if(dp=="mid") Consumer::privacy_lvl=Privacy::MID;
//  else if(dp=="low") Consumer::privacy_lvl=Privacy::LOW;
//  else if(dp=="none") Consumer::privacy_lvl=Privacy::NONE;
//  else throw "privacy_lvl error\n";
  if(lv>MAXLVL || lv<MINLVL){
    throw "Privacy\n";
    return 1;
  }
  privacy_lvl=lv;
  return 0;
}

int Consumer::setNode_Type(std::string type){
  if(type=="none") Consumer::node_type=Node_Type::NONE;
  else if(type=="sensor") Consumer::node_type=Node_Type::SENSOR;
  else if(type=="actuator") Consumer::node_type=Node_Type::ACTUATOR;
  else throw "node_type error";
  return 0;
}

int Consumer::setData_Type(std::string type){
  if(type=="none") Consumer::data_type=Data_Type::NONE;
  else if(type=="power") Consumer::data_type=Data_Type::POWER;
  else if(type=="temp") Consumer::data_type=Data_Type::TEMP;
  else if(type=="wind") Consumer::data_type=Data_Type::WIND;
  else if(type=="CO2") Consumer::data_type=Data_Type::CO2;
  else throw "data_type error";
  return 0;
}

int Consumer::setinterval(int f){
  interval=f;
  return 0;
}

User_ID Consumer::getUser_ID(){
  return Consumer::user_id;
}

Node_ID Consumer::getNode_ID(){
  return Consumer::node_id;
}

Privacy Consumer::getPrivacy_lvl(){
//  if(Consumer::privacy_lvl==Privacy::HIGH)return "high";
//  else if(Consumer::privacy_lvl==Privacy::MID)return "mid";
//  else if(Consumer::privacy_lvl==Privacy::LOW)return "low";
//  else if(Consumer::privacy_lvl==Privacy::NONE)return "none";
//  else throw "privacy_lvl error";
  return privacy_lvl;
}

std::string Consumer::getNode_Type(){
  switch(node_type){
    case Node_Type::ACTUATOR:
      return "actuator";
      break;
    case Node_Type::SENSOR:
      return "sensor";
      break;
    case Node_Type::NONE:
      return "none";
      break;
    default:
      throw "node_type error";
  }
}

std::string Consumer::getData_Type(){
  switch(data_type){
    case Data_Type::POWER:
      return "power";
      break;
    case Data_Type::TEMP:
      return "temp";
      break;
    case Data_Type::NONE:
      return "none";
      break;
    case Data_Type::WIND:
      return "wind";
      break;
    case Data_Type::CO2:
      return "co2";
      break;
    default:
      throw "data_type error";
    }
}

int Consumer::getinterval(){
  return Consumer::interval;
}

//=============Vender=============
int Vender::setVender_ID(Vender_ID id){
  if(id.size()<=63){
    Vender::vender_id=id;
    return 0;
  }
  else throw "vender_id size error";
}

int Vender::setService_ID(Service_ID id){
  if(id.size()<=63){
    Vender::service_id=id;
    return 0;
  }
  else throw "service_id size error";
}

int Vender::setPrivacy_lvl(Privacy lv){
  //if(pr=="high") Vender::privacy_lvl=Privacy::HIGH;
  //else if(pr=="mid") Vender::privacy_lvl=Privacy::MID;
  //else if(pr=="low") Vender::privacy_lvl=Privacy::LOW;
  //else if(pr=="none") Vender::privacy_lvl=Privacy::NONE;
  //else throw "privacy_lvl error";
  if(lv>MAXLVL || lv<MINLVL){
    throw "Privacy\n";
    return 1;
  }
  privacy_lvl=lv;
  return 0;
}

int Vender::setData_Type(std::string type){
  if(type=="none") Vender::data_type=Data_Type::NONE;
  else if(type=="power") Vender::data_type=Data_Type::POWER;
  else if(type=="temp") Vender::data_type=Data_Type::TEMP;
  else if(type=="wind") Vender::data_type=Data_Type::WIND;
  else if(type=="CO2") Vender::data_type=Data_Type::CO2;
  else throw "data_type error";
  return 0;
}

int Vender::setinterval(int f){
  interval=f;
  return 0;
}

std::string Vender::getVender_ID(){
  return Vender::vender_id;
}

std::string Vender::getService_ID(){
  return Vender::service_id;
}

Privacy Vender::getPrivacy_lvl(){
  //if(Vender::privacy_lvl==Privacy::HIGH)return "high";
  //else if(Vender::privacy_lvl==Privacy::MID)return "mid";
  //else if(Vender::privacy_lvl==Privacy::LOW)return "low";
  //else if(Vender::privacy_lvl==Privacy::NONE)return "none";
  //else throw "privacy_lvl error";
  return privacy_lvl;
}

std::string Vender::getData_Type(){
  if(Vender::data_type==Data_Type::POWER)return "power";
  else if(Vender::data_type==Data_Type::TEMP)return "temp";
  else if(Vender::data_type==Data_Type::NONE)return "none";
  else if(Vender::data_type==Data_Type::WIND)return "wind";
  else if(Vender::data_type==Data_Type::CO2)return "co2";
  else throw "data_type error";
}

int Vender::getinterval(){
  return interval;
}

Vender::Vender(){
  Vender::privacy_lvl=MAXLVL;
  Vender::data_type=Data_Type::NONE;
  Vender::interval=0;
}
Vender::~Vender(){}

//==========class Relation===========
int Relation::setRelation_ID(Relation_ID id){
  Relation::relation_id=id;
  return 0;
}

int Relation::setAnonymization(std::string an){
  if(an=="delete")Relation::method=Anonymization_Method::DELETE;
  else if(an=="noise")Relation::method=Anonymization_Method::NOISE;
  else if(an=="chenge")Relation::method=Anonymization_Method::CHENGE;
  else throw "anonymization error";
  return 0;
}

int Relation::setPrivacy_lvl(Privacy lv){
  //if(lvl=="high") Relation::privacy_lvl=Privacy::HIGH;
  //else if(lvl=="mid") Relation::privacy_lvl=Privacy::MID;
  //else if(lvl=="low") Relation::privacy_lvl=Privacy::LOW;
  //else if(lvl=="none") Relation::privacy_lvl=Privacy::NONE;
  //else throw "privacy_lvl error";
  if(lv>MAXLVL || lv<MINLVL){
    throw "Privacy\n";
    return 1;
  }
  privacy_lvl=lv;
  return 0;
}

//int Relation::addServices(Service_ID id){
//  Relation::services.push_back(id);
//  return 0;
//}
int Relation::setNode_ID(Node_ID id){
  node_id=id;
  return 0;
}

//int Relation::addNodes(Node_ID id){
//  Relation::nodes.push_back(id);
//  return 0;
//}
int Relation::setService_ID(Service_ID id){
  service_id=id;
  return 0;
}

int Relation::setinterval(int f){
  interval=f;
  return 0;
}

Relation_ID Relation::getRelation_ID(){
  return Relation::relation_id;
}

std::string Relation::getAnonymization(){
  if(Relation::method==Anonymization_Method::DELETE)return "delete";
  else if(method==Anonymization_Method::NOISE)return "noise";
  else if(method==Anonymization_Method::CHENGE)return "chenge";
 else throw "anonymization error";
}

Privacy Relation::getPrivacy_lvl(){
  //if(Relation::privacy_lvl==Privacy::HIGH)return "high";
  //else if(Relation::privacy_lvl==Privacy::MID)return "mid";
  //else if(Relation::privacy_lvl==Privacy::LOW)return "low";
  //else if(Relation::privacy_lvl==Privacy::NONE)return "none";
  //else throw "privacy_lvl error";
  return privacy_lvl;
}

//std::vector<Service_ID> Relation::getServices(){
//  return Relation::services;
//}
Node_ID Relation::getNode_ID(){
  return node_id;
}

//std::vector<Node_ID> Relation::getNodes(){
//  return Relation::nodes;
//}
Service_ID Relation::getService_ID(){
  return service_id;
}

int Relation::getinterval(){
  return interval;
}

Relation::Relation(){
  Relation::method=Anonymization_Method::NONE;
  Relation::privacy_lvl=3;
  Relation::interval=0;
}

Relation::~Relation(){}

#endif
//===================================
//int main(){
//  try{
//  Consumer c;
//  c.setUser_ID("http://foshdoiasdfhosahoashfoh/");
//  c.setNode_ID("http://kljkjl/ljl/jljl");
//  c.setPrivacy_lvl(2);
//  c.setNode_Type("sensor");
//  c.setData_Type("temp");
//  std::cout<<c.getUser_ID()<<c.getNode_ID()<<c.getPrivacy_lvl()<<c.getNode_Type()<<c.getData_Type()<<c.getinterval()<<std::endl;
//
//  Vender v;
//  v.setVender_ID("http://");
//  v.setService_ID("http://slj/");
//  v.setPrivacy_lvl("high");
//  v.setData_Type("power");
//  std::cout<<v.getVender_ID()<<v.getService_ID()<<v.getPrivacy_lvl()<<v.getData_Type()<<std::endl;
//
//  Relation r;
//  r.setAnonymization("noise");
//  r.setPrivacy_lvl(1);
//  r.setService_ID("http://hoh/");
//  r.setNode_ID("http://hljl");
//  r.setinterval(60);
//  std::cout<<r.getAnonymization()<<r.getPrivacy_lvl()<<r.getService_ID()<<r.getNode_ID()<<r.getNode_ID()<<r.getService_ID()<<std::endl;
//  }
//  catch(const char* e){
//    std::cout<<e<<std::endl;
//  }
//
//  return 0;
//}
