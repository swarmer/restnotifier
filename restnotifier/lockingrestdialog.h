#ifndef LOCKINGRESTDIALOG_H
#define LOCKINGRESTDIALOG_H

#include <QEventLoop>

#include "restdialog.h"


class LockingRestDialog : public RestDialog
{
    Q_OBJECT

// PUBLIC
public:
    explicit LockingRestDialog(QWidget *parent = 0);
    void executeLocking();

// PRIVATE
private:
    QEventLoop *eventLoop;

private slots:
    void lockScreen();
    void unlockScreen();
    void dialogClosed();
};

#endif // LOCKINGRESTDIALOG_H
