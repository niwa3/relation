#ifndef UNIX_DOMAIN_SOCKET_SERVER_CPP
#define UNIX_DOMAIN_SOCKET_SERVER_CPP
#include "UnixDomainSocketServer.h"
#include <csignal>
#include <unistd.h>

volatile sig_atomic_t eflag=0;
const std::string SOCK_NAME = "/tmp/unix-socket";

void sigpipe_handle(int x) {
    std::cerr<<"sigerr\n";
    eflag=1;
}

UnixDomainSocketServer::UnixDomainSocketServer(){
  UnixDomainSocketServer::socketName_=SOCK_NAME;
  std::cout << "UnixDomainSocketServer" << std::this_thread::get_id() << std::endl;
  unlink(socketName_.c_str());
}

UnixDomainSocketServer::~UnixDomainSocketServer() {
}

void UnixDomainSocketServer::run() {
  create();
  serve();
}

void UnixDomainSocketServer::create() {
  try{
    struct sockaddr_un server_addr;
    int soval = 1;

    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, socketName_.c_str(), sizeof(server_addr.sun_path) -1);

    server_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if (!server_) {
      std::cerr<<"socket";
      throw;
    }
    if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1 ) {
      std::cerr<<"setsockopt";
      throw;
    }
    if (bind(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
      std::cerr<<"bind";
      throw;
    }
    if (listen(server_, 10) < 0) {
      std::cerr<<"listen";
      throw;
    }
  }
  catch(...){
    unlink(socketName_.c_str());
  }
}

void UnixDomainSocketServer::serve() {
  int client=0;
  try{
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);
    while (1) {
      if ((client = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0){
        //while(client!=0 && eflag==0){
        //  handle(client);
        //}
        //eflag=0;
        //client=0;
        handle(client);
      }
    }
    closeSocket(client);
  }
  catch(...){
    closeSocket(client);
    unlink(socketName_.c_str());
  }
}

void UnixDomainSocketServer::handle(int& client) {
  try{
    MakeRelation make;
    bool success;
    std::string method;
    int res;
    std::string xml;
    std::string xml_res;
    if ((getXML(client, xml))!='\0') {
      xmlParse xmlparse(xml);
      xmlparse.XML_transport();
      xmlCreate xmlcreate;
      if(xmlparse.XML_header(method)){
        if(method=="authentication"){
          struct AUTH auth;
          User_ID userid;
          if(xmlparse.XML_auth(auth)){
            if(make.auth_user(auth.username,auth.password,userid)){
              xml_res.clear();
              xml_res=xmlcreate.create_XML_userid(userid);
              if(!sendXML(client, xml_res)){
                std::cerr<<"cant send userid\n";
              }
            }
            else{
              xmlcreate.Clear();
              xml_res.clear();
              xml_res=xmlcreate.create_XML_err();
              sendXML(client, xml_res);
            }
          }else{
            std::cerr<<"cant get username\n";
            xmlcreate.Clear();
            xml_res.clear();
            xml_res=xmlcreate.create_XML_err();
            sendXML(client, xml_res);
          }
        }
        else if(method=="register_newnode"){
          Consumer c;
          std::string id;
          xmlparse.XML_header_id(id);
          if(xmlparse.XML_node(c)){
            if(make.make_from_node(c)){
              xmlcreate.Clear();
              xml_res.clear();
              xml_res=xmlcreate.create_XML_ok();
              sendXML(client, xml_res);
            }
            else{
              xmlcreate.Clear();
              xml_res.clear();
              xml_res=xmlcreate.create_XML_err();
              sendXML(client, xml_res);
            }
          }
        }
        else if(method=="register_newservice"){
          Vender v;
          std::string id;
          xmlparse.XML_header_id(id);
          if(xmlparse.XML_service(v)){
            if(make.make_from_service(v)){
             xmlcreate.Clear();
             xml_res.clear();
             xml_res=xmlcreate.create_XML_ok();
             sendXML(client, xml_res);
            }
            else{
              xmlcreate.Clear();
              xml_res.clear();
              xml_res=xmlcreate.create_XML_err();
              sendXML(client, xml_res);
            }
          }
        }
        else if(method=="privacy"){
          std::string s;
          std::string n;
          int p;
          std::string id;
          xmlparse.XML_header_id(id);
          if(xmlparse.XML_privacy(s,n,p)){
            if(make.change_privacy_from_node(s,n,p)){
             xmlcreate.Clear();
             xml_res.clear();
             xml_res=xmlcreate.create_XML_ok();
             sendXML(client, xml_res);
            }
            else{
              xmlcreate.Clear();
              xml_res.clear();
              xml_res=xmlcreate.create_XML_err();
              sendXML(client, xml_res);
            }
          }
        }
        else if(method=="delete_node"){
          std::string n;
          std::string id;
          xmlparse.XML_header_id(id);
          if(xmlparse.XML_delete_node(n)){
            if(make.delete_node(n)){
              xmlcreate.Clear();
              xml_res.clear();
              xml_res=xmlcreate.create_XML_ok();
              sendXML(client, xml_res);
            }
            else{
              xmlcreate.Clear();
              xml_res.clear();
              xml_res=xmlcreate.create_XML_err();
              sendXML(client, xml_res);
            }
          }
        }
        else if(method=="delete_service"){
          std::string s;
          std::string id;
          xmlparse.XML_header_id(id);
          if(xmlparse.XML_delete_service(s)){
            if(make.delete_service(s)){
              xmlcreate.Clear();
              xml_res.clear();
              xml_res=xmlcreate.create_XML_ok();
              sendXML(client, xml_res);
            }
            else{
              xmlcreate.Clear();
              xml_res.clear();
              xml_res=xmlcreate.create_XML_err();
              sendXML(client, xml_res);
            }
          }
        }
        else if(method=="quite"){
          closeSocket(client);
        }
      }
      xmlparse.Clear();
      xmlcreate.Clear();
    }
    else{
      closeSocket(client);
    }
  }
  catch(...){
    closeSocket(client);
    unlink(socketName_.c_str());
  }
}

