#include <QPixmap>

#include "restdialog.h"


RestDialog::RestDialog(QWidget *parent) :
    QDialog(parent)
{
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags((flags & ~Qt::WindowContextHelpButtonHint) |
                   Qt::WindowStaysOnTopHint);
    ui_restDialog = QSharedPointer<Ui::RestDialog>(new Ui::RestDialog());
    ui_restDialog->setupUi(this);

    // set message
    QString message = settings.value("message", QString()).toString();
    ui_restDialog->messageLabel->setText(message);

    // possibly set image
    bool useImage = settings.value("use_img", false).toBool();
    if (useImage)
        setImage();

    activateWindow();
}

void RestDialog::setImage()
{
    QString imagePath = settings.value("img_path", QString()).toString();
    QPixmap image(imagePath);
    if (image.isNull())
        return;
    ui_restDialog->imageLabel->setPixmap(image);
}

bool RestDialog::isPostponed() const
{
    return ui_restDialog->afterCheckBox->isChecked();
}
