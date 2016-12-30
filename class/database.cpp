#ifndef MY_DATABASE_CPP
#define MY_DATABASE_CPP
#include "database.h"
typedef std::string VALUEERR;

//=============class DataBase===============
DataBase::DataBase(std::string call){
  DataBase::conn.reset(new pqxx::connection(call));
  DataBase::T.reset(new pqxx::work(*DataBase::conn));
}

DataBase::~DataBase(){
  DataBase::T.get()->commit();
}

bool DataBase::insertValue(Consumer c){
  try{
    if(c.getNode_ID().empty()){
      VALUEERR err = "no nodeid.";
      throw err;
    }
    else if(c.getUser_ID().empty()){
      VALUEERR err = "no userid.";
      throw err;
    }
    else if(c.getPrivacy_lvl()>MAXLVL || c.getPrivacy_lvl()<MINLVL){
      VALUEERR err = "no privacy.";
      throw err;
    }
    else if(c.getNode_Type().empty()){
      VALUEERR err = "no nodetype.";
      throw err;
    }
    else if(c.getData_Type().empty()){
      VALUEERR err = "no datatype.";
      throw err;
    }
    else if(c.getinterval()<0){
      VALUEERR err = "interval";
      throw err;
    }
    else if(c.getlocation().empty()){
      VALUEERR err = "no location";
      throw err;
    }
    pqxx::result result=T.get()->exec(
        "SELECT * "
        "FROM node "
        "WHERE nodeid =" +T.get()->quote(c.getNode_ID()));

    if(result.size() != 0){
      std::cerr<<c.getNode_ID()<<" is existing."<<std::endl;
      return false;
    }
    else{
      T.get()->exec(
          "INSERT INTO node "
          "VALUES (" + T.get()->quote(c.getNode_ID()) + "," + T.get()->quote(c.getUser_ID()) + "," + T.get()->quote(c.getPrivacy_lvl()) + "," +T.get()->quote(c.getNode_Type()) + "," + T.get()->quote(c.getData_Type()) + "," + std::to_string(c.getinterval()) + "," + T.get()->quote(c.getlocation()) + ");");
      return true;
    }
  }
  catch(VALUEERR e){
    std::cerr<<e<<std::endl;
    return false;
  }
  catch(const pqxx::sql_error& e){
    std::cerr<<e.what()<<": SQL->"<<"select id from test"<<std::endl;
    return false;
  }
  catch(const pqxx::usage_error& e){
    std::cerr<<e.what()<<std::endl;
    return false;
  }
}


bool DataBase::insertValue(Vender v){
  try{
    if(v.getService_ID().empty()){
      VALUEERR err = "no serviceid.";
      throw err;
    }
    else if(v.getVender_ID().empty()){
      VALUEERR err = "no venderid.";
      throw err;
    }
    else if(v.getPrivacy_lvl()>MAXLVL || v.getPrivacy_lvl()<MINLVL){
      VALUEERR err = "no privacy.";
      throw err;
    }
    else if(v.getData_Type().empty()){
      VALUEERR err = "no servicetype.";
      throw err;
    }
    else if(v.getinterval()==0){
      VALUEERR err = "interval";
      throw err;
    }

    pqxx::result result=T.get()->exec(
        "SELECT * "
        "FROM service "
        "WHERE serviceid =" +T.get()->quote(v.getService_ID()));

    if(result.size() != 0){
      std::cerr<<v.getService_ID()<<" is existing."<<std::endl;
      return false;
    }
    else{
      T.get()->exec(
          "INSERT INTO service "
          "VALUES (" + T.get()->quote(v.getService_ID()) + "," + T.get()->quote(v.getVender_ID()) + "," + T.get()->quote(v.getPrivacy_lvl()) + "," +T.get()->quote(v.getData_Type()) + "," + std::to_string(v.getinterval()) + ")");
      return true;
    }
  }
  catch(VALUEERR e){
    std::cerr<< e <<std::endl;
    return false;
  }
  catch(const pqxx::sql_error& e){
    std::cerr<<e.what()<<": SQL->"<<"select id from test"<<std::endl;
    return false;
  }
  catch(const pqxx::usage_error& e){
    std::cerr<<e.what()<<std::endl;
    return false;
  }
}



