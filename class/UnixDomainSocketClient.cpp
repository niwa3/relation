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
  try{
    create();
    bool flag=true;
    xmlCreate xmlcreate;
    std::string xml_res;
    do{
      AUTH auth;
      std::string xml_req;
      std::cout<<"username:";
      std::cin>>std::setw(64)>>auth.username;
      std::cout<<"password:";
      std::cin>>std::setw(64)>>auth.password;
      xml_req=xmlcreate.create_XML_auth(auth);
      if(!send_XML(xml_req)){
        std::cerr<<"cant sent auth\n";
        throw;
      }
      else{
        if(get_XML(xml_res)){
          xmlParse xmlparse(xml_res);
          std::string idname;
          xmlparse.XML_id(idname,userid);
          send_response(0);
          flag=false;
        }else{
          std::cerr<<"cant get userid\n";
        }
      }
    }while(flag);
    while(1){
      handle();
      if(endflag){
        endflag=false;
        break;
      }
    }
    close(server_);
  }
  catch(...){
    close(server_);
  }
}

void UnixDomainSocketClient::close_socket(){
  try{
    if(close(server_)==-1){
      std::cerr<<"close"<<std::endl;
      throw;
    }
  }catch(...){
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
    if(connect(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr))<0){
      std::cerr<<"connect"<<std::endl;
      throw;
    }
  }
  catch(...){
    close(server_);
  }
}

void UnixDomainSocketClient::handle(){
  try{
    bool sent, success;
    char req;
    std::string xml_req;
    std::string xml_res;
    xmlCreate xmlcreate;
    std::cout<<"a:authentication\nn:newnode\ns:newservice\nc:chenge Privacy_lvl\nd:delete\nq:quite\nrequest:";
    std::cin>>req;
    switch(req){
      case 'a':{
        AUTH auth;
        std::string tmp;
        std::cout<<"username:";
        std::cin>>std::setw(64)>>auth.username;
        std::cout<<"password:";
        std::cin>>std::setw(64)>>auth.password;
        xmlcreate.Clear();
        xml_req=xmlcreate.create_XML_auth(auth);
        sent = send_XML(xml_req);
        if(!sent){
          std::cerr<<"cant sent auth\n";
          throw;
        }
        else {
          if(get_XML(xml_res)){
            xmlParse xmlparse(xml_res);
            std::string idname;
            xmlparse.XML_id(idname,userid);
            std::cout<<userid<<std::endl;
            //send_response(0);
          }else{
            std::cerr<<"cant get userid\n";
            throw;
          }
        }
        break;
               }
      case 'n':{//here
        if(!userid.empty()){
          Consumer c;
          xmlCreate xmlcreate;
          std::string text;
          int num;
          std::cout<<"Node_ID:";
          std::cin>>std::setw(64)>>text;
          c.setNode_ID(text);
          std::cout<<"User_ID:";
          std::cin>>std::setw(64)>>text;
          c.setUser_ID(text);
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
          std::cout<<"location:";
          std::cin>>text;
          c.setlocation(text);
          send_XML(xmlcreate.create_XML_newnode(c));
        }else{
          std::cout<<"prease authenticate"<<std::endl;
        }
        break;
               }
      case 'q':{
        xmlcreate.Clear();
        xml_res.clear();
        xml_res=xmlcreate.create_XML_quite();
        send_XML(xml_res);
        endflag=true;
        break;
               }
    }
  }
  catch(...){
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
      std::cout<<res<<std::endl;
      return true;
    }
  }
  catch(...){
    close(server_);
  }
}

bool UnixDomainSocketClient::get_XML(std::string &xml){
  try{
    int cc;
    int size;
    if((cc=recv(server_, &size, sizeof(size), 0))<0){
      std::cout<<"get_XML size:"<<size<<std::endl;
      send_response(1);
      return false;
    }
    send_response(0);
    char tmp[size];
    if((cc=recv(server_, &tmp, sizeof(tmp), 0))>0){
      std::cout<<tmp<<std::endl;
      xml=tmp;
      send_response(0);
      return true;
    }else{
      return false;
    }
  }
  catch(...){
    close(server_);
  }
}

bool UnixDomainSocketClient::get_response(int &r){
  try{
    int gs;
    int res;
    if((gs=recv(server_, &res, sizeof(res),0))<0){
      std::cerr<<"read"<<std::endl;
      return false;
      throw;
    }
    else{
      r=res;
      return true;
    }
  }
  catch(...){
    close(server_);
  }
}

int main(){
  UnixDomainSocketClient client;
  client.run();
}
