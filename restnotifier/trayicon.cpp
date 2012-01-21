#include <QPointer>
#include <QMessageBox>
#include <QTimer>
#include <QSound>

#include "trayicon.h"
#include "settingsdialog.h"
#include "restdialog.h"
#include "lockingrestdialog.h"

extern "C" int getIdleSecs(); // idletime.c


TrayIcon::TrayIcon(QObject *parent) :
    QSystemTrayIcon(parent)
{
    menu = QSharedPointer<QMenu>(new QMenu);

    // setup context menu
    QIcon icon(":/icons/restnotifier.png");
    QIcon quitIcon(":/icons/Actions-application-exit-icon.png");
    QIcon settingsIcon(":/icons/Actions-configure-icon.png");
    setIcon(icon);
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
    int interval1 = getIntervalMsecs();
    QPointer<SettingsDialog> settingsDialog(new SettingsDialog);
    settingsDialog->exec();
    delete settingsDialog;
    int interval2 = getIntervalMsecs();
    if (interval1 != interval2)
    {
        timer->stop();
        timer->start(interval2);
    }
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

bool TrayIcon::showLockingMessage()
{
    QPointer<LockingRestDialog> lockingRestDialog(new LockingRestDialog);
    lockingRestDialog->executeLocking();
    bool postpone = lockingRestDialog->isPostponed();
    delete lockingRestDialog;
    return postpone;
}

void TrayIcon::playSound()
{
    if (QSound::isAvailable())
    {
        QSound::play(settings.soundPath());
    }
}

void TrayIcon::showRestMessage()
{
    timer->stop();
    bool postpone = false;

    // show message itself
    if (canNotify())
    {
        // sound notification
        if (settings.useSound())
            playSound();

        if (settings.lockScreen())
            postpone = showLockingMessage();
        else
            postpone = showDialogMessage();
    }

    // postpone if needed
    const int postponeTime = 60000 * 5; //to msec
    if (postpone)
        timer->start(postponeTime);
    else
        timer->start(getIntervalMsecs());
}

bool TrayIcon::canNotify()
{
    // check if message should be shown
    bool canShow = true;
    if (settings.checkIdle())
    {
        int idleSec = getIdleSecs();
        if (idleSec != -1)
        {
            QTime idleLimitTime = settings.idleLimit();
            int idleLimitSec = QTime(0, 0).msecsTo(idleLimitTime) / 1000;
            if (idleSec >= idleLimitSec)
                canShow = false;
        }
    }
    return canShow;
}

int TrayIcon::getIntervalMsecs() const
{
    QTime interval = settings.interval();
    int intervalMsec = QTime(0, 0).msecsTo(interval);
    return intervalMsec;
}
