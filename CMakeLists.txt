cmake_minimum_required(VERSION 3.19)
project(cloudflareScanner LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

qt_standard_project_setup()

qt_add_executable(cloudflareScanner
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    cloudflare.cpp
    cloudflare.h
    ping.cpp
    ping.h
    mainwindow.ui
)
set_property(TARGET cloudflareScanner PROPERTY CXX_STANDARD 23)
set_property(TARGET cloudflareScanner PROPERTY CXX_STANDARD_REQUIRED On)
target_link_libraries(cloudflareScanner
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
)

include(GNUInstallDirs)

find_package(Boost 1.88.0 REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

install(TARGETS cloudflareScanner
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET cloudflareScanner
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
