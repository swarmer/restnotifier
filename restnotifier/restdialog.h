#ifndef RESTDIALOG_H
#define RESTDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QSharedPointer>

#include "ui_restdialog.h"


class RestDialog : public QDialog
{
    Q_OBJECT

// PRIVATE
    QSettings settings;
    QSharedPointer<Ui::RestDialog> ui_restDialog;

    void setImage();

// PUBLIC
public:
    explicit RestDialog(QWidget *parent = 0);
    bool isPostponed() const;
};

#endif // RESTDIALOG_H
