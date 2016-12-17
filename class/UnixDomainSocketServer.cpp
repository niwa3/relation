#include "UnixDomainSocketServer.h"

std::string SOCK_NAME = "/tmp/unix-socket";
std::string BASE_KEY = "Key";

UnixDomainSocketServer::UnixDomainSocketServer(std::mutex *m, std::vector<std::string> *b) {
  mtx=m;
  buffer=b;
  ack_=new ACK;
  UnixDomainSocketServer::socketName_=SOCK_NAME;
  mtx->lock();
  std::cout << "UnixDomainSocketServer" << std::this_thread::get_id() << std::endl;
  mtx->unlock();
  unlink(socketName_.c_str());
}

UnixDomainSocketServer::~UnixDomainSocketServer() {
  delete(ack_);
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
      success = sendResponse(client);
      if (success) {//ここらへんで応答の確認しないと完全性が失われそう
        notifyServer();
      }
  }
}
bool UnixDomainSocketServer::getAck(int client) {
  recv(client, ack_->request, sizeof(ack_->request), 0);
  recv(client, ack_->nodeid, sizeof(ack_->nodeid), 0);
  recv(client, ack_->serviceid, sizeof(ack_->serviceid), 0);
  recv(client, ack_->lvl, sizeof(ack_->lvl), 0);
  mtx->lock();
  std::cout<<"return ack_ ="<<ack_->request<<ack_->nodeid<<ack_->serviceid<<ack_->lvl<<std::endl;
  mtx->unlock();//<----here socket 受け渡し方
  mtx->lock();
  buffer->push_back(tmp);
  mtx->unlock();
  if (ack_)
    return true;
  else
    return false;
}

bool UnixDomainSocketServer::sendResponse(int client) {
  int cc;
  char sendBuf[16] = "ok";
  mtx->lock();
  std::cout<<"will send response"<<std::endl;
  mtx->unlock();
  if ((cc = send(client, ack_, sizeof(ack_), 0)) < 0) {
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
