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
    {
        lang = QLocale::system().name();
        lang.truncate(lang.indexOf('_'));
    }
    if (lang == "ru")
    {
        QLocale::setDefault(QLocale("ru"));

        // install qt translator
#if defined Q_OS_WIN
        const QString loc;
#else
        const QString loc = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
#endif
        qtTranslator.load("qt_ru", loc);
        app.installTranslator(&qtTranslator);

        // install app translator
        QString translationsPath = settings.value("tr_path", QString()).toString();
        translator.load("restnotifier_ru", translationsPath);
        app.installTranslator(&translator);
    }

    TrayIcon *trayIcon = new TrayIcon();
    trayIcon->show();
    QObject::connect(trayIcon, SIGNAL(quitScheduled()), &app, SLOT(quit()));
    int code = app.exec();
    delete trayIcon;
    return code;
}
