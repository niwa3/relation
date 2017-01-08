//xmlcreate
#ifndef MY_XMLCREATE_CPP
#define MY_XMLCREATE_CPP
#include "xmlcreate.h"

//===============class xmlCreate==============
xmlCreate::xmlCreate(){
  tinyxml2::XMLDeclaration *decl=xml.NewDeclaration();
  xml.InsertEndChild(decl);
}

tinyxml2::XMLDocument* xmlCreate::getXML(){
  return xmlCreate::xml.GetDocument();
}

void xmlCreate::InsertEle(std::string e){
  xmlCreate::element[e] = xmlCreate::xml.NewElement(e.c_str());
  xmlCreate::xml.InsertEndChild(xmlCreate::element[e]);
}

void xmlCreate::InsertEle(std::string e, std::string dst){
  xmlCreate::element[e] = xmlCreate::xml.NewElement(e.c_str());
  xmlCreate::element[dst]->InsertEndChild(xmlCreate::element[e]);
}

void xmlCreate::SetAtt(ELEMENTNAME e,std::string n, std::string v){
  element[e]->SetAttribute(n.c_str(),v.c_str());
}

void xmlCreate::InsertText(ELEMENTNAME e,std::string t){
  tinyxml2::XMLText* text=xmlCreate::xml.NewText(t.c_str());
  element[e]->InsertEndChild(text);
}

void xmlCreate::Print(){
  xmlCreate::xml.Print();
}

void xmlCreate::SaveFile(std::string file){
  xmlCreate::xml.SaveFile(file.c_str());
}

void xmlCreate::Clear(){
  xml.Clear();
  tinyxml2::XMLDeclaration *decl=xml.NewDeclaration();
  xml.InsertEndChild(decl);
  element.clear();
}

std::string xmlCreate::return_string(){
  tinyxml2::XMLPrinter printer;
  xml.Print(&printer);
  return printer.CStr();
}

bool xmlCreate::XML_transport(){
  try{
    if(element.count("transport")!=0)
      throw;
    InsertEle("transport");
    return true;
  }catch(...){
    return false;
  }
}

bool xmlCreate::XML_header(std::string method){
  try{
    if(element.count("header")!=0)
      throw;
    InsertEle("header","transport");
    InsertEle("method","header");
    InsertText("method",method);
    return true;
  }catch(...){
    return false;
  }
}

bool xmlCreate::XML_header_id(std::string id){
  try{
    InsertEle("id","header");
    InsertText("id", id);
    return true;
  }catch(...){
    return false;
  }
}

bool xmlCreate::XML_body(){
  try{
    if(element.count("body")!=0)
      throw;
    InsertEle("body","transport");
    return true;
  }catch(...){
  return false;
  }
}

std::string xmlCreate::XML_node(Consumer c){
  XML_body();
  InsertEle("node","body");
  InsertEle("nodeid","node");
  InsertText("nodeid", c.getNode_ID());
  InsertEle("userid","node");
  InsertText("userid", c.getUser_ID());
  InsertEle("privacy_lvl","node");
  InsertText("privacy_lvl", std::to_string(c.getPrivacy_lvl()));
  InsertEle("node_type","node");
  InsertText("node_type", c.getNode_Type());
  InsertEle("data_type","node");
  InsertText("data_type", c.getData_Type());
  InsertEle("interval","node");
  InsertText("interval", std::to_string(c.getinterval()));
  InsertEle("location","node");
  InsertText("location",c.getlocation());
  return return_string();
}

std::string xmlCreate::XML_node(std::vector<Consumer> c){
  XML_body();
  for(std::vector<Consumer>::iterator itr=c.begin(); itr != c.end(); itr++){
    InsertEle("node","body");
    InsertEle("nodeid","node");
    InsertText("nodeid", itr->getNode_ID());
    InsertEle("userid","node");
    InsertText("userid", itr->getUser_ID());
    InsertEle("node_type","node");
    InsertText("node_type", itr->getNode_Type());
    InsertEle("data_type","node");
    InsertText("data_type", itr->getData_Type());
    InsertEle("privacy_lvl","node");
    InsertText("privacy_lvl", std::to_string(itr->getPrivacy_lvl()));
    InsertEle("interval","node");
    InsertText("interval", std::to_string(itr->getinterval()));
    InsertEle("location","node");
    InsertText("location", itr->getlocation());
  }
  return return_string();
}