bool DataBase::insertValue(Relation r){
  try{
    if(r.getAnonymization().empty()){
      VALUEERR err = "no anonymous.";
      throw err;
    }
    else if(r.getPrivacy_lvl()>MAXLVL || r.getPrivacy_lvl()<MINLVL){
      VALUEERR err = "no privacy.";
      throw err;
    }
    else if(r.getNode_ID().empty()){
      VALUEERR err = "no node.";
      throw err;
    }
    else if(r.getService_ID().empty()){
      VALUEERR err = "no service.";
      throw err;
    }
    else if(r.getinterval()<0){
      VALUEERR err = "interval";
      throw err;
    }
    else if(r.getlocation().empty()){
      VALUEERR err = "location";
      throw err;
    }
  }
  catch (VALUEERR e){
    std::cerr<< e << std::endl;
    return false;
  }
  try{
    pqxx::result result=T.get()->exec(
        "SELECT relationid "
        "FROM relation "
        "WHERE nodeid = " + T.get()->quote(r.getNode_ID()) + " "
        "AND serviceid = " + T.get()->quote(r.getService_ID()));
    if(!result.empty()){
      std::cout<<result.begin()["relationid"].as<int>()<<" is exist"<<std::endl;
      return false;
    }
    result=T.get()->exec(
        "SELECT coalesce(max(relationid), 0) +1 AS gap "
        "FROM (SELECT relationid, Row_Number() OVER(order by relationid) AS Rn FROM relation) a "
        "WHERE relationid = Rn");
    pqxx::result::iterator tmp;
    tmp=result.begin();
    r.setRelation_ID(tmp["gap"].as<int>());

    T.get()->exec(
        "INSERT INTO relation "
        "VALUES (" + std::to_string(r.getRelation_ID()) + "," + T.get()->quote(r.getService_ID()) + "," + T.get()->quote(r.getNode_ID()) + "," + std::to_string(r.getPrivacy_lvl()) + "," + T.get()->quote(r.getAnonymization()) + "," + std::to_string(r.getinterval()) + "," + T.get()->quote(r.getlocation()) + ")");
    return true;
  }
  catch(const pqxx::sql_error& e){
    std::cerr<<e.what()<<": SQL->"<<"select id from test"<<std::endl;
    return false;
  }
  catch(const pqxx::usage_error& e){
    std::cerr<<e.what()<<std::endl;
    return false;
  }
}



bool DataBase::deleteValue(std::string kind, std::string id){
  try{
    if(id.empty()){
      VALUEERR err = "no id.";
      throw err;
    }
  }
  catch (VALUEERR e){
    std::cerr<< e << std::endl;
    return false;
  }

  try{
    if(kind=="node"){
      T.get()->exec(
          "DELETE "
          "FROM node "
          "WHERE nodeid =" +T.get()->quote(id));
     return true;
    }
    if(kind=="service"){
      T.get()->exec(
          "DELETE "
          "FROM service "
          "WHERE serviceid =" + T.get()->quote(id));
      return true;
    }
  }
  catch(const pqxx::sql_error& e){
    std::cerr<<e.what()<<": SQL->"<<"select id from test"<<std::endl;
    return false;
  }
  catch(const pqxx::usage_error& e){
    std::cerr<<e.what()<<std::endl;
    return false;
  }
}



bool DataBase::deleteRelation(Node_ID nodeid, Service_ID serviceid){
  try{
    if(nodeid.empty()){
      VALUEERR err = "no nodeid.";
      throw err;
    }
    else if(serviceid.empty()){
      VALUEERR err = "no serviceid.";
      throw err;
    }
  }
  catch (VALUEERR e){
    std::cerr<< e << std::endl;
    return false;
  }
  try{
    T.get()->exec(
        "DELETE "
        "FROM relation "
        "WHERE serviceid = " + T.get()->quote(serviceid) + " AND nodeid = " + T.get()->quote(nodeid));
    return true;
  }
  catch(const pqxx::sql_error& e){
    std::cerr<<e.what()<<": SQL->"<<"select id from test"<<std::endl;
    return false;
  }
  catch(const pqxx::usage_error& e){
    std::cerr<<e.what()<<std::endl;
    return false;
  }
}

