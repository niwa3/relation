#!/bin/sh
g++ -ggdb ./UnixDomainSocketServer.cpp ./MakeRelation.cpp ./database.cpp ./type.cpp ./sha256.cpp ./xmlcreate.cpp ./xmlparse.cpp -lpqxx -std=c++11 -pthread -lcryptopp -ltinyxml2
