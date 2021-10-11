add_library(crashreporter-handler STATIC Handler.cpp)
target_include_directories(crashreporter-handler PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)

target_link_libraries(crashreporter-handler PUBLIC
    PkgConfig::BREAKPAD
    Qt5::Core)

if(WIN32)
    target_compile_definitions(crashreporter-handler PRIVATE UNICODE _UNICODE)
endif()
