#include <QPixmap>
#include <QDesktopWidget>

#include "messagecontent.h"
#include "ui_messagecontent.h"


MessageContent::MessageContent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageContent)
{
    ui->setupUi(this);

    // set message
    QString message = settings.message();
    ui->messageLabel->setText(message);

    // possibly set image
    if (settings.useImage())
        setImage();
}

void MessageContent::setImage()
{
    QPixmap image(settings.imagePath());
    if (image.isNull())
        return;

    // check that image is not bigger than screen resolution
    QSize imageSize = image.size();
    QWidget *parent = parentWidget();
    int screenWidth = QApplication::desktop()->width();
    int screenHeight = QApplication::desktop()->height();
    int widthPadding = 100;
    int heightPadding = height() + 100;
    if (parent)
        heightPadding += parent->height();
    if ((imageSize.height() >= screenHeight) ||
            (imageSize.width() >= screenWidth))
    {
        // let's scale it
        image = image.scaled((screenWidth - widthPadding),
                             (screenHeight - heightPadding),
                             Qt::KeepAspectRatio);
    }

    ui->imageLabel->setPixmap(image);
}

MessageContent::~MessageContent()
{
    delete ui;
}
