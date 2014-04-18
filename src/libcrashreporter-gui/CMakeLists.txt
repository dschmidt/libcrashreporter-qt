set(crashreporter_SOURCES CrashReporter.cpp)
set(crashreporter_UI CrashReporter.ui)
set(crashreporter_RC ../../resources.qrc)

qt_wrap_ui( crashreporter_UI_HEADERS ${crashreporter_UI} )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} ${QT_INCLUDES} )

add_library(crashreporter-gui STATIC
    ${crashreporter_SOURCES}
    ${crashreporter_HEADERS_MOC}
    ${crashreporter_UI_HEADERS}
    ${crashreporter_RC_RCC}
)


target_link_libraries(crashreporter-gui
    ${QT_QTGUI_LIBRARY}
    ${QT_QTNETWORK_LIBRARY}
)

set_target_properties(crashreporter-gui PROPERTIES AUTOMOC ON)
#install(TARGETS crashreporter-gui
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#)

qt5_use_modules(crashreporter-gui Widgets Network)
