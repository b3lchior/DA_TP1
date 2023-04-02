cmake_minimum_required(VERSION 3.23)
project(DA_TP1)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_TP1 source/main.cpp source/Graph.cpp headers/Graph.h source/VertexEdge.cpp headers/VertexEdge.h headers/MutablePriorityQueue.h source/Manager.cpp headers/Manager.h source/GraphAlgorithms.cpp headers/GraphAlgorithms.h)
