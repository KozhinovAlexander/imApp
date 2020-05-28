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

set(COMPILER_VER "-9")
set(CMAKE_C_COMPILER "${BUILD_TOOLS_ROOT}/gcc${COMPILER_VER}" CACHE INTERNAL "Set gcc compiler in internal cache")
set(CMAKE_CXX_COMPILER "${BUILD_TOOLS_ROOT}/g++${COMPILER_VER}" CACHE INTERNAL "Set g++ compiler in internal cache")

set(CMAKE_MAKE_PROGRAM "${BUILD_TOOLS_ROOT}/ninja" CACHE INTERNAL "Set variable in internal cache")
message(STATUS "CMAKE_MAKE_PROGRAM: ${CMAKE_MAKE_PROGRAM}")

project(imApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
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

find_package(Qt5 COMPONENTS
                Widgets
                LinguistTools
                Core
             REQUIRED)

set(TS_FILES imApp_en_DE.ts)

set(APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/app")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

set(APP_INC_DIR "${APP_DIR}/include")
set(APP_SRC_DIR "${APP_DIR}/src")

set(LIB_INC_DIR "${LIB_DIR}/include")
set(LIB_SRC_DIR "${LIB_DIR}/src")

include_directories(${APP_INC_DIR} ${LIB_INC_DIR})

# Project specific directories:
add_subdirectory(${APP_DIR})
add_subdirectory(${LIB_DIR})

set(PRJ_HDS "${APP_INC_DIR}/WorkerThread.h")
set(PRJ_SRC "${APP_SRC_DIR}/WorkerThread.cpp")

if(ANDROID)
  add_library(imApp SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${TS_FILES}
    ${PRJ_HDS}
    ${PRJ_SRC}
  )
else()
  add_executable(imApp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${TS_FILES}
    ${PRJ_HDS}
    ${PRJ_SRC}
  )
endif()

target_link_libraries(imApp PRIVATE Qt::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

