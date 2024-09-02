add_library(
        libchat STATIC
        ContactsService.hpp
        MessageService.hpp
        ServerConnection.hpp

        # ContactsService.cpp
        MessageService.cpp
        ServerConnection.cpp

)

target_link_libraries(libchat)

target_include_directories(libchat PUBLIC ../network)
