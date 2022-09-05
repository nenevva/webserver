cmake_minimum_required(VERSION 3.23)
project(webserver)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. SRC_LIST) # 搜索当前目录下的所有.cpp文件

add_executable(webserver ${SRC_LIST})