# Binary Search Tree in C++

This GUI program manages dynamic binary search trees (BST) structure, allowing users to create
and delete nodes while maintaining BST and AVL properties, while using the Qt framework and 
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

## Setting up Qt6 on Windows
Before setting up Qt6, make sure you have the following apps and tools installed:

1. **Visual Studio** (2022 or Latest version): [Visual Studio](https://visualstudio.microsoft.com/)

3. **MinGW or MSVC Compiler**: [MinGW](https://sourceforge.net/projects/mingw-w64/). MSVC is usually installed along with Visual Studio.

### Steps
When installing Qt 6 using the Qt Installer, follow these steps:

1. **Install Qt6**:
- Download the **Qt Installer** from the Qt website: [Qt 6 Download](https://www.qt.io/download-dev). Create an account before proceeding.
- Run the installer and log in your Qt account.
- During installation, select **Qt for developers** or any MSVC/MinGW compatible version.
- Follow the rest of the installation prompts to finish the setup.

2. **Install the Qt Visual Studio Tools Extension**:
- Open **Visual Studio** and go to **Extensions → Manage Extensions → Online**.
- Search for **Qt Visual Studio Tools** and install it.
- Restart Visual Studio before proceeding.

3. **Set Up the Qt Version**:
- Once the extension is installed, go to **Extensions → Qt VS Tools → Qt Versions**.
- Click **Add**, then browse to the path where Qt was installed:
  - **MinGW**: C:/Qt/6.* /mingw* /lib/cmake/Qt6
  - **MSVC**: "C:/Qt/6.* /msvc* /lib/cmake/Qt6"
- Click **OK** to register it.

4. **Create a Qt project**
- Open **Visual Studio** and open or create a new project as **Qt Widgets Application or Qt Quick Application.**
- Choose the Qt version and kit (e.g., MSVC 64-bit).
- Click **Create** and set up your project.

5. Configure **CMakeLists.txt (Optional)** to support Qt6:
  - If you're using **CMake** manually (for advanced users), add the following lines:
  ```cmake
  cmake_minimum_required(VERSION "Version set")
  # Set the project name
  project("Project name")
  
  # Set the required C++ standard
  set(CMAKE_CXX_STANDARD 17 "or after")
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTORCC ON)
  set(CMAKE_AUTOUIC ON)
  
  # Set Qt6 CMake package path (adjust the Qt version if necessary)
  # MinGW path
  set(CMAKE_PREFIX_PATH "C:/Qt/6.*/mingw*/lib/cmake/Qt6")
  # MSVC path
  set(CMAKE_PREFIX_PATH "C:/Qt/6.*/msvc*/lib/cmake/Qt6")

  # Find the Qt6 packages you need
  find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

  # Add executable
  add_executable(${PROJECT_NAME} main.cpp ... "Here's where the implemented classes go!")

  # Link Qt6 libraries
  target_link_libraries(${PROJECT_NAME} Qt::Core Qt::Gui Qt::Widgets)
  ```
6. Then configure your CMake profile in **CMakeSettings.json** or via the CMake GUI in Visual Studio.

## Setting up Qt6 on Mac
Before setting up Qt6, make sure you have the following apps and tools installed:

1. **CLion** (Latest version): [JetBrains CLion](https://www.jetbrains.com/clion/download/)

2. **CMake** (Usually bundled with CLion, but you can install it separately if needed): [CMake](https://cmake.org/download/)

## Steps
When installing Qt 6 using the Qt Installer, follow these steps:

1. Download the **Qt Installer** from the Qt website: [Qt 6 Download](https://www.qt.io/download-dev). Create an account before proceeding.
2. Run the installer and log in your Qt account.
3. When installing, select **Qt for developers**.
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

  # Find the Qt6 packages you need
  find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

  # Add executable
  add_executable(${PROJECT_NAME} main.cpp ... "Here's where the implemented classes go!")

  # Link Qt6 libraries
  target_link_libraries(${PROJECT_NAME} Qt::Core Qt::Gui Qt::Widgets)
  ```
7. Then go to **CMake configuration** and add this package path on CMake Options: "-DCMAKE_PREFIX_PATH=/Users/username/Qt/6.*/macos" (Replace **username** with your actual macOS username.)
8. Apply the changes on **CMake configuration** and click on the **Ok** button.
9. Go to **project configuration** and add this environment variable: "-DCMAKE_PREFIX_PATH=/Users/username/Qt/6.*/macos/plugins/platforms" (You can also find the platform file on Qt6 files)
10. Apply the changes and click on the **Ok** button.
11. Now you can use Qt6 in Clion.

## Building and Running in Visual Studio Code

You can also build and run this project using Visual Studio Code (VS Code):

### 1. Open the Project
- Launch VS Code.
- Open your project folder.

### 2. Install Required Extensions
- Install these extensions from the Extensions sidebar:
  - **C/C++** (by Microsoft)
  - **CMake Tools** (by Microsoft)
  - (Optional) **Code Runner** for quick code execution

### 3. Configure the Build System
- Ensure you have CMake and a C++ compiler (g++, clang++, or MSVC) installed.
- Open the Command Palette (`Cmd+Shift+P` on Mac, `Ctrl+Shift+P` on Windows/Linux).
- Type and select: `CMake: Configure` to generate build files.

### 4. Build the Project
- Open the Command Palette again.
- Type and select: `CMake: Build` to compile the code and create the binary (likely named `BinaryTree`).

### 5. Run the Program
- In the built-in terminal, run:
  ```sh
  cmake .
  make
  ./BinaryTree
  ```
  (If the binary is in a subfolder like `build` or `cmake-build-debug`, navigate there first.)

### 6. (Optional) Set Up a Launch Configuration
- For debugging or running with a button:
  1. Go to the Run and Debug sidebar.
  2. Click "create a launch.json file".
  3. Choose "C++ (GDB/LLDB)".
  4. Edit the `program` path to point to your compiled binary (e.g., `"${workspaceFolder}/BinaryTree"`).

### 7. (Optional) Run with Code Runner
- If you installed Code Runner, right-click `main.cpp` and select "Run Code."
- Note: This may not use your CMake build and might not work for multi-file projects.

# License
MIT License.

# Acknowledgements
This project was created as an educational example for demonstrating the Model-View-Controller (MVC) design pattern in C++ with Qt.
