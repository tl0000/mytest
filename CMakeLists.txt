CMAKE_MINIMUM_REQUIRED(VERSION 2.8)# 指定工程名称

PROJECT(facedemo)

set(CMAKE_CXX_FLAGS "-std=c++11") 


if( ANDROID AND ("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "armv7-a"))
    set( PROTOBUF_LIB ${PROTOBUF_DIR}/arm32_lib/libprotobuf.so)
endif()
if( ANDROID AND ("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "aarch64"))
    set( PROTOBUF_LIB ${PROTOBUF_DIR}/arm64_lib/libprotobuf.so)
endif()

if( BLAS_DIR)
    if( ANDROID AND ("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "armv7-a"))
         set( BLAS_LIB ${BLAS_DIR}/arm32/lib/libopenblas.so)
    endif()
    if( ANDROID AND ("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "aarch64"))
         set( BLAS_LIB ${BLAS_DIR}/arm64/lib/libopenblas.so)
    endif()
endif()

# 导入OpenCV库
#opencv
set(OpenCV_DIR /home/watrix/opencv-2.4.13/release)
set(OpenCV_FOUND 1)
find_package(OpenCV REQUIRED)

# 设置源文件
SET(SRC_DIR_PATH src )
SET(LIBS_DIR lib)
#FILE(GLOB_RECURSE SOURCE_FILES "src/*.cpp") 
#AUX_SOURCE_DIRECTORY(./src DIR_SRCS)
AUX_SOURCE_DIRECTORY(./src/driver DIR_SRCS)
AUX_SOURCE_DIRECTORY(./src/common DIR_SRCS)
# 设置头文件搜索目录

#SET( CAFFE_ROOT /home/kevin/SSD/caffe)
#SET( CUDA_HOME /usr/local/cuda-8.0 )

set(CAFFE_LIB   ${PROJECT_SOURCE_DIR}/lib/libcaffe.so)
set(TENGINE_LIB   ${PROJECT_SOURCE_DIR}/lib/libtengine.so)
#set(CAFFE_LIB  /usr/local/AID/Caffe-HRT/lib/libcaffe.so)
set(X86_LIB  /usr/lib/x86_64-linux-gnu/libglog.so.0)
set(BOOST_LIB  /usr/lib/x86_64-linux-gnu/libboost_system.so.1.58.0)


#INCLUDE_DIRECTORIES(${CAFFE_ROOT}/include/ ./include/ ${CAFFE_ROOT}/.build_release/src/ ${CUDA_HOME}/include/ ) 
# 设置动态库链接目录

INCLUDE_DIRECTORIES(include include/tengine) 

# 设置动态库链接目录
#LINK_DIRECTORIES( ${CAFFE_ROOT}/build/lib/ ${CUDA_HOME}/lib64/) 
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/)

# 设置要链接的库文件
#SET( LIB_PROJECT caffe glog boost_system protobuf boost_thread gflags) 

# 指定执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 生成可执行文件，即程序
#ADD_EXECUTABLE( facedemo ${PUBLIC_SRC_FILE} ${SRC_DIR_PATH}/faceID.cpp  ) 
ADD_EXECUTABLE( facedemo ${DIR_SRCS} ${SRC_DIR_PATH}/faceID.cpp)

# 要链接的动态库, 参数指明库的名字即可，比如libxxxx1.so, 指明是xxxx1即可！！！
#TARGET_LINK_LIBRARIES( facedemo ${LIB_PROJECT} ${OpenCV_LIBS} )
TARGET_LINK_LIBRARIES( facedemo  ${LIB_PROJECT}  ${OpenCV_LIBS}  ${X86_LIB} ${BOOST_LIB} ${CAFFE_LIB}  ${TENGINE_LIB})


