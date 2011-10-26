#include <QPixmap>
#include <QDesktopWidget>

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

    // check that image is not bigger than screen resolution
    QSize imageSize = image.size();
    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();
    if ((imageSize.height() >= screenHeight) ||
            (imageSize.width() >= screenWidth))
    {
        // let's scale it
        image = image.scaled((screenWidth - width() - 50),
                             (screenHeight - height() - 50),
                             Qt::KeepAspectRatio);
    }

    ui_restDialog->imageLabel->setPixmap(image);
}

bool RestDialog::isPostponed() const
{
    return ui_restDialog->afterCheckBox->isChecked();
}
