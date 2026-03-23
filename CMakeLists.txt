cmake_minimum_required(VERSION 3.19)
project(pingapka LANGUAGES CXX)


find_package(Qt6 REQUIRED COMPONENTS Widgets Network Charts Test)

qt_standard_project_setup()

qt_add_executable(pingapka
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(pingapka
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
        Qt6::Charts
)

enable_testing()


qt_add_executable(test_pingapka
    test_pingapka.cpp
)


target_link_libraries(test_pingapka
    PRIVATE
        Qt6::Test
        Qt6::Core
)


add_test(NAME PingapkaTest COMMAND test_pingapka)