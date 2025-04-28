cmake_minimum_required(VERSION 3.30)
project(BinaryTree)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "DCMAKE_PREFIX_PATH=/Users/developer/Qt/6.8.2/macos")

find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(BinaryTree main.cpp
        model/Node.cpp
        model/Node.h
        model/BinaryTreeModel.cpp
        model/BinaryTreeModel.h
        view/View.cpp
        view/View.h
        controller/Controller.cpp
        controller/Controller.h
)
target_link_libraries(BinaryTree
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

