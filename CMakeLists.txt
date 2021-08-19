project(libcrashreporter-qt)
cmake_minimum_required(VERSION 3.1)

if(POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()

if(POLICY CMP0063)
    cmake_policy(SET CMP0063 NEW)
endif()

option(ENABLE_GPL_CODE "Enable GPL-licensed depencencies of libcrashreporter-qt (dr.konqui integration)" OFF)
if(ENABLE_GPL_CODE AND NOT APPLE AND NOT WIN32)
    add_definitions( -DENABLE_GPL_CODE )
endif()

option(ENABLE_CRASH_REPORTER "Enable libcrashreporter-qt GUI component" ON)

find_package(Qt5 COMPONENTS Core Network Widgets)
add_definitions(
    -DQT_NO_FOREACH
)

if((CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_FLAGS) OR
   (UNIX AND NOT APPLE AND CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    # Breakpad uses GNU compiler extensions like typeof.
    # Luckily these features are not used on OSX, so we can build the
    # crashreporter there with the normal C++11 standard.
    string(REPLACE "-std=c++11" "-std=gnu++11" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    string(REPLACE "-std=c++14" "-std=gnu++14" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()

if(ENABLE_CRASH_REPORTER)
    add_definitions(-DENABLE_CRASH_REPORTER)
endif(ENABLE_CRASH_REPORTER)

add_subdirectory(3rdparty)
add_subdirectory(src)
