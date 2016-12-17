//unixclient.h
#ifndef _INCLUDE_UNIXCLIENT_
#define _INCLUDE_UNIXCLIENT_

#include <errno.h>
#include <netdb.h>
#include <string>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <fstream>
#include <iostream>

class UnixDomainSocketClient{
  public:
    UnixDomainSocketClient(int);
    ~UnixDomainSocketClient();
    void run();
  private:
    void create();
    void handle();
    bool send_ack();
    bool get_response();
    void close_socket();

    int server_;
    char ack_[100]={'\0'};
    std::string socket_name_;
    int name;
    int num;
};


#endif
