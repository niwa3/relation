#include "main.h"

int main(){

  std::cout<<"main"<<std::this_thread::get_id()<<std::endl;
  std::mutex* mtx=new std::mutex();
  std::vector<ACK> *buffer=new std::vector<ACK>();
  MakeRelation make(mtx,buffer);
  make.run();
  delete(mtx);
  delete(buffer);

  return 0;
}
