

add_library(crashreporter-handler STATIC Handler.cpp)
target_link_libraries(crashreporter-handler
    PUBLIC
        Qt5::Core
    PRIVATE
        PkgConfig::BREAKPAD
    )

