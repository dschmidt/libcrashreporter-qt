# message(FATAL_ERROR "${CMAKE_CURRENT_LIST_DIR}/../../3rdparty/breakpad")

list(APPEND crashreporter-handler_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/../../3rdparty/breakpad
    ${QT_QTCORE_INCLUDE_DIR}
)

list(APPEND crashreporter-handler_SOURCES
    Handler.cpp
)

list(APPEND crashreporter-handler_LIBRARIES
    crashreporter-breakpad
)

if(UNIX AND NOT APPLE)
set(CMAKE_AUTOMOC 1)
list(APPEND crashreporter-handler_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/../../3rdparty/drkonqi-parser
)
list(APPEND crashreporter-handler_LIBRARIES
    drkonqi_backtrace_parser
)
list(APPEND crashreporter-handler_SOURCES
    linux-backtrace-generator/crashedapplication.cpp
    linux-backtrace-generator/backtracegenerator.cpp
    linux-backtrace-generator/debugger.cpp
    linux-backtrace-generator/crqt-kmacroexpander.cpp
    linux-backtrace-generator/crqt-kmacroexpander_unix.cpp
    linux-backtrace-generator/crqt-kshell.cpp
    linux-backtrace-generator/crqt-kshell_unix.cpp
)
endif()

include_directories(${crashreporter-handler_INCLUDE_DIRECTORIES})
add_library(crashreporter-handler STATIC ${crashreporter-handler_SOURCES})
target_link_libraries(crashreporter-handler ${crashreporter-handler_LIBRARIES})
qt5_use_modules(crashreporter-handler Core)

if(WIN32)
    add_definitions( -DUNICODE ) #-fshort-wchar )
endif()
