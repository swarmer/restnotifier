#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QSharedPointer>
#include <QIcon>
#include <QMenu>

#include "settings.h"


class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

// PRIVATE
    QSharedPointer<QMenu> menu;
    Settings settings;
    QTimer *timer;

    int getIntervalMsecs() const;
    bool showDialogMessage(); // returns true if message was postponed
    void showLockingMessage();
    void playSound();
    bool canNotify();

private slots:
    void showSettings();
    void showRestMessage();


// PUBLIC
public:
    explicit TrayIcon(QObject *parent = 0);

signals:
    void quitScheduled();
};

#endif // TRAYICON_H
