cmake_minimum_required(VERSION 2.8)

project(restnotifier)

# Plugins for compiler options checking
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)


# Setup Qt
find_package(Qt4 REQUIRED)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})


# File lists
set(restnotifier_SOURCES
        main.cpp
        trayicon.cpp
        settingsdialog.cpp
        restdialog.cpp
        idletime.c
        restnotifier.rc)

set(restnotifier_HEADERS
        trayicon.h
        settingsdialog.h
        restdialog.h)

set(restnotifier_FORMS
        settingsdialog.ui
        restdialog.ui)

set(restnotifier_RESOURCES
        icons.qrc)


# Run Qt preprocessors
QT4_WRAP_CPP(restnotifier_HEADERS_MOC ${restnotifier_HEADERS})
QT4_WRAP_UI(restnotifier_FORMS_HEADERS ${restnotifier_FORMS})
QT4_ADD_RESOURCES(restnotifier_RESOURCES_RCC ${restnotifier_RESOURCES})


# Set main build target
add_executable(restnotifier
                ${restnotifier_SOURCES}
                ${restnotifier_HEADERS_MOC}
                ${restnotifier_FORMS_HEADERS}
                ${restnotifier_RESOURCES_RCC})


# Disable console window on windows
if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

# Set strict compiler flags if possible
foreach(FLAG -Wall -Wextra -Werror)
    CHECK_CXX_COMPILER_FLAG(${FLAG} CXX_OK)
    CHECK_C_COMPILER_FLAG(${FLAG} C_OK)
    if(${CXX_OK} AND ${C_OK})
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAG}")
    endif()
endforeach()

# Set linking options
# And link to libxss if on unix
set(LIBS ${QT_LIBRARIES})
if(UNIX)
    list(APPEND LIBS -lXss)
endif()

target_link_libraries(restnotifier ${LIBS})
