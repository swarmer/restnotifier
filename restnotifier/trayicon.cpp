#include <QPointer>
#include <QStyle>

#include "trayicon.h"
#include "settingsdialog.h"


TrayIcon::TrayIcon(QObject *parent) :
    QSystemTrayIcon(parent)
{
    icon = QSharedPointer<QIcon>(new QIcon(":/cloud.png"));
    menu = QSharedPointer<QMenu>(new QMenu);
    settings = QSharedPointer<QSettings>(new QSettings);
    setIcon(*icon);
    QStyle *style = QApplication::style();
    QIcon quitIcon = style->standardIcon(QStyle::SP_DialogCloseButton);
    menu->addAction(tr("Settings"), this, SLOT(showSettings()));
    menu->addSeparator();
    menu->addAction(quitIcon, tr("Quit"), this, SIGNAL(quitScheduled()));
    setContextMenu(menu.data());
    timer = new QTimer(this);
    int interval; //minutes
    bool ok;
    interval = settings->value("interval", 60).toInt(&ok);
    if (!ok)
        interval = 60;
    timer->setInterval(interval * 60000); //minutes to msecs
    connect(timer, SIGNAL(timeout()), SLOT(showRestMessage()));
    timer->start();
}

void TrayIcon::showSettings()
{
    QPointer<SettingsDialog> settingsDialog(new SettingsDialog(settings));
    settingsDialog->exec();
    delete settingsDialog;
    // TODO: check timeout
}

void TrayIcon::showRestMessage()
{
    QString message = settings->value("message", "").toString();
    showMessage("Restnotifier", message, Information);
}