bool DataBase::selectValue(std::string req, std::vector<Consumer> &c_res){
  try{
    pqxx::result r=T.get()->exec(
        "SELECT * "
        "FROM node "
        "WHERE " + req);
    for(pqxx::result::iterator it=r.begin();it!=r.end();it++){
      Consumer tmp;
      tmp.setNode_ID(it["nodeid"].as<std::string>());
      tmp.setUser_ID(it["userid"].as<std::string>());
      tmp.setPrivacy_lvl(it["privacy_lvl"].as<int>());
      tmp.setNode_Type(it["node_type"].as<std::string>());
      tmp.setData_Type(it["data_type"].as<std::string>());
      tmp.setinterval(it["interval"].as<int>());
      tmp.setlocation(it["location"].as<std::string>());
      c_res.push_back(tmp);
    }
    return true;
  }
  catch(std::string e){
    std::cerr<<e<<std::endl;
  }
  catch(const pqxx::sql_error& e){
    std::cerr<<e.what()<<": SQL->"<<"select id from test"<<std::endl;
    return false;
  }
  catch(const pqxx::usage_error& e){
    std::cerr<<e.what()<<std::endl;
    return false;
  }
}



bool DataBase::selectValue(std::string req, std::vector<Vender> &v_res){
  try{
    pqxx::result r=T.get()->exec(
        "SELECT * "
        "FROM service "
        "WHERE " + req);
    for(pqxx::result::iterator it=r.begin();it!=r.end();it++){
      Vender tmp;
      tmp.setService_ID(it["serviceid"].as<std::string>());
      tmp.setVender_ID(it["venderid"].as<std::string>());
      tmp.setPrivacy_lvl(it["privacy_lvl"].as<int>());
      tmp.setData_Type(it["data_type"].as<std::string>());
      tmp.setinterval(it["interval"].as<int>());
      v_res.push_back(tmp);
    }
    return true;
  }
  catch(std::string e){
    std::cerr<<e<<std::endl;
  }
  catch(const pqxx::sql_error& e){
    std::cerr<<e.what()<<": SQL->"<<"select id from test"<<std::endl;
    return false;
  }
  catch(const pqxx::usage_error& e){
    std::cerr<<e.what()<<std::endl;
    return false;
  }
}



bool DataBase::selectValue(std::string req, std::vector<Relation> &r_res){
  try{
    pqxx::result r=T.get()->exec(
        "SELECT * "
        "FROM relation "
        "WHERE " + req);
    for(pqxx::result::iterator it=r.begin();it!=r.end();it++){
      Relation tmp;
      tmp.setRelation_ID(it["relationid"].as<int>());
      tmp.setNode_ID(it["nodeid"].as<std::string>());
      tmp.setService_ID(it["serviceid"].as<std::string>());
      tmp.setAnonymization(it["anonymization_method"].as<std::string>());
      tmp.setPrivacy_lvl(it["privacy_lvl"].as<int>());
      tmp.setinterval(it["interval"].as<int>());
      tmp.setlocation(it["location"].as<std::string>());
      r_res.push_back(tmp);
    }
    return true;
  }
  catch(std::string e){
    std::cerr<<e<<std::endl;
  }
  catch(const pqxx::sql_error& e){
    std::cerr<<e.what()<<": SQL->"<<"select id from test"<<std::endl;
    return false;
  }
  catch(const pqxx::usage_error& e){
    std::cerr<<e.what()<<std::endl;
    return false;
  }
}

std::string DataBase::quote(std::string in){
  return T.get()->quote(in);
}

bool DataBase::updataRelationPrivacy(Node_ID nodeid, Service_ID serviceid, int lvl){
  try{
    pqxx::result result=T.get()->exec("SELECT relationid FROM relation WHERE nodeid = " + T.get()->quote(nodeid) + "AND serviceid = " + T.get()->quote(serviceid));
    if(result.empty())return false;
    T.get()->exec("UPDATE relation SET privacy_lvl = " + std::to_string(lvl) + " WHERE relationid = " + result.begin()["relationid"].as<std::string>());
    return true;
  }
  catch(const pqxx::sql_error& e){
    std::cerr<<e.what()<<": SQL->"<<"select relationid from relation"<<std::endl;
    return false;
  }
  catch(const pqxx::usage_error& e){
    std::cerr<<e.what()<<std::endl;
    return false;
  }
  catch(...){
    std::cerr<<"err\n";
    return false;
  }
}

