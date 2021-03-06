#ifndef LOCKINGRESTDIALOG_H
#define LOCKINGRESTDIALOG_H

#include <QEventLoop>
#include <QDialog>
#include <QSharedPointer>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>

#include "settings.h"
#include "messagecontent.h"
#include "ui_lockingrestdialog.h"


class QShortcut;


class LockingRestDialog : public QDialog
{
    Q_OBJECT

// PUBLIC
public:
    explicit LockingRestDialog(QWidget *parent = 0);
    void executeLocking();
    bool isPostponed() const;

// PRIVATE
private:
    QShortcut *postponeShortcut;
    QEventLoop *eventLoop;
    MessageContent *messageContent;
    QSharedPointer<Ui::LockingRestDialog> ui;
    QTimer timer;
    Settings settings;
    QTime timeLeft;
    bool postponed;

    void updateTimeLeft();

private slots:
    void postpone();
    void lockScreen();
    void unlockScreen();
    void dialogClosed();
    void timerTick();
};

#endif // LOCKINGRESTDIALOG_H
