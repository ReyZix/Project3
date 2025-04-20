cmake_minimum_required(VERSION 3.29)
project(Project3)

set(CMAKE_CXX_STANDARD 14)


set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Project3
        main.cpp
        backend.cpp
        frontend.cpp
        textbox.cpp
        button.cpp
)

target_link_libraries(Project3
        sfml-graphics
        sfml-window
        sfml-system
)


#set_target_properties(Project3 PROPERTIES
#        WIN32_EXECUTABLE ON
#)
