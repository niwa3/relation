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

class ACK{
  public:
  char *request;//n:newnode s:newservice c:chengerelation a:authentication
  char nodeid[64];
  char serviceid[64];
  int *lvl;
  public:
  ACK(){
    request=new char();
    lvl=new int();
  };
  ~ACK(){
    delete(request);
    delete(lvl);
  };
};

class UnixDomainSocketServer{
  public:
    UnixDomainSocketServer(std::mutex*, std::vector<std::string>*);
    ~UnixDomainSocketServer();
    void run();

  private:
    void create();
    void serve();
    void closeSocket();
    void handle(int);
    void notifyServer();
    bool getAck(int);
    bool sendResponse(int);

    int server_;
    struct ACK *ack_;
    std::string socketName_;
    std::string basekey_;
    std::mutex *mtx;
    std::vector<std::string> *buffer;
};

#endif
