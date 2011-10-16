#include <QVariant>
#include <QTime>

#include "settingsdialog.h"


SettingsDialog::SettingsDialog(QSharedPointer<QSettings> p_settings,
                               QWidget *parent) :
    QDialog(parent)
{
    // window setup
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags & ~Qt::WindowContextHelpButtonHint);
    settings = p_settings;
    ui_settingsDialog = QSharedPointer<Ui::SettingsDialog>(new Ui::SettingsDialog);
    ui_settingsDialog->setupUi(this);
    connect(ui_settingsDialog->dialogButtonBox, SIGNAL(clicked(QAbstractButton*)),
            SLOT(buttonClicked(QAbstractButton*)));

    // set initial interval
    int interval; //minutes
    bool ok;
    interval = settings->value("interval", 60).toInt(&ok);
    if (!ok)
        interval = 60;
    int hours, minutes;
    hours = interval / 60;
    minutes = interval % 60;
    QTime time(hours, minutes);
    ui_settingsDialog->intervalTime->setTime(time);
    // ... message
    QString message = settings->value("message",
                                      tr("It's time to rest")).toString();
    ui_settingsDialog->messageLine->setText(message);
    // ... and message type
    MessageType mt = (MessageType)(settings->value("m_type", 0).toInt(&ok));
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

void SettingsDialog::buttonClicked(QAbstractButton *button)
{
    QDialogButtonBox::ButtonRole role =
            ui_settingsDialog->dialogButtonBox->buttonRole(button);
    if ((role == QDialogButtonBox::ApplyRole) ||
        (role == QDialogButtonBox::AcceptRole))
    {
        saveSettings();
    }
}

void SettingsDialog::saveSettings()
{
    int interval; //minutes
    QTime time = ui_settingsDialog->intervalTime->time();
    interval = (time.hour() * 60) + time.minute();
    settings->setValue("interval", interval);
    settings->setValue("message", ui_settingsDialog->messageLine->text());
    int m_type = 0;
    if (ui_settingsDialog->trayRadio->isChecked())
        m_type = (int)MT_TRAY;
    else if (ui_settingsDialog->dialogRadio->isChecked())
        m_type = (int)MT_DIALOG;
    settings->setValue("m_type", m_type);
}
