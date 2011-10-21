#include "restdialog.h"

RestDialog::RestDialog(QString& message, QWidget *parent) :
    QDialog(parent)
{
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags((flags & ~Qt::WindowContextHelpButtonHint) |
                   Qt::WindowStaysOnTopHint);
    ui_restDialog = QSharedPointer<Ui::RestDialog>(new Ui::RestDialog());
    ui_restDialog->setupUi(this);
    ui_restDialog->messageLabel->setText(message);
    activateWindow();
}

bool RestDialog::isPostponed() const
{
    return ui_restDialog->afterCheckBox->isChecked();
}
