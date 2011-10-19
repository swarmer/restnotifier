#include <QApplication>
#include <QSettings>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>

#include "trayicon.h"



int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QApplication::setOrganizationName("Restnotifier");
    app.setQuitOnLastWindowClosed(false);

    // Set language
    QSettings settings;
    QString lang;
    QTranslator translator, qtTranslator;
    if (settings.contains("lang"))
        lang = settings.value("lang").toString();
    else
        lang = QLocale::languageToString(QLocale::system().language());
    if (lang == "ru")
    {
        QLocale::setDefault(QLocale("ru_RU"));

        // install qt translator
#if defined Q_WS_X11
        const QString loc = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
#elif defined Q_WS_WIN
        const QString loc();
#endif
        qtTranslator.load("qt_" + QLocale().name(), loc);
        app.installTranslator(&qtTranslator);

        // install app translator
        translator.load("restnotifier_ru_RU");
        app.installTranslator(&translator);
    }

    TrayIcon *trayIcon = new TrayIcon();
    trayIcon->show();
    QObject::connect(trayIcon, SIGNAL(quitScheduled()), &app, SLOT(quit()));
    int code = app.exec();
    delete trayIcon;
    return code;
}
