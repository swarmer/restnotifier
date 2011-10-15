#include <QApplication>

#include "trayicon.h"



int main(int argc, char **argv)
{
    QApplication *app = new QApplication(argc, argv);
    QApplication::setOrganizationName("Restnotifier");
    TrayIcon *trayIcon = new TrayIcon();
    trayIcon->show();
    QObject::connect(trayIcon, SIGNAL(quitScheduled()), app, SLOT(quit()));
    int code = app->exec();
    delete trayIcon;
    delete app;
    return code;
}
