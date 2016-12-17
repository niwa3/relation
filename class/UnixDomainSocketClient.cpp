//unixclient.cpp
#include "UnixDomainSocketClient.h"

const std::string SOCKET_NAME="/tmp/unix-socket";

UnixDomainSocketClient::UnixDomainSocketClient(){
  socket_name_=SOCKET_NAME;
}
UnixDomainSocketClient::~UnixDomainSocketClient(){
  close(server_);
}

void UnixDomainSocketClient::run(){
  create();
  std::cout<<"created"<<std::endl;
  handle();
  close_socket();
}

void UnixDomainSocketClient::close_socket(){
  try{
    if(close(server_)==-1){
      std::cerr<<"close"<<std::endl;
      throw;
    }
  }catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}

void UnixDomainSocketClient::create(){
  try{
    struct sockaddr_un server_addr;

    server_addr.sun_family=AF_UNIX;
    strncpy(server_addr.sun_path, socket_name_.c_str(), sizeof(server_addr.sun_path)-1);
    server_=socket(AF_UNIX, SOCK_STREAM, 0);
    if(!server_){
      std::cout<<"socket"<<std::endl;
      throw;
    }
    std::cout<<"will connect"<<std::endl;
    if(connect(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr))<0){
      std::cerr<<"connect"<<std::endl;
      throw;
    }
  }
  catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}

void UnixDomainSocketClient::handle(){
  try{
    bool sent, success;
    sent = send_ack();
    std::cout<<"send ack"<<std::endl;
    if(!sent)throw;
    success=get_response();
    if(!success)throw;

  }
  catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}

bool UnixDomainSocketClient::send_ack(){
  try{
    int ss;
    ack_.request='n';
    strncpy(ack_.nodeid,"http://GW/sensor9",sizeof(ack_.nodeid)-1);
    std::cout<<ack_.request<<" "<<ack_.nodeid<<std::endl;
    if((ss=send(server_, &ack_, sizeof(ack_), 0))<0){
      std::cerr<<"write"<<std::endl;
      return false;
      throw;
    }else{
      return true;
    }
  }
  catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}

bool UnixDomainSocketClient::get_response(){
  try{
    int gs;
    int success;
    std::cout<<"waiting response"<<std::endl;
    if((gs=recv(server_, &success, sizeof(success),0))<0){
      std::cerr<<"read"<<std::endl;
      return false;
      throw;
    }
    else{
      std::cout<<success<<std::endl;
      return true;
    }
  }
  catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}
int main(){
  UnixDomainSocketClient client;
  client.run();
}
