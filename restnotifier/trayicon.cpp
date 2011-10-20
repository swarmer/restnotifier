#include <QPointer>
#include <QStyle>
#include <QMessageBox>
#include <QTimer>

#include "trayicon.h"
#include "settingsdialog.h"


TrayIcon::TrayIcon(QObject *parent) :
    QSystemTrayIcon(parent)
{
    icon = QSharedPointer<QIcon>(new QIcon(":/cloud.png"));
    menu = QSharedPointer<QMenu>(new QMenu);

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
    if (timer->interval() != interval)
    {
        timer->stop();
        timer->start(interval);
    }
}

QString TrayIcon::getRestMessage() const
{
    QString message = settings.value("message", "").toString();
    if (message.size() > 100)
        message = "";
    return message;
}

void TrayIcon::showTrayMessage()
{
    QString message = getRestMessage();
    showMessage("Restnotifier", message, Information);
}

void TrayIcon::showDialogMessage()
{
    QString message = getRestMessage();
    QPointer<QMessageBox> mbox(new QMessageBox);
    mbox->addButton(QMessageBox::Ok);
    mbox->setWindowTitle("Restnotifier");
    mbox->setText(message);
    mbox->setIcon(QMessageBox::Information);
    mbox->activateWindow();
    mbox->exec();
    delete mbox;
}

void TrayIcon::showRestMessage()
{
    timer->stop();
    MessageType mt = (MessageType)(settings.value("m_type", 0).toInt());
    switch (mt)
    {
    default:
    case MT_TRAY:
        showTrayMessage();
        break;
    case MT_DIALOG:
        showDialogMessage();
        break;
    }
    timer->start(getIntervalMsecs());
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
