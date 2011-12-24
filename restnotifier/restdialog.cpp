#include <QPixmap>
#include <QDesktopWidget>

#include "restdialog.h"


RestDialog::RestDialog(QWidget *parent) :
    QDialog(parent)
{
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags((flags & ~Qt::WindowContextHelpButtonHint) |
                   Qt::WindowStaysOnTopHint);
    setWindowState(Qt::WindowFullScreen);
    ui_restDialog = QSharedPointer<Ui::RestDialog>(new Ui::RestDialog());
    ui_restDialog->setupUi(this);

    // set message
    QString message = settings.message();
    ui_restDialog->messageLabel->setText(message);

    // possibly set image
    if (settings.useImage())
        setImage();
}

void RestDialog::setImage()
{
    QPixmap image(settings.imagePath());
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
