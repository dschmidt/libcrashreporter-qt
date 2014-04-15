# message(FATAL_ERROR "${CMAKE_CURRENT_LIST_DIR}/../../3rdparty/breakpad")

list(APPEND crashreporter-launcher_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/../../3rdparty/breakpad
    ${QT_QTCORE_INCLUDE_DIR}
)

list(APPEND crashreporter-launcher_SOURCES
    Launcher.cpp
)

list(APPEND crashreporter-launcher_LIBRARIES
    crashreporter-breakpad
)

include_directories(${crashreporter-launcher_INCLUDE_DIRECTORIES})
add_library(crashreporter-launcher STATIC ${crashreporter-launcher_SOURCES})
target_link_libraries(crashreporter-launcher ${crashreporter-launcher_LIBRARIES})

if(WIN32)
    add_definitions( -DUNICODE ) #-fshort-wchar )
endif()