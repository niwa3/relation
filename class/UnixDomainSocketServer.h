#ifndef INCLUDE_UNIXDOMAINSOCKET
#define INCLUDE_UNIXDOMAINSOCKET

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
#include <mutex>
#include <vector>
#include <atomic>
#include "type.h"
#include "MakeRelation.h"
#include "xmlcreate.h"
#include "xmlparse.h"

class UnixDomainSocketServer{
  public:
    UnixDomainSocketServer();
    ~UnixDomainSocketServer();
    void run();

  private:
    void create();
    void serve();
    void closeSocket(int&);
    void handle(int&);
    bool getXML(int&, std::string&);
    bool sendResponse(int&,int);
    bool sendUserID(int&,User_ID);
    bool sendXML(int&, std::string&);
    int server_;
    struct ACK res;
    std::string socketName_;
    std::mutex mtx;
};
#endif
