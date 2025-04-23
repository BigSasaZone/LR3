cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 0.1 LANGUAGES CXX)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
set(PROJECT_SOURCES
    main.cpp
    MainWindow.cpp
    Polynomial.h
    PriorityQueue.h
    Stack.h
    RedBlackTree.h
    SegmentDeque.h
    dynamic_array.h
)
add_executable(MyProject
    ${PROJECT_SOURCES}
)
target_link_libraries(MyProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
