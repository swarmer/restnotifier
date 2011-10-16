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

    // setup context menu
    setIcon(*icon);
    QStyle *style = QApplication::style();
    QIcon quitIcon = style->standardIcon(QStyle::SP_DialogCloseButton);
    menu->addAction(tr("Settings"), this, SLOT(showSettings()));
    menu->addSeparator();
    menu->addAction(quitIcon, tr("Quit"), this, SIGNAL(quitScheduled()));
    setContextMenu(menu.data());

    // setup timer
    timer = new QTimer(this);
    int interval; //minutes
    bool ok;
    interval = settings->value("interval", 60).toInt(&ok);
    if (!ok)
        interval = 60;
    connect(timer, SIGNAL(timeout()), SLOT(showRestMessage()));
    timer->start(interval * 60000); //minutes to msecs
}

void TrayIcon::showSettings()
{
    // show dialog
    QPointer<SettingsDialog> settingsDialog(new SettingsDialog(settings));
    settingsDialog->exec();
    delete settingsDialog;

    // reset timer if timeout has changed
    int interval; //minutes
    bool ok;
    interval = settings->value("interval", 60).toInt(&ok);
    if (!ok)
        interval = 60;
    interval *= 60000; // to msec
    if (timer->interval() != interval)
    {
        timer->stop();
        timer->start(interval);
    }
}

void TrayIcon::showRestMessage()
{
    QString message = settings->value("message", "").toString();
    showMessage("Restnotifier", message, Information);
}
