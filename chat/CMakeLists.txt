add_library(
        libchat STATIC
        ContactsService.hpp
        MessageService.hpp
        ServerConnection.hpp
)

target_link_libraries(libchat)

target_include_directories(libchat PUBLIC ../network)
