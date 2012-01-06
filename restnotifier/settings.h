#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QTime>


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
    QTime interval() const;
    void setInterval(QTime interval);

    QString message() const;
    void setMessage(const QString& message);

    bool useImage() const;
    void setUseImage(bool use);

    QString imagePath() const;
    void setImagePath(const QString& path);

    QString language() const;
    void setLanguage(const QString& language);

    bool checkIdle() const;
    void setCheckIdle(bool check);

    QTime idleLimit() const;
    void setIdleLimit(QTime idleLimit);

    bool useSound() const;
    void setUseSound(bool use);

    QString soundPath() const;
    void setSoundPath(const QString& path);
};

#endif // SETTINGS_H
