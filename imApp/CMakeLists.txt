#
# Copyrigth: Alexander Kozhinov
# E-Mail: AlexanderKozhinov@yandex.com
#

cmake_minimum_required(VERSION 3.5)

set(BUILD_TOOLS_ROOT "")

if (APPLE)
    set(MACOSX TRUE)
    set(BUILD_TOOLS_ROOT "/usr/local/bin")
    message(STATUS "run build in macOS")
elseif(UNIX)
    set(UNIX TRUE)
    message(STATUS "run build in unix")
elseif(WIN32)
    set(WINDOWS_x32 TRUE)
    message(STATUS "run build in windows x32")
elseif("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
    set(WINDOWS_x64 TRUE)
    message(STATUS "run build in windows x64")
endif()

set(CMAKE_MAKE_PROGRAM "${BUILD_TOOLS_ROOT}/ninja" CACHE INTERNAL "Set variable in internal cache")
message(STATUS "CMAKE_MAKE_PROGRAM: ${CMAKE_MAKE_PROGRAM}")

project(imApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES imApp_en_DE.ts)

if(ANDROID)
  add_library(imApp SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${TS_FILES}
  )
else()
  add_executable(imApp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${TS_FILES}
  )
endif()

target_link_libraries(imApp PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
