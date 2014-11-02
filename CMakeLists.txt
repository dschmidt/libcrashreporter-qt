cmake_minimum_required(VERSION 2.6)
project(libcrashreporter-qt)

if(CMAKE_COMPILER_IS_GNUCXX)
    # Breakpad uses GNU compiler extensions like typeof.
    # Luckily these features are not used on OSX, so we can build the
    # crashreporter there with the normal C++11 standard.
    string(REPLACE "-std=c++11" "-std=gnu++11" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()

add_subdirectory(3rdparty)
add_subdirectory(src)

