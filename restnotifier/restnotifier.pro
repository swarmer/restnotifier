SOURCES += \
    main.cpp \
    trayicon.cpp \
    settingsdialog.cpp \
    restdialog.cpp

HEADERS += \
    trayicon.h \
    settingsdialog.h \
    restdialog.h

RESOURCES += \
    icons.qrc

FORMS += \
    settingsdialog.ui \
    restdialog.ui

TRANSLATIONS = \
    restnotifier_ru.ts


unix {
    QMAKE_CXXFLAGS += -Wall -Wextra -Werror
}



