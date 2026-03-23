cmake_minimum_required(VERSION 3.19)
project(pingapka LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network Charts)

qt_standard_project_setup()

qt_add_executable(pingapka
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    .gitignore
)
target_link_libraries(pingapka
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
        Qt6::Charts
)

install(TARGETS pingapka
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET pingapka
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts Network)
target_link_libraries(pingapka PRIVATE Qt6::Charts)