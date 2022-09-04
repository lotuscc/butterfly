#CMake最低版本号要求
cmake_minimum_required(VERSION 2.8)

#指定项目名称
project(demo)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#指定编译选项
set(CMAKE_BUILD_TYPE Debug)

#并将名称保存到DIR_LIB_SRCS目录
aux_source_directory(. DIR_LIB_SRCS)



#设置编译选项(会将gcc g++全部加上)
add_compile_options(-g -std=c++17)

#指定生成目标
add_executable(demo ${DIR_LIB_SRCS})
