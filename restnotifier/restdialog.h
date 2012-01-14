#ifndef RESTDIALOG_H
#define RESTDIALOG_H

#include <QDialog>
#include <QSharedPointer>

#include "ui_restdialog.h"
#include "messagecontent.h"


class RestDialog : public QDialog
{
    Q_OBJECT

// PRIVATE
    QSharedPointer<Ui::RestDialog> ui_restDialog;
    MessageContent *messageContent;

// PUBLIC
public:
    explicit RestDialog(QWidget *parent = 0);
    bool isPostponed() const;
};

#endif // RESTDIALOG_H
