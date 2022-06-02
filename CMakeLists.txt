cmake_minimum_required(VERSION 3.16)
project(OS_Design_Pattern)

set(CMAKE_CXX_STANDARD 14)

add_executable(OS_Design_Pattern main1.c guard.cpp client.c singleton.cpp reactor.hpp reactor.cpp pollserver.cpp pollclient.c)
