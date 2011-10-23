#include <QVariant>
#include <QTime>
#include <QLocale>
#include <QPointer>
#include <QFileDialog>
#include <QPalette>
#include <QFileInfo>

#include "settingsdialog.h"


SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    // window setup
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags & ~Qt::WindowContextHelpButtonHint);
    ui_settingsDialog = QSharedPointer<Ui::SettingsDialog>(new Ui::SettingsDialog);
    ui_settingsDialog->setupUi(this);
    connect(this, SIGNAL(accepted()), SLOT(saveSettings()));
    ui_settingsDialog->restartLabel->hide();
    loadSettings();
    // connect after loading settings
    // because otherwise unexpected signal may be emitted

    // show label asking to restart app to apply translation
    connect(ui_settingsDialog->languageComboBox, SIGNAL(currentIndexChanged(int)),
            ui_settingsDialog->restartLabel, SLOT(show()));

    // check that image and sound files exist
    connect(ui_settingsDialog->imageLineEdit, SIGNAL(textChanged(QString)),
            SLOT(checkFilePaths()));
    connect(ui_settingsDialog->soundLineEdit, SIGNAL(textChanged(QString)),
            SLOT(checkFilePaths()));

    // show file path dialogs
    connect(ui_settingsDialog->imagePathButton, SIGNAL(clicked()),
            SLOT(showImagePathDialog()));
    connect(ui_settingsDialog->soundPathButton, SIGNAL(clicked()),
            SLOT(showSoundPathDialog()));
    checkFilePaths();
}

void SettingsDialog::loadSettings()
{
    loadIntervalSettings();
    loadMessageSettings();
    loadIdleSettings();
    loadImageSettings();
    loadLanguageSettings();
    loadSoundSettings();
}

// loading functions
void SettingsDialog::loadLanguageSettings()
{
    QString language;
    if (settings.contains("lang"))
        language = settings.value("lang").toString();
    else
        language = QLocale::languageToString(QLocale().language());
    QComboBox *langBox = ui_settingsDialog->languageComboBox;
    if (language == "ru")
        langBox->setCurrentIndex(langBox->findText(QString::fromUtf8("Русский")));
    else
        langBox->setCurrentIndex(langBox->findText("English"));
}

void SettingsDialog::loadImageSettings()
{
    // set whether to use image
    bool useImage = settings.value("use_img", false).toBool();
    ui_settingsDialog->imageGroupBox->setChecked(useImage);

    // set image file path
    QString imagePath = settings.value("img_path", QString()).toString();
    ui_settingsDialog->imageLineEdit->setText(imagePath);
}

void SettingsDialog::loadIdleSettings()
{
    // set whether to check user idle time
    bool checkIdle = settings.value("check_idle", true).toBool();
    ui_settingsDialog->idleGroupBox->setChecked(checkIdle);

    // set idle time limit
    bool ok;
    int seconds = settings.value("idle_limit", 60).toInt(&ok);
    if (!ok)
        seconds = 60;
    int hours, minutes;
    hours = seconds / 3600;
    seconds %= 3600;
    minutes = seconds / 60;
    seconds %= 60;
    QTime idleTime(hours, minutes, seconds);
    ui_settingsDialog->idleTimeEdit->setTime(idleTime);
}

void SettingsDialog::loadMessageSettings()
{
    // set message
    QString message = settings.value("message",
                                      tr("It's time to rest")).toString();
    ui_settingsDialog->messageLine->setText(message);

    // set message type
    bool ok;
    MessageType mt = (MessageType)(settings.value("m_type", 0).toInt(&ok));
    if (!ok)
        mt = MT_TRAY;
    switch (mt)
    {
    case MT_TRAY:
        ui_settingsDialog->trayRadio->toggle();
        break;
    case MT_DIALOG:
        ui_settingsDialog->dialogRadio->toggle();
        break;
    }
}

void SettingsDialog::loadIntervalSettings()
{
    int interval; //minutes
    bool ok;
    interval = settings.value("interval", 60).toInt(&ok);
    if (!ok)
        interval = 60;
    int hours, minutes;
    hours = interval / 60;
    minutes = interval % 60;
    QTime intervalTime(hours, minutes);
    ui_settingsDialog->intervalTime->setTime(intervalTime);
}

