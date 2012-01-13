#include <QVariant>
#include <QTime>
#include <QLocale>
#include <QPointer>
#include <QFileDialog>
#include <QPalette>
#include <QFileInfo>
#include <QSound>

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

    // check that QSound is available
    if (!QSound::isAvailable())
    {
        ui_settingsDialog->soundGroupBox->hide();
        adjustSize();
    }

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
    loadLockSettings();
}

// loading functions
void SettingsDialog::loadLanguageSettings()
{
    QString language = settings.language();
    QComboBox *langBox = ui_settingsDialog->languageComboBox;
    if (language == "ru")
        langBox->setCurrentIndex(langBox->findText(QString::fromUtf8("Русский")));
    else
        langBox->setCurrentIndex(langBox->findText("English"));
}

void SettingsDialog::loadImageSettings()
{
    // set whether to use image
    bool useImage = settings.useImage();
    ui_settingsDialog->imageGroupBox->setChecked(useImage);

    // set image file path
    QString imagePath = settings.imagePath();
    ui_settingsDialog->imageLineEdit->setText(imagePath);
}

void SettingsDialog::loadIdleSettings()
{
    // set whether to check user idle time
    bool checkIdle = settings.checkIdle();
    ui_settingsDialog->idleGroupBox->setChecked(checkIdle);

    // set idle time limit
    QTime idleTime = settings.idleLimit();
    ui_settingsDialog->idleTimeEdit->setTime(idleTime);
}

void SettingsDialog::loadMessageSettings()
{
    // set message
    QString message = settings.message();
    ui_settingsDialog->messageLine->setText(message);
}

void SettingsDialog::loadIntervalSettings()
{
    QTime intervalTime = settings.interval();
    ui_settingsDialog->intervalTime->setTime(intervalTime);
}

void SettingsDialog::loadSoundSettings()
{
    // set whether to use sound
    bool useSound = settings.useSound();
    ui_settingsDialog->soundGroupBox->setChecked(useSound);

    // set sound file path
    QString soundPath = settings.soundPath();
    ui_settingsDialog->soundLineEdit->setText(soundPath);
}

void SettingsDialog::loadLockSettings()
{
    // set whether to lock the screen
    bool lockScreen = settings.lockScreen();
    ui_settingsDialog->lockGroupBox->setChecked(lockScreen);

    // set lock time
    QTime lockTime = settings.lockTime();
    ui_settingsDialog->lockTime->setTime(lockTime);
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
    saveLockSettings();
}

// saving functions
void SettingsDialog::saveLanguageSettings()
{
    if (ui_settingsDialog->languageComboBox->currentText() ==
            QString::fromUtf8("Русский"))
    {
        settings.setLanguage("ru");
    }
    else
        settings.setLanguage("en");
}

void SettingsDialog::saveImageSettings()
{
    // save whether to use image
    bool useImage = ui_settingsDialog->imageGroupBox->isChecked();
    settings.setUseImage(useImage);

    // save image file path
    QString imagePath = ui_settingsDialog->imageLineEdit->text();
    settings.setImagePath(imagePath);
}

void SettingsDialog::saveIdleSettings()
{
    // save whether to check user idle time
    bool checkIdle = ui_settingsDialog->idleGroupBox->isChecked();
    settings.setCheckIdle(checkIdle);

    // save idle time limit
    QTime idleLimit = ui_settingsDialog->idleTimeEdit->time();
    settings.setIdleLimit(idleLimit);
}

void SettingsDialog::saveMessageSettings()
{
    // save message
    settings.setMessage(ui_settingsDialog->messageLine->text());
}

void SettingsDialog::saveIntervalSettings()
{
    QTime time = ui_settingsDialog->intervalTime->time();
    settings.setInterval(time);
}

void SettingsDialog::saveSoundSettings()
{
    // save whether to use sound
    bool useSound = ui_settingsDialog->soundGroupBox->isChecked();
    settings.setUseSound(useSound);

    // save sound file path
    QString soundPath = ui_settingsDialog->soundLineEdit->text();
    settings.setSoundPath(soundPath);
}

void SettingsDialog::saveLockSettings()
{
    // save whether to lock the screen
    bool lockScreen = ui_settingsDialog->lockGroupBox->isChecked();
    settings.setLockScreen(lockScreen);

    // save lock time
    QTime lockTime = ui_settingsDialog->lockTime->time();
    settings.setLockTime(lockTime);
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
    // set line color to red if file doesn't exist
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
