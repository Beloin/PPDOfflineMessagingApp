add_library(
        libchat STATIC
        MessageService.hpp
        ServerConnection.hpp

        MessageService.cpp
        ServerConnection.cpp
)

target_link_libraries(libchat)

target_include_directories(libchat PUBLIC ../network)
