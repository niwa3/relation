//unixclient.cpp
#include "UnixDomainSocketClient.h"
#include <thread>

const std::string SOCKET_NAME="/tmp/unix-socket";
std::mutex m;

UnixDomainSocketClient::UnixDomainSocketClient(int i){
  name=i;
  socket_name_=SOCKET_NAME;
  num=0;
}
UnixDomainSocketClient::~UnixDomainSocketClient(){
  close(server_);
}

void UnixDomainSocketClient::run(){
  for(int i=0;i<100;i++){
    num=i;
    create();
    m.lock();
    std::cout<<"created"<<std::to_string(name)<<std::endl;
    m.unlock();
    handle();
  }
  close_socket();
}

void UnixDomainSocketClient::close_socket(){
  try{
    if(close(server_)==-1){
      std::cerr<<"close"<<std::to_string(name)<<std::endl;
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
      std::cerr<<"socket"<<std::endl;
      throw;
    }
    m.lock();
    std::cout<<"will connect"<<std::endl;
    m.unlock();
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
    m.lock();
    std::cout<<"send ack"<<std::endl;
    m.unlock();
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
    std::string ACK;
    ACK=std::to_string(name)+"hello"+std::to_string(num);
    strncpy(ack_,ACK.c_str(),sizeof(ack_)-1);
    if((ss=send(server_, ack_, sizeof(ack_), 0))<0){
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
    char res[16]={0};
    m.lock();
    std::cout<<"waiting response"<<std::endl;
    m.unlock();
    if((gs=recv(server_, res, sizeof(res),0))<0){
      std::cerr<<"read"<<std::endl;
      return false;
      throw;
    }
    else{
      std::cout<<"\""<<name<<"\""<<res<<std::endl;
      return true;
    }
  }
  catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}
int main(){
  UnixDomainSocketClient client1(1);
  UnixDomainSocketClient client2(2);
  std::thread th(&UnixDomainSocketClient::run,client1);
  std::thread th2(&UnixDomainSocketClient::run,client2);
  th.join();
  th2.join();
  return 0;
}
