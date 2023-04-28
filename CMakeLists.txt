project(libcrashreporter-qt)
cmake_minimum_required(VERSION 3.16)

include(FeatureSummary)

find_package(ECM 5.50.0 REQUIRED NO_MODULE)

set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://projects.kde.org/projects/kdesupport/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH})

if(POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()

if(POLICY CMP0063)
    cmake_policy(SET CMP0063 NEW)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT 5.15 NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network Widgets REQUIRED)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

# Only on linux breakpad provides a usable build system.
# The submodule on the other hand can't be used on linux, 
# as parts of it requires to be checked out by a seperate tool.
if (UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(BREAKPAD REQUIRED IMPORTED_TARGET breakpad breakpad-client)
else()
    add_subdirectory(3rdparty/breakpad)
endif()


option(ENABLE_GPL_CODE "Enable GPL-licensed depencencies of libcrashreporter-qt (dr.konqui integration)" OFF)
if(ENABLE_GPL_CODE AND NOT APPLE AND NOT WIN32)
    add_definitions( -DENABLE_GPL_CODE )
endif()

option(ENABLE_CRASH_REPORTER "Enable libcrashreporter-qt GUI component" ON)

add_definitions(
    -DQT_NO_FOREACH
)


if(ENABLE_CRASH_REPORTER)
    add_definitions(-DENABLE_CRASH_REPORTER)
endif(ENABLE_CRASH_REPORTER)

add_subdirectory(3rdparty)
add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
