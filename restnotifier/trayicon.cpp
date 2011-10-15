#include "trayicon.h"


TrayIcon::TrayIcon(QObject *parent) :
    QSystemTrayIcon(parent)
{
    icon = QSharedPointer<QIcon>(new QIcon(":/cloud.png"));
    menu = QSharedPointer<QMenu>(new QMenu);
    settings = QSharedPointer<QSettings>(new QSettings);
    setIcon(*icon);
    menu->addAction(tr("Exit"), this, SIGNAL(quitScheduled()));
    setContextMenu(menu.data());
}
