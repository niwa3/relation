#include "UnixDomainSocketServer.h"

std::string SOCK_NAME = "/tmp/unix-socket";

UnixDomainSocketServer::UnixDomainSocketServer(std::mutex *m, std::vector<ACK> *b, int *s) {
  mtx=m;
  buffer=b;
  req_success=s;
  UnixDomainSocketServer::socketName_=SOCK_NAME;
  mtx->lock();
  std::cout << "UnixDomainSocketServer" << std::this_thread::get_id() << std::endl;
  mtx->unlock();
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
    mtx->lock();
    std::cout << "socket running" << std::endl;
    mtx->unlock();
    if ((client = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0)
      handle(client);
  }
  closeSocket();
}

void UnixDomainSocketServer::handle(int client) {
  bool success;
  if (getAck(client)) {
    while(*req_success){
      std::this_thread::yield();
    }
    if(req_success==0){
      std::cout<<"sendResponse"<<req_success<<std::endl;
      success = sendResponse(client,0);
      *req_success=1;
      if (success) {//ここらへんで応答の確認しないと完全性が失われそう
        notifyServer();
      }
    }
    else{
      success = sendResponse(client,1);
      *req_success=1;
    }
  }
}
bool UnixDomainSocketServer::getAck(int client) {
  recv(client, &res, sizeof(res), 0);
  mtx->lock();
  std::cout<<"recv ="<<res.request<<" "<<res.nodeid<<" "<<res.serviceid<<" "<<res.lvl<<std::endl;
  buffer->push_back(res);
  mtx->unlock();//<----here socket 受け渡し方
  //mtx->lock();
  //buffer->push_back(tmp);
  //mtx->unlock();
  if (res.request)
    return true;
  else
    return false;
}

bool UnixDomainSocketServer::sendResponse(int client, int success) {
  int cc;
  //char sendBuf[16] = "ok";
  mtx->lock();
  std::cout<<"will send response"<<std::endl;
  mtx->unlock();
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
