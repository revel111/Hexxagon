cmake_minimum_required(VERSION 3.22)
project(Hexxagon)
set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)
add_executable(Hexxagon main.cpp button.h button.cpp game.h game.cpp gamestate.h)
target_compile_definitions(Hexxagon PRIVATE SFML_BUILD_STATIC)
target_link_libraries(Hexxagon sfml-graphics sfml-audio sfml-network sfml-window sfml-system)