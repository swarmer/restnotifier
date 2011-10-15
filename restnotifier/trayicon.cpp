#include "trayicon.h"


TrayIcon::TrayIcon(QObject *parent) :
    QSystemTrayIcon(parent)
{
    icon = QSharedPointer<QIcon>(new QIcon(":/cloud.png"));
    menu = QSharedPointer<QMenu>(new QMenu);
    settings = QSharedPointer<Settings>(new Settings);
    setIcon(*icon);
    menu->addAction(tr("Exit"), this, SIGNAL(quitScheduled()));
    setContextMenu(menu.data());
}
