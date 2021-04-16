cmake_minimum_required(VERSION 3.7.0)

project(analogclock VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(smartbirdcafe
  window.cpp
  main.cpp
  photoview.cpp
)

target_link_libraries(smartbirdcafe Qt5::Widgets)
target_link_libraries(smartbirdcafe qwt-qt5)

install(
    TARGETS smartbirdcafe
    RUNTIME DESTINATION bin
)
