#include "main.h"

int main(){

  std::cout<<"main"<<std::this_thread::get_id()<<std::endl;
  std::mutex* mtx=new std::mutex();
  std::vector<std::string> *buffer=new std::vector<std::string>();
  UnixDomainSocketServer socket(mtx,buffer);
  std::thread th(&UnixDomainSocketServer::run, socket);
  while(1){
    while(buffer->empty()){
      std::this_thread::yield;
    }
    mtx->lock();
    std::vector<std::string>::iterator itr=buffer->begin();
    std::cout<<*itr<<std::endl;
    buffer->erase(itr);
    mtx->unlock();
  }
  th.join();
  delete(mtx);
  delete(buffer);

  return 0;
}
