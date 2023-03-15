cmake_minimum_required(VERSION 3.23)
project(DA_TP1)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_TP1 main.cpp Graph.cpp Graph.h VertexEdge.cpp VertexEdge.h MutablePriorityQueue.h Manager.cpp Manager.h)
