cmake_minimum_required(VERSION 3.5)

project(3DViewer_v2 VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGL)

include_directories(../3DViewerBack/)
include_directories(../3DViewerControl/)
include_directories("../3DViewerBack/gif/qtgifimage/src/gifimage")
include_directories("../3DViewerBack/gif/qtgifimage/src/3rdParty/giflib")

set(PROJECT_SOURCES
    main.cc
    mainwindow.cc
    mainwindow.ui
    ../3DViewerBack/gif/qtgifimage/src/gifimage/qgifglobal.h
    ../3DViewerBack/gif/qtgifimage/src/gifimage/qgifimage.h
    ../3DViewerBack/gif/qtgifimage/src/gifimage/qgifimage_p.h
    ../3DViewerBack/gif/qtgifimage/src/gifimage/qgifimage.cpp
    ../3DViewerBack/gif/qtgifimage/src/3rdParty/giflib/dgif_lib.c
    ../3DViewerBack/gif/qtgifimage/src/3rdParty/giflib/egif_lib.c
    ../3DViewerBack/gif/qtgifimage/src/3rdParty/giflib/gifalloc.c
    ../3DViewerBack/gif/qtgifimage/src/3rdParty/giflib/gif_err.c
    ../3DViewerBack/gif/qtgifimage/src/3rdParty/giflib/gif_font.c
    ../3DViewerBack/gif/qtgifimage/src/3rdParty/giflib/gif_hash.c
    ../3DViewerBack/gif/qtgifimage/src/3rdParty/giflib/gif_hash.c
    ../3DViewerBack/gif/qtgifimage/src/3rdParty/giflib/quantize.c

    ../3DViewerBack/object3d.cc
    ../3DViewerBack/view_parameters.cc
    ../3DViewerBack/openglwidget.cc
    ../3DViewerBack/openglwidget.h
    ../3DViewerBack/settings.cc
    ../3DViewerBack/strategy.cc
    ../3DViewerBack/template.cc
    ../3DViewerBack/recording.cc
    ../3DViewerControl/controller.cc


    
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer_v2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        #${C_SOURCES}
        #${MATRIX_SOURCES}
    )

# Define target properties for Android with Qt 6 as:
# set_property(TARGET 3DViewer_v2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewer_v2 SHARED
            ${PROJECT_SOURCES}
            ${C_SOURCES}
            ${MATRIX_SOURCES}
        )

    # Define properties for Android with Qt 5 after find_package() calls as:
    # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer_v2
            ${PROJECT_SOURCES}
            ${C_SOURCES}
            ${MATRIX_SOURCES}
        )
    endif()
endif()

target_link_libraries(3DViewer_v2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3DViewer_v2 PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(3DViewer_v2 PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)

set_target_properties(3DViewer_v2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS 3DViewer_v2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer_v2)
endif()
