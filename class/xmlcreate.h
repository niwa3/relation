//xmlcreate.h
#ifndef INCLUDED_MYXMLCREATE
#define INCLUDED_MYXMLCREATE

#include <iostream>
#include <tinyxml2.h>
#include <memory>
#include <map>
#include "type.h"

typedef std::string ELEMENTNAME;
typedef tinyxml2::XMLElement* ELEMENT;

class xmlCreate{
  private:
    tinyxml2::XMLDocument xml;
    tinyxml2::XMLDeclaration *decl;
    std::map<ELEMENTNAME, ELEMENT> element;
  public:
    xmlCreate();
    tinyxml2::XMLDocument* getXML();
    void InsertEle(std::string e);
    void InsertEle(std::string e, std::string dst);
    void SetAtt(ELEMENTNAME e,std::string n, std::string v);
    void InsertText(ELEMENTNAME e,std::string t);
    void Print();
    void SaveFile(std::string);
    void Clear();
    std::string return_string();

    bool XML_transport();
    bool XML_header(std::string);
    bool XML_header_id(std::string);
    bool XML_body();
    std::string XML_node(Consumer);
    std::string XML_node(std::vector<Consumer>);
    std::string XML_service(Vender);
    std::string XML_service(std::vector<Vender>);
    std::string XML_relation(Relation);
    std::string XML_relation(std::vector<Relation>);
    std::string XML_auth(AUTH);
    std::string XML_id(std::string idname,std::string id);
    std::string XML_privacy(std::string serviceid, std::string nodeid, int privacy_lvl);
    std::string XML_delete_node(std::string nodeid);
    std::string XML_delete_service(std::string serviceid);
    std::string create_XML_newnode(Consumer, std::string);
    std::string create_XML_newnode(std::vector<Consumer>, std::string);
    std::string create_XML_newservice(Vender, std::string);
    std::string create_XML_newservice(std::vector<Vender>, std::string);
    std::string create_XML_auth(AUTH);
    std::string create_XML_userid(std::string);
    std::string create_XML_privacy(Service_ID, Node_ID, int, std::string);
    std::string create_XML_delete_node(Node_ID, std::string);
    std::string create_XML_delete_service(Service_ID, std::string);
    std::string create_XML_err();
    std::string create_XML_ok();
    std::string create_XML_quite(std::string);
    ~xmlCreate();
};

#endif
