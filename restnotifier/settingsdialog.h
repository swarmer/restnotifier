#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSharedPointer>

#include "settings.h"
#include "ui_settingsdialog.h"


class SettingsDialog : public QDialog
{
    Q_OBJECT

// PRIVATE
    Settings settings;
    QSharedPointer<Ui::SettingsDialog> ui_settingsDialog;

    void loadSettings();

    // loading functions
    void loadLanguageSettings();
    void loadImageSettings();
    void loadIdleSettings();
    void loadMessageSettings();
    void loadIntervalSettings();
    void loadSoundSettings();
    void loadLockSettings();

    // saving functions
    void saveLanguageSettings();
    void saveImageSettings();
    void saveIdleSettings();
    void saveMessageSettings();
    void saveIntervalSettings();
    void saveSoundSettings();
    void saveLockSettings();

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
