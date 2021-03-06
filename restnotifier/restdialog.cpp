#include "restdialog.h"


RestDialog::RestDialog(QWidget *parent) :
    QDialog(parent)
{
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags((flags & ~Qt::WindowContextHelpButtonHint) |
                   Qt::WindowStaysOnTopHint);
    ui_restDialog = QSharedPointer<Ui::RestDialog>(new Ui::RestDialog());
    ui_restDialog->setupUi(this);

    messageContent = new MessageContent(this);

    QVBoxLayout *vlayout = dynamic_cast<QVBoxLayout*>(layout());
    vlayout->insertWidget(0, messageContent);
    adjustSize();
}

bool RestDialog::isPostponed() const
{
    return ui_restDialog->afterCheckBox->isChecked();
}
