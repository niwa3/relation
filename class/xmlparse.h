#ifndef INCLUDED_XMLPARSE
#define INCLUDED_XMLPARSE

#include <iostream>
#include <tinyxml2.h>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include "type.h"

typedef std::string ELEMENTNAME;
typedef tinyxml2::XMLElement* ELEMENT;

class xmlParse{
  private:
    tinyxml2::XMLDocument xml;
    std::map<ELEMENTNAME, ELEMENT> element;

  public:
    xmlParse();
    xmlParse(std::string);
    ~xmlParse();
    void Parse(std::string);
    void Print();
    void Clear();
    void SaveFile(std::string);
    void LoadFile(std::string);
    void GetEle(ELEMENTNAME);
    void GetEle(ELEMENTNAME,std::string);
    std::string GetEleinEle(ELEMENTNAME dst);
    bool GetNextEle(ELEMENTNAME);
    std::string GetText(ELEMENTNAME);
    std::string GetAtt(ELEMENTNAME,std::string);

    bool XML_transport();
    bool XML_header(std::string &method);
    bool XML_header_id(std::string &id);
    bool XML_body();
    bool XML_node(Consumer&);
    bool XML_node(std::vector<Consumer>&);
    bool XML_service(Vender&);
    bool XML_service(std::vector<Vender>&);
    bool XML_relation(Relation&);
    bool XML_relation(std::vector<Relation>&);
    bool XML_auth(AUTH&);
    bool XML_id(std::string &idname, std::string &id);
    bool XML_privacy(std::string &serviceid, std::string &nodeid, int &req);
    bool XML_delete_node(std::string&);
    bool XML_delete_service(std::string&);
};

#endif