std::string xmlCreate::XML_service(Vender v){
  XML_body();
  InsertEle("service","body");
  InsertEle("serviceid","service");
  InsertText("serviceid", v.getService_ID());
  InsertEle("venderid","service");
  InsertText("venderid", v.getVender_ID());
  InsertEle("privacy_lvl","service");
  InsertText("privacy_lvl", std::to_string(v.getPrivacy_lvl()));
  InsertEle("data_type","service");
  InsertText("data_type", v.getData_Type());
  InsertEle("interval","service");
  InsertText("interval", std::to_string(v.getinterval()));
  return return_string();
}

std::string xmlCreate::XML_service(std::vector<Vender> v){
  XML_body();
  for(std::vector<Vender>::iterator itr=v.begin(); itr != v.end(); itr++){
    InsertEle("service","body");
    InsertEle("serviceid","service");
    InsertText("serviceid", itr->getService_ID());
    InsertEle("venderid","service");
    InsertText("venderid", itr->getVender_ID());
    InsertEle("privacy_lvl","service");
    InsertText("privacy_lvl", std::to_string(itr->getPrivacy_lvl()));
    InsertEle("data_type","service");
    InsertText("data_type", itr->getData_Type());
    InsertEle("interval","service");
    InsertText("interval", std::to_string(itr->getinterval()));
  }
  return return_string();
}

std::string xmlCreate::XML_relation(Relation r){
  XML_body();
  InsertEle("relation","body");
  InsertEle("relationid","relation");
  InsertText("relationid", std::to_string(r.getRelation_ID()));
  InsertEle("serviceid","relation");
  InsertText("serviceid", r.getService_ID());
  InsertEle("nodeid","relation");
  InsertText("nodeid", r.getNode_ID());
  InsertEle("anonymization_method","relation");
  InsertText("anonymization_method", r.getAnonymization());
  InsertEle("privacy_lvl","relation");
  InsertText("privacy_lvl", std::to_string(r.getPrivacy_lvl()));
  InsertEle("interval","relation");
  InsertText("interval", std::to_string(r.getinterval()));
  InsertEle("location","relation");
  InsertText("location",r.getlocation());
  return return_string();
}

std::string xmlCreate::XML_relation(std::vector<Relation> r){
  XML_body();
  for(std::vector<Relation>::iterator itr=r.begin(); itr != r.end(); itr++){
    InsertEle("relation","body");
    InsertEle("relationid","relation");
    InsertText("relationid", std::to_string(itr->getRelation_ID()));
    InsertEle("serviceid","relation");
    InsertText("serviceid", itr->getService_ID());
    InsertEle("nodeid","relation");
    InsertText("nodeid", itr->getNode_ID());
    InsertEle("anonymization_method","relation");
    InsertText("anonymization_method", itr->getAnonymization());
    InsertEle("privacy_lvl","relation");
    InsertText("privacy_lvl", std::to_string(itr->getPrivacy_lvl()));
    InsertEle("interval","relation");
    InsertText("interval", std::to_string(itr->getinterval()));
    InsertEle("location","relation");
    InsertText("location",itr->getlocation());
  }
  return return_string();
}

std::string xmlCreate::XML_auth(AUTH a){
  XML_body();
  InsertEle("auth_info","body");
  InsertEle("username","auth_info");
  InsertText("username",a.username);
  InsertEle("password","auth_info");
  InsertText("password",a.password);
  return return_string();
}

std::string xmlCreate::XML_id(std::string idname, std::string id){
  XML_body();
  InsertEle(idname,"body");
  InsertText(idname,id);
  return return_string();
}

