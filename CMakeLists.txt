# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.0)

# 项目信息
project (PerlinNoise)

# 添加编译的信息
set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O3")

# 添加头文件
include_directories(lib)

# 查找目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
# syntax aux_source_directory(<dir> <variable>)
aux_source_directory(src DIR_SRCS)

# add_library(perlinNoise SHARED ${LIB_SRC})

# 添加 src 子目录
add_subdirectory(lib)

# 指定生成目标
add_executable(${PROJECT_NAME}  ${DIR_SRCS})

target_link_libraries(${PROJECT_NAME}  perlinNoise)

