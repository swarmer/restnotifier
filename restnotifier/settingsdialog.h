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

    // loading functions
    void loadLanguageSettings();
    void loadImageSettings();
    void loadIdleSettings();
    void loadMessageSettings();
    void loadIntervalSettings();
    void loadSoundSettings();

    // saving functions
    void saveLanguageSettings();
    void saveImageSettings();
    void saveIdleSettings();
    void saveMessageSettings();
    void saveIntervalSettings();
    void saveSoundSettings();

private slots:
    void saveSettings();
    void showImagePathDialog();
    void showSoundPathDialog();
    void checkFilePaths();
    void checkFilePath(QLineEdit *lineEdit);


// PUBLIC
public:
    explicit SettingsDialog(QWidget *parent = 0);
};

#endif // SETTINGSDIALOG_H
