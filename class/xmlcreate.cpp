//xmlcreate

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

xmlCreate::~xmlCreate(){
}