bool DataBase::authUser(std::string username,std::string password, std::string &userid){
  try{
    pqxx::result result=T.get()->exec("SELECT * FROM users WHERE username = " + T.get()->quote(username));
    if(result.empty())return false;
    else{
      std::string salt;
      pqxx::result::iterator itr=result.begin();
      salt=itr["salt"].as<std::string>();
      if(itr["password"].as<std::string>()==mysha256(salt+password)){
        userid=itr["userid"].as<std::string>();
        return true;
      }else return false;
    }
  }
  catch(const pqxx::sql_error& e){
    std::cerr<<e.what()<<": SQL->"<<"select relationid from relation"<<std::endl;
    return false;
  }
  catch(const pqxx::usage_error& e){
    std::cerr<<e.what()<<std::endl;
    return false;
  }
  catch(...){
    std::cerr<<"err\n";
    return false;
  }
}

bool DataBase::authVender(std::string vendername,std::string password, std::string &venderid){
  try{
    pqxx::result result=T.get()->exec("SELECT * FROM venders WHERE vendername = " + T.get()->quote(vendername));
    if(result.empty())return false;
    else{
      std::string salt;
      pqxx::result::iterator itr=result.begin();
      salt=itr["salt"].as<std::string>();
      if(itr["password"].as<std::string>()==mysha256(salt+password)){
        venderid=itr["venderid"].as<std::string>();
        return true;
      }else return false;
    }
  }
  catch(const pqxx::sql_error& e){
    std::cerr<<e.what()<<": SQL->"<<"select relationid from relation"<<std::endl;
    return false;
  }
  catch(const pqxx::usage_error& e){
    std::cerr<<e.what()<<std::endl;
    return false;
  }
  catch(...){
    std::cerr<<"err\n";
    return false;
  }
}

bool DataBase::insertUser(std::string username, std::string password){
  try{
    std::string salt;
    salt="testsalt";
    std::string hashedpass;
    hashedpass=mysha256("testsalt"+password);
    std::string userid="u00001";
    T.get()->exec("INSERT INTO users "
        "VALUES (" + T.get()->quote(username) +
        ", " + T.get()->quote(hashedpass) +
        ", " + T.get()->quote(salt) +
        ", " + T.get()->quote(userid) + ")");
    return true;
  }
  catch(const pqxx::sql_error& e){ std::cerr<<e.what()<<": SQL->"<<"select relationid from relation"<<std::endl;
    return false;
  }
  catch(const pqxx::usage_error& e){
    std::cerr<<e.what()<<std::endl;
    return false;
  }
  catch(...){
    std::cerr<<"err\n";
  }
}

//==========================================


//===============splitarray=================
std::vector<std::string> splitarray(std::string str){
  size_t c;
  while((c=str.find_first_of(" {}")) != std::string::npos){
      str.erase(c,1);
  }
  return split(str,',');
}
//==========================================

//================string split===================
std::vector<std::string> split(const std::string &str, char sep){
  std::vector<std::string> v;
  std::stringstream ss(str);
  std::string buffer;
  while( std::getline(ss, buffer, sep) ){
    v.push_back(buffer);
  }
  return v;
}
//===============================================


#endif
//int main(){
//  DataBase db("dbname=test user=testuser password=testpass");
//  Consumer c[10];
//  for(int i=0;i<10;i++){
//  c[i].setNode_ID("http://GW/sensor"+std::to_string(i));
//  c[i].setUser_ID("jhon");
//  if(i%3==0)  c[i].setPrivacy_lvl(1);
//  else if(i%3==1) c[i].setPrivacy_lvl(2);
//  else c[i].setPrivacy_lvl(3);
//  //if(i%2==0) c[i].setNode_Type("sensor");
//  //else c[i].setNode_Type("actuator");
//  c[i].setNode_Type("sensor");
//  if(i%2==0) c[i].setData_Type("power");
//  else c[i].setData_Type("temp");
//  c[i].setinterval((i+1)*60);
//  c[i].setlocation("http://10.24.129.39");
//  db.deleteValue("node",c[i].getNode_ID());
//  db.insertValue(c[i]);
//  }
//  std::vector<Consumer> res;
//  db.selectValue("privacy_lvl >= 2",res);
//
//  for(std::vector<Consumer>::iterator it=res.begin();it!=res.end();it++){
//    std::cout<<it->getNode_ID()<<it->getUser_ID()<<it->getPrivacy_lvl()<<it->getNode_Type()<<it->getData_Type()<<it->getinterval()<<std::endl;
//  }

