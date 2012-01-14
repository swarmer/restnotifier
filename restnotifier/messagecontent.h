#ifndef MESSAGECONTENT_H
#define MESSAGECONTENT_H

#include <QWidget>

#include "settings.h"


namespace Ui {
class MessageContent;
}

class MessageContent : public QWidget
{
    Q_OBJECT

// PRIVATE
private:
    Ui::MessageContent *ui;
    Settings settings;

    void setImage();

// PUBLIC
public:
    explicit MessageContent(QWidget *parent = 0);
    ~MessageContent();
};

#endif // MESSAGECONTENT_H
