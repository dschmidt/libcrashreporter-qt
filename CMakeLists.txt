cmake_minimum_required(VERSION 2.6)
project(libcrashreporter-qt)

# Breakpad uses GNU compiler extensions like typeof.
# Luckily these features are not used on OSX, so we can build the
# crashreporter there with the normal C++11 standard.
if( UNIX AND NOT APPLE )
    check_cxx_compiler_flag( "-std=gnu++11" GNUXX11_FOUND )
    check_cxx_compiler_flag( "-std=gnu++0x" GNUXX0X_FOUND )

    # Replace both possible occurences so that we do not depend on the std
    # flag set by the parent project.
    if(GNUXX11_FOUND)
        string(REPLACE "-std=c++11" "-std=gnu++11" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    endif()
    if(GNUXX0X_FOUND)
        string(REPLACE "-std=c++0x" "-std=gnu++0x" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    endif()

    if ( (NOT GNUXX11_FOUND) AND (NOT GNUXX0X_FOUND) )
        message(FATAL_ERROR "${CMAKE_CXX_COMPILER} does not support C++11 with
        GNU extensions, please use a different compiler")
    endif()
endif()

add_subdirectory(3rdparty)
add_subdirectory(src)

