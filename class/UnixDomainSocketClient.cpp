//unixclient.cpp
#include "UnixDomainSocketClient.h"

const std::string SOCKET_NAME="/tmp/unix-socket";

UnixDomainSocketClient::UnixDomainSocketClient(){
  socket_name_=SOCKET_NAME;
  endflag=false;
}

UnixDomainSocketClient::~UnixDomainSocketClient(){
  close(server_);
}

void UnixDomainSocketClient::run(){
  while(1){
    create();
    std::cout<<"created"<<std::endl;
    handle();
    close_socket();
    if(endflag){
      endflag=false;
      break;
    }
  }
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
    char req;
    std::cin>>req;
    sent = send_req(req);
    if(!sent)throw;
    else{
      switch(req){
        case 'a':{
          if(get_response()){
            AUTH auth;
            std::string tmp;
            std::cin>>std::setw(64)>>tmp;
            strncpy(auth.username,tmp.c_str(),sizeof(auth.username));
            std::cin>>std::setw(64)>>tmp;
            strncpy(auth.password,tmp.c_str(),sizeof(auth.password));
            sent = send_auth(auth);
          }
          else{
            std::cerr<<"cant get response\n";
            throw;
          }
          if(!sent){
            std::cerr<<"cant sent auth\n";
            throw;
          }
          else {
            std::cout<<"get userid\n";
            if(get_userid()){
              send_response(0);
            }else{
              std::cerr<<"cant get userid\n";
              throw;
            }
          }
          break;
                 }
        case 'n':{
          if(!userid.empty()){
            if(get_response()){
              Consumer c;
              std::string text;
              int num;
              std::cout<<"Node_ID:";
              std::cin>>std::setw(64)>>text;
              c.setNode_ID(text);
              c.setUser_ID(userid);
              std::cout<<"Privacy_lvl:";
              std::cin>>num;
              c.setPrivacy_lvl(num);
              std::cout<<"Node_type(sensor or actuator):";
              std::cin>>text;
              c.setNode_Type(text);
              std::cout<<"Data_ID(power, temp, wind, co2):";
              std::cin>>text;
              c.setData_Type(text);
              std::cout<<"interval:";
              std::cin>>num;
              c.setinterval(num);
              send_XML(xmlcreate.XML_node(c));
            }
          }else{
            std::cout<<"not auth"<<std::endl;
          }
          break;
                 }
        case 'q':{
          endflag=true;
          break;
                 }
      }
    }
  }
  catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}

bool UnixDomainSocketClient::send_ack(){
  try{
    int ss;
    ack_.request='a';
    strncpy(ack_.nodeid,"http://GW/sensor9",sizeof(ack_.nodeid)-1);
    std::cout<<ack_.request<<" "<<ack_.nodeid<<std::endl;
    if((ss=send(server_, &ack_, sizeof(ack_), 0))<0){
      std::cerr<<"write"<<std::endl;
      return false;
    }else{
      return true;
    }
  }
  catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}

bool UnixDomainSocketClient::send_req(char req){
  try{
    int ss;
    std::cout<<"send request:"<<req<<std::endl;
    if((ss=send(server_, &req, sizeof(req), 0))<0){
      std::cerr<<"request\n";
      return false;
    }else{
      return true;
    }
  }
  catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}

bool UnixDomainSocketClient::send_auth(AUTH auth){
  try{
    int ss;
    std::cout<<"send username:"<<auth.username<<std::endl;
    if((ss=send(server_, &auth, sizeof(auth), 0))<0){
      std::cerr<<"request\n";
      return false;
    }else{
      return true;
    }
  }
  catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}

bool UnixDomainSocketClient::send_XML(std::string xml){
  try{
    int cc;
    int res;
    int size=xml.size();
    char tmp[size];
    strncpy(tmp,xml.c_str(),sizeof(tmp));
    std::cout<<"send size:"<<size<<std::endl;
    if((cc=send(server_, &size, sizeof(size), 0))<0){
      std::cerr<<"send size";
      return false;
    }else{
      if((cc=recv(server_, &res, sizeof(res), 0))<0){
        std::cerr<<"response res";
        return false;
      }else{
        if(res==0){
          std::cout<<"send xml:"<<tmp<<std::endl;
          if((cc=send(server_, &tmp, sizeof(tmp), 0))<0){
            std::cerr<<"send tmp";
            return false;
          }else{
            if((cc=recv(server_, &res, sizeof(res), 0))<0){
              std::cerr<<"response res2";
              return false;
            }else{
              if(res!=0){
                std::cerr<<"content err";
                return false;
              }
              std::cout<<"can send node\n";
            }
          }
        }else{
          std::cerr<<"size err";
          return false;
        }
      }
      return true;
    }
  }
  catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}

bool UnixDomainSocketClient::send_response(int res){
  try{
    int cc;
    if((cc=send(server_, &res, sizeof(res), 0))<0){
      std::cerr<<"send response"<<std::endl;
      return false;
    }else{
      return true;
    }
  }
  catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}

bool UnixDomainSocketClient::get_XML(){
  try{
    int cc;
    int size;
    if((cc=recv(server_, &size, sizeof(size), 0))<0){
      send_response(1);
      return false;
    }
    send_response(0);
    char tmp[size];
    if((cc=recv(server_, &tmp, sizeof(tmp), 0))>0){
      std::string xml=tmp;
      std::cout<<xml<<std::endl;
      return true;
    }else{
      return false;
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
    int res;
    std::cout<<"waiting response"<<std::endl;
    if((gs=recv(server_, &res, sizeof(res),0))<0){
      std::cerr<<"read"<<std::endl;
      return false;
      throw;
    }
    else{
      std::cout<<res<<std::endl;
      return true;
    }
  }
  catch(...){
    unlink(socket_name_.c_str());
    close(server_);
  }
}

bool UnixDomainSocketClient::get_userid(){
  try{
    int gs;
    char userid_tmp[64]={'\0'};
    std::cout<<"waiting userid"<<std::endl;
    if((gs=recv(server_, &userid_tmp, sizeof(userid_tmp),0))<0){
      std::cerr<<"read"<<std::endl;
      return false;
      throw;
    }
    else{
      userid=userid_tmp;
      std::cout<<userid<<std::endl;
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
