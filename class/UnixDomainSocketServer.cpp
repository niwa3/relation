#include "UnixDomainSocketServer.h"

std::string SOCK_NAME = "/tmp/unix-socket";

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
  int client;
  struct sockaddr_in client_addr;
  socklen_t clientlen = sizeof(client_addr);
  while (1) {
    mtx.lock();
    std::cout << "socket running" << std::endl;
    mtx.unlock();
    if ((client = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0)
      handle(client);
  }
  closeSocket();
}

void UnixDomainSocketServer::handle(int client) {
  bool success;
  char req;
  if ((req=getReq(client, req))!='\0') {
    switch(req){
      case 'a':{
        struct AUTH auth;
        if(getAuth(client,auth)){
          
        };
        break;
               }
      case 'n':
      case 's':
      case 'c':
      case 'd':
      default:
    }
    std::cout<<"sendResponse"<<std::endl;
    success = sendResponse(client,0);
    if (success) {//ここらへんで応答の確認しないと完全性が失われそう
      notifyServer();
    }
  }else{
    success = sendResponse(client,1);
    if(success){
      notifyServer();
    }
  }
}
bool UnixDomainSocketServer::getAck(int client) {
  int cc;
  if((cc=recv(client, &res, sizeof(res), 0))<0)return false;
  else{
    mtx.lock();
    std::cout<<"recv ="<<res.request<<" "<<res.nodeid<<" "<<res.serviceid<<" "<<res.lvl<<std::endl;
    buffer.push_back(res);
    mtx.unlock();//<----here socket 受け渡し方
    //mtx.lock();
    //buffer.push_back(tmp);
    //mtx.unlock();
    return true;
  }
}

bool UnixDomainSocketServer::getReq(int client,char &req){
  int cc;
  if((cc=recv(client, &req, sizeof(req), 0))>0){
    return true;
  }else{
    return false;
  }
}

bool UnixDomainSocketServer::getAuth(int client, AUTH &auth){
  int cc;
  if((cc=recv(client, &auth, sizeof(auth), 0))>0){
    return true;
  }else{
    return false;
  }
}


bool UnixDomainSocketServer::sendResponse(int client, int success) {
  int cc;
  //char sendBuf[16] = "ok";
  mtx.lock();
  std::cout<<"will send response"<<std::endl;
  mtx.unlock();
  if ((cc=send(client, &success, sizeof(success), 0))<0) {
    std::cerr<<"send";
    return false;
  } else {
    return true;
  }
}

void UnixDomainSocketServer::closeSocket() {
  unlink(socketName_.c_str());
}

void UnixDomainSocketServer::notifyServer() {
}
