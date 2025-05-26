cmake_minimum_required(VERSION 3.5)
project(DHondtAllocator)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

qt_wrap_ui(UIS_HDRS mainwindow.ui)

add_executable(DHondtAllocator
        main.cpp
        mainwindow.cpp
        mainwindow.h
        party.cpp
        party.h
        d_hondt_allocator.cpp
        d_hondt_allocator.h
)

target_link_libraries(DHondtAllocator
        Qt6::Widgets
        Qt6::Charts
)
