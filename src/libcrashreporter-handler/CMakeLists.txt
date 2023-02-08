# message(FATAL_ERROR "${CMAKE_CURRENT_LIST_DIR}/../../3rdparty/breakpad")

list(APPEND crashreporter-handler_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_LIST_DIR}/..
    ${QT_QTCORE_INCLUDE_DIR}
)

list(APPEND crashreporter-handler_SOURCES
    Handler.cpp
)

list(APPEND crashreporter-handler_LIBRARIES
    crashreporter-breakpad
)

add_library(crashreporter-handler STATIC ${crashreporter-handler_SOURCES})
target_include_directories(crashreporter-handler PUBLIC ${crashreporter-handler_INCLUDE_DIRECTORIES})
target_link_libraries(crashreporter-handler
    PUBLIC
        Qt5::Core
    PRIVATE
        ${crashreporter-handler_LIBRARIES}
    )

if(WIN32)
    add_definitions( -DUNICODE ) #-fshort-wchar )
endif()
