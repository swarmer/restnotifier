#include <QPointer>
#include <QStyle>
#include <QMessageBox>

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
    connect(timer, SIGNAL(timeout()), SLOT(showRestMessage()));
    timer->start(getIntervalMsecs());
}

void TrayIcon::showSettings()
{
    // show dialog
    QPointer<SettingsDialog> settingsDialog(new SettingsDialog(settings));
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

void TrayIcon::showRestMessage()
{
    timer->stop();
    QString message = settings->value("message", "").toString();
    MessageType mt = (MessageType)(settings->value("m_type", 0).toInt());
    switch (mt)
    {
    case MT_TRAY:
        showMessage("Restnotifier", message, Information);
        break;
    case MT_DIALOG:
        QPointer<QMessageBox> mbox(new QMessageBox);
        mbox->addButton(QMessageBox::Ok);
        mbox->setWindowTitle("Restnotifier");
        mbox->setText(message);
        mbox->setIcon(QMessageBox::Information);
        mbox->activateWindow();
        mbox->exec();
        delete mbox;
        break;
    }
    timer->start(getIntervalMsecs());
}

int TrayIcon::getIntervalMsecs()
{
    bool ok;
    int interval = settings->value("interval", 60).toInt(&ok);
    if (!ok)
        interval = 60;
    interval *= 60000; // to msec
    return interval;
}