bool UnixDomainSocketServer::getXML(int& client, std::string &xml){
  try{
    int cc;
    //char buffer[16]={'\0'};
    int size =0;
    //std::stringstream ss;
    if((cc=recv(client, &size, sizeof(size), 0))<0){
      return false;
    }
    //std::cout<<buffer<<std::endl;
    //ss<<buffer;
    //ss>>size;
    char tmp[size];
    //ss.str("");
    //ss.clear();
    if((cc=recv(client, &tmp, sizeof(tmp), 0))>0){
      std::stringstream ss;
      xml=tmp;
      return true;
    }else{
      return false;
    }
  }
  catch(...){
    closeSocket(client);
    unlink(socketName_.c_str());
  }
}

bool UnixDomainSocketServer::sendResponse(int& client, int res) {
  try{
    int cc;
    if ((cc=send(client, &res, sizeof(res), 0))<0) {
      std::cerr<<"send";
      return false;
    } else {
      return true;
    }
  }
  catch(...){
    closeSocket(client);
    unlink(socketName_.c_str());
  }
}

bool UnixDomainSocketServer::sendXML(int& client, std::string& xml){
  try{
    int cc;
    int res;
    int size=xml.size();
    char tmp[size];
    strncpy(tmp,xml.c_str(),sizeof(tmp));
    //std::stringstream ss;
    //char buffer[4]={'\0'};
    //std::cout<<size<<std::endl;
    //ss<<size;
    //ss>>buffer;
    //std::cout<<buffer<<std::endl;
    if((cc=send(client, &size, sizeof(size), 0))<0){
      std::cerr<<"send size";
      return false;
    }else{
      while((cc=send(client, &tmp, sizeof(tmp), 0))<0){
        std::cerr<<"send tmp";
        //return false;
      }
      return true;
    }
  }
  catch(...){
    closeSocket(client);
    unlink(socketName_.c_str());
  }
}

void UnixDomainSocketServer::closeSocket(int &client) {
  close(client);
  client=0;
}


#endif
int main(){
  std::signal(SIGPIPE,sigpipe_handle);
  UnixDomainSocketServer server;
  server.run();
  return 0;
}
