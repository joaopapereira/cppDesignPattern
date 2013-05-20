
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET( lib_srcs libJPReactor.cpp )
include_directories( modules/include/ )
ADD_LIBRARY( JPReactorStatic STATIC ${lib_srcs})
ADD_LIBRARY( JPReactor SHARED ${lib_srcs})

