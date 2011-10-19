#include <QVariant>
#include <QTime>
#include <QLocale>

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
    // connect after loading settings because it may emit unexpected signal
    connect(ui_settingsDialog->languageComboBox, SIGNAL(currentIndexChanged(int)),
            ui_settingsDialog->restartLabel, SLOT(show()));
}

void SettingsDialog::loadSettings()
{
    // set initial interval
    int interval; //minutes
    bool ok;
    interval = settings.value("interval", 60).toInt(&ok);
    if (!ok)
        interval = 60;
    int hours, minutes;
    hours = interval / 60;
    minutes = interval % 60;
    QTime time(hours, minutes);
    ui_settingsDialog->intervalTime->setTime(time);

    // set message
    QString message = settings.value("message",
                                      tr("It's time to rest")).toString();
    ui_settingsDialog->messageLine->setText(message);

    // set message type
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

    // set language
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

void SettingsDialog::saveSettings()
{
    // save interval
    int interval; //minutes
    QTime time = ui_settingsDialog->intervalTime->time();
    interval = (time.hour() * 60) + time.minute();
    settings.setValue("interval", interval);

    // save message
    settings.setValue("message", ui_settingsDialog->messageLine->text());

    // save message type
    int m_type = 0;
    if (ui_settingsDialog->trayRadio->isChecked())
        m_type = (int)MT_TRAY;
    else if (ui_settingsDialog->dialogRadio->isChecked())
        m_type = (int)MT_DIALOG;
    settings.setValue("m_type", m_type);

    // save language
    if (ui_settingsDialog->languageComboBox->currentText() ==
            QString::fromUtf8("Русский"))
    {
        settings.setValue("lang", "ru");
    }
    else
        settings.setValue("lang", "en");
}
