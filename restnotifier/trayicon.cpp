#include <QPointer>

#include "trayicon.h"
#include "settingsdialog.h"


TrayIcon::TrayIcon(QObject *parent) :
    QSystemTrayIcon(parent)
{
    icon = QSharedPointer<QIcon>(new QIcon(":/cloud.png"));
    menu = QSharedPointer<QMenu>(new QMenu);
    settings = QSharedPointer<QSettings>(new QSettings);
    setIcon(*icon);
    // TODO: add icons
    menu->addAction(tr("Settings"), this, SLOT(showSettings()));
    menu->addAction(tr("Quit"), this, SIGNAL(quitScheduled()));
    setContextMenu(menu.data());
}

void TrayIcon::showSettings()
{
    QPointer<SettingsDialog> settingsDialog(new SettingsDialog(settings));
    settingsDialog->exec();
    delete settingsDialog;
}
