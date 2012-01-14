#include <QShowEvent>
#include <QLayout>

#include "lockingrestdialog.h"

#if defined Q_WS_X11
#include <QX11Info>
#include <X11/Xlib.h>

#endif


LockingRestDialog::LockingRestDialog(QWidget *parent) :
    QDialog(parent)
{
    // gui
    messageContent = QSharedPointer<MessageContent>(new MessageContent);
    ui = QSharedPointer<Ui::LockingRestDialog>(new Ui::LockingRestDialog);
    ui->setupUi(this);
    setWindowState(Qt::WindowFullScreen);
    QVBoxLayout *vlayout = dynamic_cast<QVBoxLayout*>(layout());
    vlayout->insertWidget(0, messageContent.data());
    adjustSize();

    eventLoop = new QEventLoop(this);
    timeLeft = settings.lockTime();
    updateTimeLeft();

    // setup timer
    timer.setInterval(1000);
    connect(&timer, SIGNAL(timeout()), SLOT(timerTick()));
}

void LockingRestDialog::executeLocking()
{
    show();
    connect(this, SIGNAL(finished(int)), SLOT(dialogClosed()));

    // process events so that qt shows the window
    // X keyboard locking magic doesn't work unless the window is visible
    eventLoop->processEvents();
    lockScreen();
    timer.start();
    eventLoop->exec();
}

void LockingRestDialog::timerTick()
{
    timeLeft = timeLeft.addSecs(-1);
    updateTimeLeft();
    if ((timeLeft.minute() == 0) && (timeLeft.second() == 0))
    {
        accept();
        return;
    }
    timer.start();
}

void LockingRestDialog::updateTimeLeft()
{
    QString timeText = timeLeft.toString("mm:ss");
    ui->timeLeftLabel->setText(timeText);
}

void LockingRestDialog::dialogClosed()
{
    unlockScreen();
    eventLoop->exit();
}

void LockingRestDialog::lockScreen()
{
//linux
#if defined Q_WS_X11
    QX11Info xinfo = x11Info();
    Display *display = xinfo.display();
    Window wnd = winId();
    XGrabKeyboard(display, wnd, False,
                  GrabModeAsync, GrabModeAsync, CurrentTime);
// ^ linux

#endif
}

void LockingRestDialog::unlockScreen()
{
//linux
#if defined Q_WS_X11
    QX11Info xinfo = x11Info();
    Display *display = xinfo.display();
    XUngrabKeyboard(display, CurrentTime);
// ^ linux

#endif
}
