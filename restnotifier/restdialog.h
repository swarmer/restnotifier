#ifndef RESTDIALOG_H
#define RESTDIALOG_H

#include <QDialog>
#include <QSharedPointer>

#include "ui_restdialog.h"


class RestDialog : public QDialog
{
    Q_OBJECT

// PRIVATE
    QSharedPointer<Ui::RestDialog> ui_restDialog;

// PUBLIC
public:
    explicit RestDialog(QString& message, QWidget *parent = 0);
    bool isPostponed() const;
};

#endif // RESTDIALOG_H
