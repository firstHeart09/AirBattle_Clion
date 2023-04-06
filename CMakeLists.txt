cmake_minimum_required(VERSION 3.24)
project(AirBattle_Clion)

set(CMAKE_CXX_STANDARD 17)
set(EasyX_DIR D:/MyPackage/CC++/EsayX)
include_directories(${EasyX_DIR}/include)
link_directories(${EasyX_DIR}/lib64)
link_libraries(libEasyX.a libgdi32.a libole32.a)
add_executable(AirBattle_Clion main.cpp DoubleList.cpp DoubleList.h AirPlay.cpp AirPlay.h)
