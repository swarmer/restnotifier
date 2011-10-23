SOURCES += \
    main.cpp \
    trayicon.cpp \
    settingsdialog.cpp \
    restdialog.cpp \
    idletime.c

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

unix:LIBS += -lXss

# strict compiler flags
unix {
    QMAKE_CXXFLAGS += -Wall -Wextra -Werror
}
