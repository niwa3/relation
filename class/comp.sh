#!/bin/sh
g++ -W -DWITH_OPENSSL ./UnixDomainSocketServer.cpp ./MakeRelation.cpp ./database.cpp ./type.cpp ./sha256.cpp ./xmlcreate.cpp ./xmlparse.cpp ../client/mySoapClient.cpp ../client/soapC.cpp ../client/soapRManagerProxy.cpp -lpqxx -std=c++11 -pthread -lcryptopp -ltinyxml2 -lgsoapssl++ -lcrypto -lgsoapssl
#g++ -W ./UnixDomainSocketServer.cpp ./MakeRelation.cpp ./database.cpp ./type.cpp ./sha256.cpp ./xmlcreate.cpp ./xmlparse.cpp  -lpqxx -std=c++11 -pthread -lcryptopp -ltinyxml2