//  for(int i=0;i<100;i++){
//    Vender v;
//    if(i<30){
//      v.setVender_ID("v00001");
//      v.setService_ID("http://service1/dummy"+std::to_string(i));
//      v.setinterval((i+1)*30);
//    }
//    else if(i<60){
//      v.setVender_ID("v00002");
//      v.setService_ID("http://service2/dummy"+std::to_string(i-30));
//      v.setinterval((i-29)*30);
//    }
//    else{
//      v.setVender_ID("v00003");
//      v.setService_ID("http://service3/dummy"+std::to_string(i-60));
//      v.setinterval((i-59)*30);
//    }
//    if(i%3==0) v.setPrivacy_lvl(3);
//    else if(i%3==1) v.setPrivacy_lvl(2);
//    else v.setPrivacy_lvl(1);
//    if(i%4==0) v.setData_Type("temp");
//    else if(i%4==1) v.setData_Type("CO2");
//    else if(i%4==2) v.setData_Type("wind");
//    else v.setData_Type("power");
//    //db.deleteValue("service",v.getService_ID());
//    db.insertValue(v);
//    std::cout<<i<<std::endl;
//  }
//  std::vector<Vender> vres;
//  db.selectValue("privacy_lvl > 1",vres);
//  for(std::vector<Vender>::iterator it=vres.begin();it!=vres.end();it++){
//    std::cout<<it->getService_ID()<<it->getVender_ID()<<it->getPrivacy_lvl()<<it->getData_Type()<<it->getinterval()<<std::endl;
//  }

//  Relation r;
//  r.setNode_ID("http://GW/sensor2");
//  r.setService_ID("http://service/dummy1");
//  r.setAnonymization("noise");
//  r.setPrivacy_lvl(3);
//  r.setinterval(180);
//  db.insertValue(r);
//  std::cout<<"ok\n";
//
//  std::vector<Relation> r_res;
//  db.selectValue("relationid=1",r_res);
//  for(std::vector<Relation>::iterator it=r_res.begin();it!=r_res.end();it++){
//    std::cout<<it->getRelation_ID()<<std::endl;
//    std::cout<<it->getNode_ID()<<std::endl;
//    std::cout<<it->getService_ID()<<std::endl;
//    std::cout<<it->getinterval()<<std::endl;
//
//    //std::vector<Node_ID> nodesres=it->getNodes();
//    //for(std::vector<Node_ID>::iterator nodeit=nodesres.begin();nodeit!=nodesres.end();nodeit++){
//    //  std::cout<<*nodeit<<std::endl;
//    //}
//
//    //std::vector<Service_ID> servicesres=it->getServices();
//    //for(std::vector<Service_ID>::iterator serviceit=servicesres.begin();serviceit!=servicesres.end();serviceit++){
//    //  std::cout<<*serviceit<<std::endl;
//    //}
//
//    std::cout<<it->getAnonymization()<<it->getPrivacy_lvl()<<std::endl;
//  }
//  //db.deleteRelation("'jklsdjl'=ANY(nodeid)");
//  return 0;
//
//  db.insertUser("jhon","testpass");
//  std::string userid;
//  if(db.authUser("jhon","testpass",userid)){
//    std::cout<<userid<<std::endl;
//  }
//  else std::cerr<<"cant";
//  if(db.authUser("jhon","notpass",userid)){
//    std::cout<<userid<<std::endl;
//  }
//  else std::cerr<<"cant";
//  if(db.authUser("allry","testpass",userid)){
//    std::cout<<userid<<std::endl;
//  }
//  else std::cerr<<"cant";
//
//
//  return 0;
//}


