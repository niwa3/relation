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

class UnixDomainSocketServer{
  public:
    UnixDomainSocketServer(std::mutex*, std::vector<ACK>*, int*);
    ~UnixDomainSocketServer();
    void run();

  private:
    void create();
    void serve();
    void closeSocket();
    void handle(int);
    void notifyServer();
    bool getAck(int);
    bool sendResponse(int,int);

    int server_;
    struct ACK res;
    std::string socketName_;
    std::string basekey_;
    std::mutex *mtx;
    std::vector<ACK> *buffer;
    int *req_success;
};

#endif
