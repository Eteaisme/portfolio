cmake_minimum_required(VERSION 3.16)
project(portfolio)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui.git
  GIT_TAG v5.0.0
)

FetchContent_MakeAvailable(ftxui)

add_executable(portfolio
    src/main.cpp
)

target_link_libraries(portfolio
    PRIVATE
        ftxui::screen
        ftxui::dom
        ftxui::component
)
