#ifndef _UNIX_DOMAIN_SOCKET_SERVER_CPP_
#define _UNIX_DOMAIN_SOCKET_SERVER_CPP_
#include "UnixDomainSocketServer.h"

const std::string SOCK_NAME = "/tmp/unix-socket";

UnixDomainSocketServer::UnixDomainSocketServer():make(&mtx,&buffer){
  UnixDomainSocketServer::socketName_=SOCK_NAME;
  mtx.lock();
  std::cout << "UnixDomainSocketServer" << std::this_thread::get_id() << std::endl;
  mtx.unlock();
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
      mtx.lock();
      std::cout << "socket running" << std::endl;
      mtx.unlock();
      if ((client = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0){
        while(client!=0){
          handle(client);
        }
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
    bool success;
    char req;
    int res;
    if ((getReq(client, req))!='\0') {
      std::cout<<req<<std::endl;
      switch(req){
        case 'a':{
          sendResponse(client, 0);
          struct AUTH auth;
          User_ID userid;
          if(getAuth(client,auth)){
            std::cout<<auth.username<<std::endl;
            if(make.auth_user(auth.username,auth.password,userid)){
              std::cout<<userid<<std::endl;
              if(sendUserID(client, userid)){
                recv(client,&res,sizeof(res),0);
              }
              else{
                std::cout<<"cant send userid\n";
                break;
              }
            }
            else{
              std::cout<<"authentication fail\n";
              sendUserID(client, "");
              break;
            }
          }else{
            std::cerr<<"cant get username\n";
            sendUserID(client, "");
            break;
          }
          break;
                 }
        case 'n':{
          xmlParse xmlparse;
          sendResponse(client, 0);
          std::string xml;
          if(getXML(client, xml)){
            Consumer c;
            xmlparse.XML_node(xml,c);
            std::cout<<c.getNode_ID()<<std::endl;
            std::cout<<c.getUser_ID()<<std::endl;
            std::cout<<c.getPrivacy_lvl()<<std::endl;
            std::cout<<c.getNode_Type()<<std::endl;
            std::cout<<c.getData_Type()<<std::endl;
            std::cout<<c.getinterval()<<std::endl;
            make.make_from_node(c);
            xmlparse.Clear();
          }
          break;
                 }
        case 's':
        case 'c':
        case 'd':
        case 'q':{
          closeSocket(client);
          break;
                 }
        default:{
          break;
                 }
      }
    }else{
      closeSocket(client);
    }
  }
  catch(...){
    closeSocket(client);
    unlink(socketName_.c_str());
  }
}

bool UnixDomainSocketServer::getReq(int& client,char &req){
  try{
    int cc;
    if((cc=recv(client, &req, sizeof(req), 0))>0){
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

bool UnixDomainSocketServer::getAuth(int& client, AUTH &auth){
  try{
    int cc;
    if((cc=recv(client, &auth, sizeof(auth), 0))>0){
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

bool UnixDomainSocketServer::getXML(int& client, std::string &xml){
  try{
    int cc;
    int size;
    if((cc=recv(client, &size, sizeof(size), 0))<0){
      sendResponse(client,1);
      return false;
    }
    sendResponse(client,0);
    char tmp[size];
    if((cc=recv(client, &tmp, sizeof(tmp), 0))>0){
      xml=tmp;
      sendResponse(client,0);
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
    //char sendBuf[16] = "ok";
    mtx.lock();
    std::cout<<"will send response"<<std::endl;
    mtx.unlock();
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

bool UnixDomainSocketServer::sendUserID(int& client, User_ID u){
  try{
    int cc;
    mtx.lock();
    std::cout<<"will send userid"<<std::endl;
    mtx.unlock();
    char userid[64]={'\0'};
    strncpy(userid,u.c_str(),sizeof(userid));
    if((cc=send(client, &userid, sizeof(userid), 0))<0){
      std::cerr<<"send";
      return false;
    }else{
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
    mtx.lock();
    std::cout<<"will send XML"<<std::endl;
    mtx.unlock();
    int size=xml.size();
    char tmp[size];
    strncpy(tmp,xml.c_str(),sizeof(tmp));
    if((cc=send(client, &size, sizeof(size), 0))<0){
      std::cerr<<"send size";
      return false;
    }else{
      if((cc=recv(client, &res, sizeof(res), 0))<0){
        std::cerr<<"response res";
        return false;
      }else{
        if(res==0){
          if((cc=send(client, &tmp, sizeof(tmp), 0))<0){
            std::cerr<<"send tmp";
            return false;
          }else{
            if((cc=recv(client, &res, sizeof(res), 0))<0){
              std::cerr<<"response res2";
              return false;
            }else{
              if(res!=0){
                std::cerr<<"content err";
                return false;
              }
            }
          }
        }else{
          std::cerr<<"size err";
          return false;
        }
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

void UnixDomainSocketServer::notifyServer() {
}

#endif
int main(){
  UnixDomainSocketServer server;
  server.run();
  return 0;
}
