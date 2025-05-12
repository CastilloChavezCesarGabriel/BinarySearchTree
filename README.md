# Binary Search Tree in C++

This GUI program manages dynamic binary search trees (BST) structure, allowing users to create
and delete nodes while maintaining BST and AVL properties, using the Qt framework and 
following the MVC (Model-View-Controller) architecture pattern to ensure code reusability.

## MVC structure:
- **Model**:
  - Implements the binary tree structure.
  - Manages node insertion, deletion, balancing, and traversal. 
  - Maintains root and ensures integrity of the tree.
- **View**:
  - Contains all GUI elements: input fields, buttons, and tree graphics. 
  - Emits user interaction signals.
  - Renders the binary tree via QGraphicsScene. 
  - Manages user feedback and export operations.
- **Controller**:
  - Connects signals from the View to handle actions in the Model. 
  - Translates user requests into data operations. 
  - Ensures the View is updated after each operation.

## Qt Libraries Used:
- **QWidget**: Provides all the UI elements for building user interfaces.
- **QPushButton**: Creates interactive buttons that emit signals when clicked.
- **QFormLayout**: Lays out widgets in a form.
- **QLineEdit**: Allows users to enter text.
- **QLabel**: Displays text or images within the window.
- **QObject**: Provides core features like memory management, event handling and signals/slots.
- **QStringList**: Stores and manipulates lists of QStrings.
- **QFileDialog**: Opens, saves, and selects files using dialog boxes.
- **QMessageBox**: Displays messages to the user.
- **QComboBox**: Displays a list of items and allows users to select one.
- **QGraphicsView**: Displays a scene.
- **QGraphicsScene**: Displays graphical elements like shapes and text on a scene.
- **QGraphicsEllipseItem**: Represents an ellipse.

## Qt Dependencies:
- Qt Core
- Qt Gui
- Qt Widgets

## Features:
- **Add Root/Node**: Builds tree structure from scratch.
- **Delete Root/Node**: Removes specific nodes based on parent and side.
- **Balance Tree**: Automatically balances a part or whole of the tree.
- **Export Tree**: Saves the rendered binary tree as an image (PNG/JPEG).
- **Real-Time Visualization**: Dynamically displays and updates the binary tree as changes done.
- **Feedback**: Displays informative and consistent GUI messages.
- **Validation**: Ensures numeric input and logical operations.

## Setting up Qt6 on Mac & Windows
Before setting up Qt6, make sure you have the following apps and tools installed:

1. **CLion** (Latest version): [JetBrains CLion](https://www.jetbrains.com/clion/download/)
2. **CMake** (Usually bundled with CLion, but you can install it separately if needed): [CMake](https://cmake.org/download/)

## Steps
When installing Qt 6 using the Qt Installer, follow these steps:

1. Download the **Qt Installer** from the Qt website: [Qt 6 Download](https://www.qt.io/download-dev). Create an account before proceeding.
2. Run the installer and log in your Qt account.
3. When installing, select **Qt for developers** or any option you prefer.
4. Follow the rest of the installation prompts to finish the setup.
5. Open **CLion** and open or create a new project as **Qt Widget Executable.**
6. Configure **`CMakeLists.txt`** to support Qt6. It's usually bundled with CLion, but make sure it looks like this:
  ```cmake
  cmake_minimum_required(VERSION "Version set")
  # Set the project name
  project("Project name")
  
  # Set the required C++ standard
  set(CMAKE_CXX_STANDARD 17 "or after")
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTORCC ON)
  set(CMAKE_AUTOUIC ON) 

  # Set CMake search path for Qt6 packages (adjust Qt version and compiler as needed)
  # MinGW on Windows
  set(CMAKE_PREFIX_PATH "C:/Qt/6.*/mingw*/lib/cmake/Qt6")
  # MSVC on Windows
  set(CMAKE_PREFIX_PATH "C:/Qt/6.*/msvc*/lib/cmake/Qt6")
  # MacOs 
  set(CMAKE_PREFIX_PATH "-DCMAKE_PREFIX_PATH=/Users/username/Qt/6.*/macos")

  # Find the Qt6 packages you need
  find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

  # Add executable
  add_executable(${PROJECT_NAME} main.cpp ... "Here's where the implemented classes go!")

  # Link Qt6 libraries
  target_link_libraries(${PROJECT_NAME} Qt::Core Qt::Gui Qt::Widgets)
  ```
7. Then go to **CMake configuration** and add this package path on CMake Options:
- **macOS**: "-DCMAKE_PREFIX_PATH=/Users/username/Qt/6.*/macos"
- **Windows**: "-DCMAKE_PREFIX_PATH=C:/Qt/6.*/msvc or mingw version/lib/cmake"
8. Apply the changes on **CMake configuration** and click on the **Ok** button.
9. Go to **project configuration** and add this environment variable: 
- **macOS**: "-DCMAKE_PREFIX_PATH=/Users/username/Qt/6.*/macos/plugins/platforms"
- **Windows**: "-DCMAKE_PREFIX_PATH=C:/Qt/6.*/msvc or mingw version/plugins/platforms"
10. Apply the changes and click on the **Ok** button.
11. If you would like to learn more about setting up Qt6 in CLion, check out this [tutorial](https://www.youtube.com/watch?v=VYnU-DoIlzY).

# License
MIT License.

# Acknowledgements
This project was created as an educational example for demonstrating the Model-View-Controller (MVC) design pattern in C++ with Qt.
