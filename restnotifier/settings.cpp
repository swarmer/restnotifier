#include <QLocale>

#include "settings.h"


QTime Settings::interval() const
{
    bool ok;
    int intervalMinutes = qsettings.value("interval", 60).toInt(&ok);
    if (!ok)
        intervalMinutes = 60;
    int hours, minutes;
    hours = intervalMinutes / 60;
    minutes = intervalMinutes % 60;
    QTime intervalTime(hours, minutes);
    return intervalTime;
}

void Settings::setInterval(QTime interval)
{
    int intervalMinutes = (interval.hour() * 60) + interval.minute();
    qsettings.setValue("interval", intervalMinutes);
}


QString Settings::message() const
{
    return qsettings.value("message",
                           QObject::tr("It's time to rest")).toString();
}

void Settings::setMessage(const QString& message)
{
    qsettings.setValue("message", message);
}


bool Settings::useImage() const
{
    return qsettings.value("use_img", false).toBool();
}

void Settings::setUseImage(bool use)
{
    qsettings.setValue("use_img", use);
}


QString Settings::imagePath() const
{
    return qsettings.value("img_path", QString()).toString();
}

void Settings::setImagePath(const QString& path)
{
    qsettings.setValue("img_path", path);
}


bool Settings::lockScreen() const
{
    return qsettings.value("lock_screen", false).toBool();
}

void Settings::setLockScreen(bool lock)
{
    qsettings.setValue("lock_screen", lock);
}


QTime Settings::lockTime() const
{
    return qsettings.value("lock_time", QTime(0, 5)).toTime();
}

void Settings::setLockTime(QTime lockTime)
{
    qsettings.setValue("lock_time", lockTime);
}


QString Settings::language() const
{
    QString language;
    if (qsettings.contains("lang"))
        language = qsettings.value("lang").toString();
    else
    {
        QLocale currentLocale;
        language = currentLocale.name();
        language.truncate(language.indexOf('_'));
    }
    return language;
}

void Settings::setLanguage(const QString& language)
{
    qsettings.setValue("lang", language);
}


bool Settings::checkIdle() const
{
    return qsettings.value("check_idle", true).toBool();
}

void Settings::setCheckIdle(bool check)
{
    qsettings.setValue("check_idle", check);
}


QTime Settings::idleLimit() const
{
    bool ok;
    int seconds = qsettings.value("idle_limit", 60).toInt(&ok);
    if (!ok)
        seconds = 60;
    int hours, minutes;
    hours = seconds / 3600;
    seconds %= 3600;
    minutes = seconds / 60;
    seconds %= 60;
    QTime idleTime(hours, minutes, seconds);
    return idleTime;
}

void Settings::setIdleLimit(QTime idleLimit)
{
    int seconds = (idleLimit.hour() * 3600) + (idleLimit.minute() * 60) +
            idleLimit.second();
    qsettings.setValue("idle_limit", seconds);
}


bool Settings::useSound() const
{
    return qsettings.value("use_sound", false).toBool();
}

void Settings::setUseSound(bool use)
{
    qsettings.setValue("use_sound", use);
}


QString Settings::soundPath() const
{
    return qsettings.value("snd_path", QString()).toString();
}

void Settings::setSoundPath(const QString& path)
{
    qsettings.setValue("snd_path", path);
}
