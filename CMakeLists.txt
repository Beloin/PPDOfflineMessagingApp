cmake_minimum_required(VERSION 3.24)
project(message_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# add_subdirectory(ui)
# add_subdirectory(Game)
# add_subdirectory(network)

add_executable(message_app main.cpp ApplicationMain.cpp ApplicationMain.h)
target_link_libraries(message_app
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ui game_lib network_lib
        rpc
)


