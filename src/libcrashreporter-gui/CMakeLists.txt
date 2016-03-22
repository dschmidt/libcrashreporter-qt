set(crashreporter_SOURCES CrashReporter.cpp CrashReporterGzip.cpp)
set(crashreporter_UI CrashReporter.ui)
set(crashreporter_RC ../../resources.qrc)
set(crashreporter_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_BINARY_DIR} ${QT_INCLUDES})


if(UNIX AND NOT APPLE)
list(APPEND crashreporter_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/../../3rdparty/drkonqi-parser
)
list(APPEND crashreporter_LIBRARIES
    drkonqi_backtrace_parser
)
list(APPEND crashreporter_SOURCES
    linux-backtrace-generator/crashedapplication.cpp
    linux-backtrace-generator/backtracegenerator.cpp
    linux-backtrace-generator/debugger.cpp
    linux-backtrace-generator/crqt-kmacroexpander.cpp
    linux-backtrace-generator/crqt-kmacroexpander_unix.cpp
    linux-backtrace-generator/crqt-kshell.cpp
    linux-backtrace-generator/crqt-kshell_unix.cpp
)
endif()

qt_wrap_ui( crashreporter_UI_HEADERS ${crashreporter_UI} )

include_directories( ${crashreporter_INCLUDE_DIRECTORIES} )

add_library(crashreporter-gui STATIC
    ${crashreporter_SOURCES}
    ${crashreporter_HEADERS_MOC}
    ${crashreporter_UI_HEADERS}
    ${crashreporter_RC_RCC}
)


target_link_libraries(crashreporter-gui
    ${QT_QTGUI_LIBRARY}
    ${QT_QTNETWORK_LIBRARY}
    ${crashreporter_LIBRARIES}
)

set_target_properties(crashreporter-gui PROPERTIES AUTOMOC ON)
#install(TARGETS crashreporter-gui
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#)

qt5_use_modules(crashreporter-gui Core Widgets Network)
