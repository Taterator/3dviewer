cmake_minimum_required(VERSION 3.5)

project(model_tests VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 REQUIRED COMPONENTS Core)

include_directories(../3DViewerBack/)

set(PROJECT_SOURCES
    ../3DViewerBack/object3d.cc
    check_calc.cc
    all_tests.cc
    #man_test.cc
)

qt_add_executable(model_tests
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(model_tests PUBLIC gtest gmock pthread)
target_link_libraries(model_tests PRIVATE Qt6::Gui Qt6::Core)

set_target_properties(model_tests PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS model_tests
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_finalize_executable(model_tests)