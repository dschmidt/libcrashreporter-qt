add_library(crashreporter-handler STATIC Handler.cpp)
add_library(CrashReporterQt::Handler ALIAS crashreporter-handler)
set_property(TARGET crashreporter-handler PROPERTY EXPORT_NAME Handler)

target_link_libraries(crashreporter-handler
    PUBLIC
        Qt5::Core
    PRIVATE
        PkgConfig::BREAKPAD
    )

if(WIN32)
    target_compile_definitions(crashreporter-handler PRIVATE UNICODE _UNICODE)
endif()

target_include_directories(crashreporter-handler PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/CrashReporterQt>
)

install(FILES Handler.h DESTINATION ${INCLUDE_INSTALL_DIR}/CrashReporterQt/libcrashreporter-handler)
install(TARGETS crashreporter-handler EXPORT CrashReporterQtTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
