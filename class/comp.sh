#!/bin/sh
g++ -ggdb ./MakeRelation.cpp ./database.cpp ./type.cpp -lpqxx -std=c++11
