#ifndef _INCLUDE_UNIXDOMAINSOCKET_
#define _INCLUDE_UNIXDOMAINSOCKET_

#include <limits>
#include <sys/socket.h>
#include <sys/un.h>
#include <thread>
#include <list>
#include <mutex>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <mutex>
#include <vector>
#include <atomic>
#include "type.h"
#include "MakeRelation.h"

class UnixDomainSocketServer{
  public:
    UnixDomainSocketServer();
    ~UnixDomainSocketServer();
    void run();

  private:
    void create();
    void serve();
    void closeSocket();
    void handle(int);
    void notifyServer();
    bool getAck(int);
    bool getReq(int,char&);
    bool getID(int);//Node_ID,Service_ID,User_ID,Vender_ID 
    bool getAuth(int,AUTH&);
    bool sendResponse(int,int); 
    int server_;
    struct ACK res;
    std::string socketName_;
    std::mutex mtx;
    std::vector<ACK> buffer;
    MakeRelation make;
};
#endif
