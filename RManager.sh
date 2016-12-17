#!/bin/sh
g++ -o RManager main.cpp ./class/*.cpp -lpqxx -lpq -pthread -std=c++11
