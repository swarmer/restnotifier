#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>


enum MessageType
{
    MT_TRAY = 0,
    MT_DIALOG = 1
};


class Settings
{
// PRIVATE
    QSettings qsettings;

// PUBLIC
public:
    // minutes
    int interval() const;
    void setInterval(int minutes);

    QString message() const;
    void setMessage(const QString& message);

    MessageType messageType() const;
    void setMessageType(MessageType mt);

    bool useImage() const;
    void setUseImage(bool use);

    QString imagePath() const;
    void setImagePath(const QString& path);

    QString language() const;
    void setLanguage(const QString& language);

    bool checkIdle() const;
    void setCheckIdle(bool check);

    // seconds
    int idleLimit() const;
    void setIdleLimit(int seconds);

    bool useSound() const;
    void setUseSound(bool use);

    QString soundPath() const;
    void setSoundPath(const QString& path);
};

#endif // SETTINGS_H
