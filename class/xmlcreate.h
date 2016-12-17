//xmlcreate.h
#ifndef INCLUDED_MYXMLCREATE
#define INCLUDED_MYXMLCREATE

#include <iostream>
#include <tinyxml2.h>
#include <memory>
#include <map>

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
  ~xmlCreate();
};



#endif

