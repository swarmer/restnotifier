cmake_minimum_required(VERSION 2.8)

project(restnotifier)

find_package(Qt4 REQUIRED)


set(restnotifier_SOURCES
        main.cpp
        trayicon.cpp
        settingsdialog.cpp
        restdialog.cpp
        idletime.c)
        
set(restnotifier_HEADERS
        trayicon.h
        settingsdialog.h
        restdialog.h)
        
set(restnotifier_FORMS
        settingsdialog.ui
        restdialog.ui)
        
set(restnotifier_RESOURCES
        icons.qrc)


include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})


QT4_WRAP_CPP(restnotifier_HEADERS_MOC ${restnotifier_HEADERS})
QT4_WRAP_UI(restnotifier_FORMS_HEADERS ${restnotifier_FORMS})
QT4_ADD_RESOURCES(restnotifier_RESOURCES_RCC ${restnotifier_RESOURCES})


include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(restnotifier
                ${restnotifier_SOURCES}
                ${restnotifier_HEADERS_MOC}
                ${restnotifier_FORMS_HEADERS}
                ${restnotifier_RESOURCES_RCC})
target_link_libraries(restnotifier
                        ${QT_LIBRARIES}
                        -lXss)