std::string xmlCreate::XML_privacy(Service_ID serviceid, Node_ID nodeid, int privacy_lvl){
  XML_body();
  InsertEle("privacy", "body");
  InsertEle("serviceid","privacy");
  InsertText("serviceid", serviceid);
  InsertEle("nodeid", "privacy");
  InsertText("nodeid", nodeid);
  InsertEle("privacy_lvl", "privacy");
  InsertText("privacy_lvl", std::to_string(privacy_lvl));
  return return_string();
}

std::string xmlCreate::XML_delete_node(Node_ID nodeid){
  XML_body();
  InsertEle("deleteid", "body");
  InsertEle("nodeid", "deleteid");
  InsertText("nodeid", nodeid);
  return return_string();
}

std::string xmlCreate::XML_delete_service(Service_ID serviceid){
  XML_body();
  InsertEle("deleteid", "body");
  InsertEle("serviceid", "deleteid");
  InsertText("serviceid", serviceid);
  return return_string();
}

std::string xmlCreate::create_XML_newnode(Consumer c, std::string id){
  XML_transport();
  XML_header("register_newnode");
  XML_header_id(id);
  XML_node(c);
  return return_string();
}

std::string xmlCreate::create_XML_newnode(std::vector<Consumer> cv, std::string id){
  XML_transport();
  XML_header("register_newnode");
  XML_header_id(id);
  XML_node(cv);
  return return_string();
}

std::string xmlCreate::create_XML_newservice(Vender v, std::string id){
  XML_transport();
  XML_header("register_newservice");
  XML_header_id(id);
  XML_service(v);
  return return_string();
}

std::string xmlCreate::create_XML_newservice(std::vector<Vender> vv, std::string id){
  XML_transport();
  XML_header("register_newservice");
  XML_header_id(id);
  XML_service(vv);
  return return_string();
}

std::string xmlCreate::create_XML_auth(AUTH a){
  XML_transport();
  XML_header("authentication");
  XML_auth(a);
  return return_string();
}

std::string xmlCreate::create_XML_userid(std::string userid){
  XML_transport();
  XML_header("userid");
  XML_id("userid",userid);
  return return_string();
}

std::string xmlCreate::create_XML_err(){
  XML_transport();
  XML_header("err");
  return return_string();
}

std::string xmlCreate::create_XML_ok(){
  XML_transport();
  XML_header("ok");
  return return_string();
}

std::string xmlCreate::create_XML_quite(std::string id){
  XML_transport();
  XML_header("quite");
  XML_header_id(id);
  return return_string();
}

std::string xmlCreate::create_XML_privacy(Service_ID s, Node_ID n, int p, std::string id){
  XML_transport();
  XML_header("privacy");
  XML_header_id(id);
  XML_privacy(s, n, p);
  return return_string();
}

std::string xmlCreate::create_XML_delete_node(Node_ID n, std::string id){
  XML_transport();
  XML_header("delete_node");
  XML_header_id(id);
  XML_delete_node(n);
  return return_string();
}

std::string xmlCreate::create_XML_delete_service(Service_ID s, std::string id){
  XML_transport();
  XML_header("delete_node");
  XML_header_id(id);
  XML_delete_service(s);
  return return_string();
}

xmlCreate::~xmlCreate(){
  element.clear();
}

#endif
//int main(){
  //xmlCreate xmlcreate;
  //std::vector<Consumer> cv;
  //Consumer c;
  //c.setNode_ID("http://");
  //c.setUser_ID("jhon");
  //c.setPrivacy_lvl(3);
  //c.setNode_Type("sensor");
  //c.setData_Type("power");
  //c.setinterval(60);
  //c.setlocation("http://");
  //for(int i=0;i<10;i++){
  //  cv.push_back(c);
  //}
  //std::cout<<"show xml\n";
  //std::cout<<xmlcreate.create_XML_privacy("http","http",3)<<std::endl;
  //xmlcreate.Clear();
  //std::cout<<"show xml\n";
  //std::cout<<xmlcreate.create_XML_newnode(cv)<<std::endl;
  //return 0;
//}
