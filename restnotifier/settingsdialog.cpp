#include <QVariant>
#include <QTime>

#include "settingsdialog.h"


SettingsDialog::SettingsDialog(QSharedPointer<QSettings> p_settings,
                               QWidget *parent) :
    QDialog(parent)
{
    Qt::WindowFlags flags = windowFlags();
    setAttribute(Qt::WA_QuitOnClose, false);
    setWindowFlags(flags & ~Qt::WindowContextHelpButtonHint);
    settings = p_settings;
    ui_settingsDialog = QSharedPointer<Ui::SettingsDialog>(new Ui::SettingsDialog);
    ui_settingsDialog->setupUi(this);
    connect(ui_settingsDialog->dialogButtonBox, SIGNAL(clicked(QAbstractButton*)),
            SLOT(buttonClicked(QAbstractButton*)));
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
    QString message = settings->value("message", QString()).toString();
    ui_settingsDialog->messageLine->setText(message);
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
}
