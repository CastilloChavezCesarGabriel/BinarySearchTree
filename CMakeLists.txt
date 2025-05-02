cmake_minimum_required(VERSION 3.30)
project(BinaryTree)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(BinaryTree main.cpp
        model/Node.cpp
        model/Node.h
        model/Model.cpp
        model/Model.h
        view/View.cpp
        view/View.h
        controller/Controller.cpp
        controller/Controller.h
        controller/DrawController.cpp
        controller/DrawController.h
        model/TreeTraversal.cpp
        model/TreeTraversal.h
        model/BinarySearchTree.cpp
        model/BinarySearchTree.h
)
target_link_libraries(BinaryTree
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

