#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QSharedPointer>
#include <QAbstractButton>

#include "ui_settingsdialog.h"


class SettingsDialog : public QDialog
{
    Q_OBJECT

// PRIVATE
    QSharedPointer<QSettings> settings;
    QSharedPointer<Ui::SettingsDialog> ui_settingsDialog;

    void saveSettings();

private slots:
    void buttonClicked(QAbstractButton *button);


// PUBLIC
public:
    explicit SettingsDialog(QSharedPointer<QSettings> p_settings, QWidget *parent = 0);
};

#endif // SETTINGSDIALOG_H
