cmake_minimum_required(VERSION 3.16)

project(Gerdt_oopp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_ROOT "C:/Qt/boost/boost_1_86_0")
#include_directories(C:/Qt/boost/boost_1_86_0)
#set(BOOST_LIBRARYDIR "C:/Qt/boost/boost_1_86_0/stage/lib")
set(Boost_USE_STATIC_LIBS ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
#find_package(Boost 1.86 REQUIRED COMPONENTS serialization)
find_package(Boost 1.86)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Gerdt_oopp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        MyWidgetGerdt.h MyWidgetGerdt.cpp
        pch.h
        Animatedfilm.h Animatedfilm.cpp
        films.h films.cpp


    )
else()
    if(ANDROID)
        add_library(Gerdt_oopp SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Gerdt_oopp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Линковка с Qt и Boost
target_link_libraries(Gerdt_oopp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${Boost_LIBRARIES})

# Указать пути к include для Boost
target_include_directories(Gerdt_oopp PRIVATE ${Boost_INCLUDE_DIRS})

set_target_properties(Gerdt_oopp PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Gerdt_oopp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Gerdt_oopp)
endif()
