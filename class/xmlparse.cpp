//xmlparse
#ifndef MY_XMLPARSE_CPP
#define MY_XMLPARSE_CPP
#include "xmlparse.h"

xmlParse::xmlParse(){
}

xmlParse::xmlParse(std::string source){
  Parse(source);
}

xmlParse::~xmlParse(){
}

void xmlParse::Parse(std::string source){
  xml.Parse(source.c_str());
}

void xmlParse::Print(){
  xml.Print();
}

void xmlParse::SaveFile(std::string file){
  xml.SaveFile(file.c_str());
}

void xmlParse::Clear(){
  xml.Clear();
  element.clear();
}

void xmlParse::LoadFile(std::string file){
  xml.LoadFile(file.c_str());
}

void xmlParse::GetEle(ELEMENTNAME e){
  if(element.count(e)==0)
    element[e] = xml.FirstChildElement(e.c_str());
}

void xmlParse::GetEle(ELEMENTNAME e, ELEMENTNAME dst){
  if(element.count(e)==0)
    element[e] = element[dst]->FirstChildElement(e.c_str());
}

std::string xmlParse::GetEleinEle(ELEMENTNAME dst){
  std::string name=element[dst]->FirstChildElement()->Name();
  element[name] = element[dst]->FirstChildElement();
  return name;
}

bool xmlParse::GetNextEle(ELEMENTNAME e){
  if(element[e]!=NULL){
    element[e] = element[e]->NextSiblingElement();
    return true;
  }
  else return false;
}

std::string xmlParse::GetText(ELEMENTNAME e){
  return element[e]->GetText();
}

std::string xmlParse::GetAtt(ELEMENTNAME e,std::string att){
  return element[e]->Attribute(att.c_str());
}

bool xmlParse::XML_transport(){
  if(element.count("transport")==0){
    GetEle("transport");
    return true;
  }
  return false;
}

bool xmlParse::XML_header(std::string &method){
  if(element.count("header")==0){
    GetEle("header","transport");
    GetEle("method", "header");
    method=GetText("method");
    return true;
  }
  return false;
}

bool xmlParse::XML_header_id(std::string &id){
  GetEle("id", "header");
  id=GetText("id");
  if(!id.empty())
    return true;
  return false;
}

bool xmlParse::XML_body(){
  if(element.count("body")==0){
    GetEle("body","transport");
    return true;
  }
  return false;
}

bool xmlParse::XML_node(Consumer& c){
  XML_body();
  GetEle("node","body");
  GetEle("nodeid","node");
  GetEle("userid","node");
  GetEle("privacy_lvl","node");
  GetEle("node_type","node");
  GetEle("data_type","node");
  GetEle("interval","node");
  GetEle("location","node");
  if(
  c.setNode_ID(GetText("nodeid"))==0 &&
  c.setUser_ID(GetText("userid"))==0 &&
  c.setPrivacy_lvl(std::stoi(GetText("privacy_lvl")))==0&&
  c.setNode_Type(GetText("node_type"))==0 &&
  c.setData_Type(GetText("data_type"))==0 &&
  c.setinterval(std::stoi(GetText("interval")))==0 &&
  c.setlocation(GetText("location"))==0)
    return true;
  return false;
}

bool xmlParse::XML_node(std::vector<Consumer> &cv){
  XML_body();
  GetEle("node","body");
  do{
  Consumer tmp;
  GetEle("nodeid","node");
  GetEle("userid","node");
  GetEle("privacy_lvl","node");
  GetEle("node_type","node");
  GetEle("data_type","node");
  GetEle("interval","node");
  tmp.setNode_ID(GetText("nodeid"));
  tmp.setUser_ID(GetText("userid"));
  tmp.setPrivacy_lvl(std::stoi(GetText("privacy_lvl")));
  tmp.setNode_Type(GetText("node_type"));
  tmp.setData_Type(GetText("data_type"));
  tmp.setinterval(std::stoi(GetText("interval")));
  cv.push_back(tmp);
  }while(GetNextEle("node"));
  return true;
}

bool xmlParse::XML_service(Vender& c){
  XML_body();
  GetEle("service","body");
  GetEle("serviceid","service");
  GetEle("venderid","service");
  GetEle("privacy_lvl","service");
  GetEle("data_type","service");
  GetEle("interval","service");
  if(
  c.setService_ID(GetText("serviceid"))==0 &&
  c.setVender_ID(GetText("venderid"))==0 &&
  c.setPrivacy_lvl(std::stoi(GetText("privacy_lvl")))==0&&
  c.setData_Type(GetText("data_type"))==0 &&
  c.setinterval(std::stoi(GetText("interval")))==0)
    return true;
  return false;
}

