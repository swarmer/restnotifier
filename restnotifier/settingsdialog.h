#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QSharedPointer>

#include "ui_settingsdialog.h"


enum MessageType
{
    MT_TRAY = 0,
    MT_DIALOG = 1
};

class SettingsDialog : public QDialog
{
    Q_OBJECT

// PRIVATE
    QSettings settings;
    QSharedPointer<Ui::SettingsDialog> ui_settingsDialog;

    void loadSettings();

private slots:
    void saveSettings();
    void showImagePathDialog();
    void checkImagePath();


// PUBLIC
public:
    explicit SettingsDialog(QWidget *parent = 0);
};

#endif // SETTINGSDIALOG_H
