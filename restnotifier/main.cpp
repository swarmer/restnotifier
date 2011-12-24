#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>

#include "settings.h"
#include "trayicon.h"
#include "buildconfig.h"


void setLanguage()
{
    Settings settings;
    QTranslator *translator = new QTranslator(qApp);
    QTranslator *qtTranslator = new QTranslator(qApp);
    QString lang = settings.language();
    if (lang == "ru")
    {
        QLocale::setDefault(QLocale("ru"));

        bool ok;
        // install qt translator
        const QString loc = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
        ok = qtTranslator->load("qt_ru");
        if (!ok)
            ok = qtTranslator->load("qt_ru", loc);
        if (ok)
            qApp->installTranslator(qtTranslator);

        // install app translator
        ok = translator->load("restnotifier_ru");
#ifdef Q_OS_UNIX
        // PREFIX_PATH is defined in buildconfig.h
        const QString translationsPath(PREFIX_PATH"/share/restnotifier");
        if (!ok)
            ok = translator->load("restnotifier_ru", translationsPath);
#endif
        if (ok)
            qApp->installTranslator(translator);
    }
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QApplication::setOrganizationName("Restnotifier");
    app.setQuitOnLastWindowClosed(false);

    setLanguage();

    TrayIcon *trayIcon = new TrayIcon();
    trayIcon->show();
    QObject::connect(trayIcon, SIGNAL(quitScheduled()), &app, SLOT(quit()));
    int code = app.exec();
    delete trayIcon;
    return code;
}
