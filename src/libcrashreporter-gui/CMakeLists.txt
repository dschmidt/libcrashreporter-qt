set(crashreporter_SOURCES CrashReporter.cpp CrashReporterGzip.cpp)
set(crashreporter_UI CrashReporter.ui)
set(crashreporter_RC ../../resources.qrc)
set(crashreporter_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR} ${QT_INCLUDES})

if(ENABLE_GPL_CODE)
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

add_library(crashreporter-gui STATIC
    ${crashreporter_SOURCES}
    ${crashreporter_HEADERS_MOC}
    ${crashreporter_UI_HEADERS}
    ${crashreporter_RC_RCC}
)
target_include_directories(crashreporter-gui PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/CrashReporterQt>
)

add_library(CrashReporterQt::Gui ALIAS crashreporter-gui)
set_property(TARGET crashreporter-gui PROPERTY EXPORT_NAME Gui)

target_link_libraries(crashreporter-gui
    PUBLIC
        Qt5::Core
        Qt5::Widgets
        Qt5::Network
    PRIVATE
        PkgConfig::BREAKPAD
)

if(WIN32)
    target_compile_definitions(crashreporter-gui PRIVATE UNICODE _UNICODE)
endif()

set_target_properties(crashreporter-gui PROPERTIES AUTOUIC ON)
set_target_properties(crashreporter-gui PROPERTIES AUTOMOC ON)

install(FILES CrashReporter.h DESTINATION ${INCLUDE_INSTALL_DIR}/CrashReporterQt/libcrashreporter-gui)
install(TARGETS crashreporter-gui EXPORT CrashReporterQtTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
