#include <QPointer>
#include <QMessageBox>
#include <QTimer>

#include "trayicon.h"
#include "settingsdialog.h"
#include "restdialog.h"


TrayIcon::TrayIcon(QObject *parent) :
    QSystemTrayIcon(parent)
{
    icon = QSharedPointer<QIcon>(new QIcon(":/cloud.png"));
    menu = QSharedPointer<QMenu>(new QMenu);
    isPostponedNow = false;

    // setup context menu
    setIcon(*icon);
    QIcon quitIcon(":/Actions-application-exit-icon.png");
    QIcon settingsIcon(":/Actions-configure-icon.png");
    menu->addAction(settingsIcon, tr("Settings"), this, SLOT(showSettings()));
    menu->addSeparator();
    menu->addAction(quitIcon, tr("Quit"), this, SIGNAL(quitScheduled()));
    setContextMenu(menu.data());

    // setup timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(showRestMessage()));
    timer->start(getIntervalMsecs());
}

void TrayIcon::showSettings()
{
    // show dialog
    QPointer<SettingsDialog> settingsDialog(new SettingsDialog);
    settingsDialog->exec();
    delete settingsDialog;

    // reset timer if timeout has changed
    int interval = getIntervalMsecs();
    if ((timer->interval() != interval) && (!isPostponedNow))
    {
        timer->stop();
        timer->start(interval);
    }
}

void TrayIcon::showTrayMessage()
{
    QString message = settings.value("message", "").toString();
    if (message.size() > 100)
        message = "";
    showMessage("Restnotifier", message, Information);
}

// returns true if message was postponed
bool TrayIcon::showDialogMessage()
{
    QPointer<RestDialog> restDialog(new RestDialog);
    restDialog->exec();
    bool postpone = restDialog->isPostponed();
    delete restDialog;
    return postpone;
}

void TrayIcon::showRestMessage()
{
    timer->stop();
    MessageType mt = (MessageType)(settings.value("m_type", 0).toInt());
    bool postpone = false;
    switch (mt)
    {
    default:
    case MT_TRAY:
        showTrayMessage();
        break;
    case MT_DIALOG:
        postpone = showDialogMessage();
        break;
    }
    // postpone if needed
    const int postponeTime = 60000 * 5; // 5 min to msec
    if (postpone)
    {
        timer->start(postponeTime);
        isPostponedNow = true;
    }
    else
    {
        timer->start(getIntervalMsecs());
        isPostponedNow = false;
    }
}

int TrayIcon::getIntervalMsecs() const
{
    bool ok;
    int interval = settings.value("interval", 60).toInt(&ok);
    if ((!ok) || (interval > 2000))
        interval = 60;
    interval *= 60000; // to msec
    return interval;
}
