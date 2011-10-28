#include <QApplication>
#include <QSettings>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>

#include "trayicon.h"


void setLanguage()
{
    QSettings settings;
    QString lang;
    QTranslator *translator = new QTranslator;
    QTranslator *qtTranslator = new QTranslator;
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
        if (!ok)
            ok = translator->load("restnotifier_ru", "/usr/share/restnotifier");
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
