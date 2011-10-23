#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QSharedPointer>

#include "ui_settingsdialog.h"


/* Current settings keys:
  int interval:
    Interval of messages in minutes

  QString message:
    Message text

  MessageType m_type:
    Type of message

  bool use_img:
    Whether to embed image in notification dialog

  QString img_path:
    Path of image to embed

  QString lang:
    Language string ("ru" or "en")

  QString tr_path:
    Path to folder with translation files (to be used on linux)

  bool check_idle:
    Whether to check user idle time

  int idle_limit:
    Maximum idle time (in seconds)

  bool use_sound:
    Whether to use sound to notify user

  QString snd_path:
    Path to sound file
*/

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
