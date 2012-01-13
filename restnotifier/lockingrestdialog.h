#ifndef LOCKINGRESTDIALOG_H
#define LOCKINGRESTDIALOG_H

#include <QEventLoop>
#include <QDialog>
#include <QSharedPointer>
#include <QVBoxLayout>

#include "messagecontent.h"
#include "ui_lockingrestdialog.h"


class LockingRestDialog : public QDialog
{
    Q_OBJECT

// PUBLIC
public:
    explicit LockingRestDialog(QWidget *parent = 0);
    void executeLocking();

// PRIVATE
private:
    QEventLoop *eventLoop;
    QSharedPointer<MessageContent> messageContent;
    QSharedPointer<Ui::LockingRestDialog> ui;

private slots:
    void lockScreen();
    void unlockScreen();
    void dialogClosed();
};

#endif // LOCKINGRESTDIALOG_H
