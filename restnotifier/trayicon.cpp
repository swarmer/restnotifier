#include <QPointer>
#include <QMessageBox>
#include <QTimer>
#include <QSound>

#include "trayicon.h"
#include "settingsdialog.h"
#include "restdialog.h"

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

void TrayIcon::playSound()
{
    if (QSound::isAvailable())
    {
        QString soundPath = settings.value("snd_path", QString()).toString();
        QSound::play(soundPath);
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
        bool useSound = settings.value("use_sound", false).toBool();
        if (useSound)
            playSound();

        // usual message
        MessageType mt = (MessageType)(settings.value("m_type", 0).toInt());
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
    }

    // postpone if needed
    const int postponeTime = 60000 * 5; // 5 min to msec
    if (postpone)
        timer->start(postponeTime);
    else
        timer->start(getIntervalMsecs());
}

bool TrayIcon::canNotify()
{
    // check if message should be shown
    bool canShow = true;
    bool checkIdle = settings.value("check_idle", true).toBool();
    if (checkIdle)
    {
        int idleSec = getIdleSecs();
        if (idleSec != -1)
        {
            bool ok;
            int idleLimit = settings.value("idle_limit", 60).toInt(&ok);
            if (!ok)
                idleLimit = 60;
            if (idleSec >= idleLimit)
                canShow = false;
        }
    }
    return canShow;
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
