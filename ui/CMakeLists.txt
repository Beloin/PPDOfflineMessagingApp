add_library(
        ui STATIC
        QTChat.cpp
        QTChat.hpp
        QTContacts.hpp
        QTContacts.cpp
)

target_link_libraries(ui
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

target_include_directories(ui PUBLIC ../utils ../chat)
