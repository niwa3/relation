#!/bin/sh
g++ -ggdb main.cpp ./class/database.cpp ./class/MakeRelation.cpp ./class/type.cpp ./class/UnixDomainSocketServer.cpp -lpqxx -lpq -pthread -std=c++11