void SettingsDialog::loadSoundSettings()
{
    // set whether to use sound
    bool useSound = settings.value("use_sound", false).toBool();
    ui_settingsDialog->soundGroupBox->setChecked(useSound);

    // set sound file path
    QString soundPath = settings.value("snd_path", QString()).toString();
    ui_settingsDialog->soundLineEdit->setText(soundPath);
}
// ^ loading functions


void SettingsDialog::saveSettings()
{
    saveIntervalSettings();
    saveMessageSettings();
    saveIdleSettings();
    saveImageSettings();
    saveLanguageSettings();
    saveSoundSettings();
}

// saving functions
void SettingsDialog::saveLanguageSettings()
{
    if (ui_settingsDialog->languageComboBox->currentText() ==
            QString::fromUtf8("Русский"))
    {
        settings.setValue("lang", "ru");
    }
    else
        settings.setValue("lang", "en");
}

void SettingsDialog::saveImageSettings()
{
    // save whether to use image
    bool useImage = ui_settingsDialog->imageGroupBox->isChecked();
    settings.setValue("use_img", useImage);

    // save image file path
    QString imagePath = ui_settingsDialog->imageLineEdit->text();
    settings.setValue("img_path", imagePath);
}

void SettingsDialog::saveIdleSettings()
{
    // save whether to check user idle time
    bool checkIdle = ui_settingsDialog->idleGroupBox->isChecked();
    settings.setValue("check_idle", checkIdle);

    // save idle time limit
    QTime idleLimit = ui_settingsDialog->idleTimeEdit->time();
    int seconds = (idleLimit.hour() * 3600) + (idleLimit.minute() * 60) +
            idleLimit.second();
    settings.setValue("idle_limit", seconds);
}

void SettingsDialog::saveMessageSettings()
{
    // save message
    settings.setValue("message", ui_settingsDialog->messageLine->text());

    // save message type
    int m_type = 0;
    if (ui_settingsDialog->trayRadio->isChecked())
        m_type = (int)MT_TRAY;
    else if (ui_settingsDialog->dialogRadio->isChecked())
        m_type = (int)MT_DIALOG;
    settings.setValue("m_type", m_type);
}

void SettingsDialog::saveIntervalSettings()
{
    int interval; //minutes
    QTime time = ui_settingsDialog->intervalTime->time();
    interval = (time.hour() * 60) + time.minute();
    settings.setValue("interval", interval);
}

void SettingsDialog::saveSoundSettings()
{
    // save whether to use sound
    bool useSound = ui_settingsDialog->soundGroupBox->isChecked();
    settings.setValue("use_sound", useSound);

    // save sound file path
    QString soundPath = ui_settingsDialog->soundLineEdit->text();
    settings.setValue("snd_path", soundPath);
}
// ^ saving functions


void SettingsDialog::showImagePathDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select image"),
            "", tr("Image files (*.png *.bmp *.jpeg *.jpg)"));
    if (!fileName.isEmpty())
        ui_settingsDialog->imageLineEdit->setText(fileName);
}

void SettingsDialog::showSoundPathDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select sound"),
            "", tr("Sound file (*.wav)"));
    if (!fileName.isEmpty())
        ui_settingsDialog->soundLineEdit->setText(fileName);
}

void SettingsDialog::checkFilePaths()
{
    checkFilePath(ui_settingsDialog->imageLineEdit);
    checkFilePath(ui_settingsDialog->soundLineEdit);
}

void SettingsDialog::checkFilePath(QLineEdit *lineEdit)
{
    QPalette palette = lineEdit->palette();
    QFileInfo info(lineEdit->text());
    if (!info.exists() || !info.isFile())
    {
        palette.setColor(QPalette::Active, QPalette::Text, Qt::red);
        lineEdit->setPalette(palette);
    }
    else
    {
        lineEdit->setPalette(qApp->palette());
    }
}
