cmake_minimum_required(VERSION 3.16)

project(tt VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()


add_executable( dateTest task1/Date.cpp task1/test/DateTest.cpp )
target_link_libraries(dateTest Qt6::Core gtest gtest_main)
add_test( dateTest dateTest )


qt_add_executable(task1
  task1/main.cpp task1/mainwindow.cpp task1/mainwindow.h task1/mainwindow.ui
  task1/Date.cpp
)

target_link_libraries(task1 PRIVATE Qt6::Widgets)

set_target_properties(task1 PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

qt_add_executable(task2
  task2/main.cpp task2/mainwindow.cpp  task2/mainwindow.ui
  task2/Car.cpp task2/Database.cpp task2/CarDialog.cpp
  task2/RangeFilter.cpp task2/SelectFilter.cpp
)

target_link_libraries(task2 PRIVATE Qt6::Widgets)

set_target_properties(task2 PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)


add_executable( task3_4 task3_4/test.cpp task3_4/BinaryOperation.cpp task3_4/Number.cpp task3_4/Expression.cpp)
target_link_libraries(task3_4 gtest gtest_main)
add_test( task3_4 task3_4 )