bool xmlParse::XML_service(std::vector<Vender> &cv){
  XML_body();
  GetEle("service","body");
  do{
  Vender tmp;
  GetEle("serviceid","service");
  GetEle("venderid","service");
  GetEle("privacy_lvl","service");
  GetEle("data_type","service");
  GetEle("interval","service");
  tmp.setService_ID(GetText("serviceid"));
  tmp.setVender_ID(GetText("venderid"));
  tmp.setPrivacy_lvl(std::stoi(GetText("privacy_lvl")));
  tmp.setData_Type(GetText("data_type"));
  tmp.setinterval(std::stoi(GetText("interval")));
  cv.push_back(tmp);
  }while(GetNextEle("service"));
  return true;
}

bool xmlParse::XML_relation(Relation& r){
  XML_body();
  GetEle("relation","body");
  GetEle("relationid","relation");
  GetEle("serviceid","relation");
  GetEle("nodeid","relation");
  GetEle("anonymization_method","relation");
  GetEle("privacy_lvl","relation");
  GetEle("interval","relation");
  GetEle("location","relation");
  if(
  r.setRelation_ID(std::stoi(GetText("relationid")))==0 &&
  r.setService_ID(GetText("serviceid"))==0 &&
  r.setNode_ID(GetText("nodeid"))==0 &&
  r.setAnonymization(GetText("anonymization_method"))==0 &&
  r.setPrivacy_lvl(std::stoi(GetText("privacy_lvl")))==0&&
  r.setinterval(std::stoi(GetText("interval")))==0 &&
  r.setlocation(GetText("location"))==0)
    return true;
  return false;
}

bool xmlParse::XML_relation(std::vector<Relation> &rv){
  XML_body();
  GetEle("relation","body");
  do{
  Relation tmp;
  GetEle("relationid","relation");
  GetEle("serviceid","relation");
  GetEle("nodeid","relation");
  GetEle("anonymization_method","relation");
  GetEle("privacy_lvl","relation");
  GetEle("interval","relation");
  GetEle("location","relation");
  tmp.setRelation_ID(std::stoi(GetText("relationid")));
  tmp.setService_ID(GetText("serviceid"));
  tmp.setNode_ID(GetText("nodeid"));
  tmp.setAnonymization(GetText("anonymization_method"));
  tmp.setPrivacy_lvl(std::stoi(GetText("privacy_lvl")));
  tmp.setinterval(std::stoi(GetText("interval")));
  tmp.setlocation(GetText("location"));
  rv.push_back(tmp);
  }while(GetNextEle("relation"));
  return true;
}

bool xmlParse::XML_auth(AUTH &a){
  XML_body();
  GetEle("auth_info","body");
  GetEle("username","auth_info");
  GetEle("password","auth_info");
  if(
      !(a.username=GetText("username")).empty() &&
      !(a.password=GetText("password")).empty())
    return true;
  return false;
}

bool xmlParse::XML_id(std::string &idname, std::string &id){
  XML_body();
  if(
      !(idname=GetEleinEle("body")).empty() &&
      !(id=GetText(idname)).empty())
    return true;
  return false;
}

bool xmlParse::XML_privacy(std::string &serviceid, std::string &nodeid, int &req){
  XML_body();
  GetEle("privacy", "body");
  GetEle("serviceid", "privacy");
  GetEle("nodeid", "privacy");
  GetEle("privacy_lvl", "privacy");
  if(
      !(serviceid=GetText("serviceid")).empty() &&
      !(nodeid=GetText("nodeid")).empty() &&
      0<(req=std::stoi(GetText("privacy_lvl"))) &&
      req<=3)
    return true;
  return false;
}

bool xmlParse::XML_delete_node(std::string &nodeid){
  XML_body();
  GetEle("deleteid", "body");
  GetEle("nodeid", "deleteid");
  if(!(nodeid=GetText("nodeid")).empty())
    return true;
  return false;
}

bool xmlParse::XML_delete_service(std::string &serviceid){
  XML_body();
  GetEle("deleteid", "body");
  GetEle("serviceid", "deleteid");
  if(!(serviceid=GetText("serviceid")).empty())
    return true;
  return false;
}

#endif
//int main(){
//  xmlParse xmlparse;
//  xmlparse.LoadFile("test.txt");
//  xmlparse.Print();
//  xmlparse.XML_transport();
//  std::string method;
//  xmlparse.XML_header(method);
//  std::cout<<method<<std::endl;
//  std::string s;
//  std::string n;
//  int p;
//  xmlparse.XML_privacy(s,n,p);
//  std::cout<<s<<n<<p<<std::endl;
//  return 0;
//}
