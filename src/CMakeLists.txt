add_subdirectory(libcrashreporter-handler)

if (ENABLE_CRASH_REPORTER)
    add_subdirectory(libcrashreporter-gui)
endif(ENABLE_CRASH_REPORTER)

include(CMakePackageConfigHelpers)

configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/CrashReporterQtConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/CrashReporterQtConfig.cmake"
        INSTALL_DESTINATION ${KDE_INSTALL_CMAKEPACKAGEDIR}/CrashReporterQt
)

install(EXPORT CrashReporterQtTargets DESTINATION "${KDE_INSTALL_CMAKEPACKAGEDIR}/CrashReporterQt"  NAMESPACE CrashReporterQt::)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/CrashReporterQtConfig.cmake" DESTINATION ${KDE_INSTALL_CMAKEPACKAGEDIR}/CrashReporterQt)
