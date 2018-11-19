cmake_minimum_required(VERSION 3.12)
project(Spl1)

set(CMAKE_CXX_STANDARD 11)

add_executable(Spl1 src/Main.cpp src/Action.cpp include/Action.h src/Customer.cpp include/Customer.h src/Dish.cpp include/Dish.h src/Main.cpp src/Restaurant.cpp include/Restaurant.h src/Table.cpp include/Table.h)