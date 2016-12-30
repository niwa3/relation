//type.h
#ifndef INCLUDE_MYTYPE
#define INCLUDE_MYTYPE
#include <iostream>
#include <vector>

typedef std::string User_ID;
typedef std::string Node_ID;

typedef std::string Vender_ID;
typedef std::string Service_ID;

typedef int Relation_ID;
typedef int Privacy;//0-3

enum class Node_Type { NONE, SENSOR, ACTUATOR };
enum class Data_Type { NONE, POWER, TEMP, CO2, WIND};

const int MAXLVL=3;
const int MINLVL=0;

class Consumer{
  private:
    User_ID user_id;
    Node_ID node_id;
    Privacy privacy_lvl;
    Node_Type node_type;
    Data_Type data_type;
    int interval;
    std::string location;

  public:
    int setUser_ID(User_ID);
    int setNode_ID(Node_ID);
    int setPrivacy_lvl(Privacy);//0-3
    int setNode_Type(std::string);
    int setData_Type(std::string);
    int setinterval(int);
    int setlocation(std::string);
    User_ID getUser_ID();
    Node_ID getNode_ID();
    Privacy getPrivacy_lvl();
    std::string getNode_Type();
    std::string getData_Type();
    int getinterval();
    std::string getlocation();
    Consumer();
    ~Consumer();
};

class Vender{
  private:
    Vender_ID vender_id;
    Service_ID service_id;
    Privacy privacy_lvl;
    Data_Type data_type;
    int interval;

  public:
    int setVender_ID(Vender_ID);
    int setService_ID(Service_ID);
    int setPrivacy_lvl(Privacy);
    int setData_Type(std::string);
    int setinterval(int);
    Vender_ID getVender_ID();
    Service_ID getService_ID();
    Privacy getPrivacy_lvl();
    std::string getData_Type();
    int getinterval();
    Vender();
    ~Vender();
};

class Relation{
  private:
    enum class Anonymization_Method{ NONE, DELETE, NOISE, CHENGE} method;
    Privacy privacy_lvl;
    Relation_ID relation_id;
    Service_ID service_id;
    Node_ID node_id;
    int interval;
    std::string location;

  public:
    int setRelation_ID(Relation_ID id);
    int setAnonymization(std::string an);
    int setPrivacy_lvl(int);
    int setService_ID(Service_ID id);
    int setNode_ID(Node_ID);
    int setinterval(int);
    int setlocation(std::string);
    Relation_ID getRelation_ID();
    std::string getAnonymization();
    Privacy getPrivacy_lvl();
    Service_ID getService_ID();
    Node_ID getNode_ID();
    int getinterval();
    std::string getlocation();
    Relation();
    ~Relation();
};

struct ACK{
  //public:
  char request='\0';//n:newnode s:newservice c:chengerelation a:authentication d:delete
  char nodeid[64]={'\0'};
  char serviceid[64]={'\0'};
  int lvl=0;
};

struct AUTH{
  std::string username;
  std::string password;
};

#endif
