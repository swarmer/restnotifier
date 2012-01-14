#include <QLocale>

#include "settings.h"


QTime Settings::interval() const
{
    QTime interval = qsettings.value("interval", QTime(1, 0)).toTime();
    if (interval.isNull())
        interval = QTime(1, 0);
    return interval;
}

void Settings::setInterval(QTime interval)
{
    qsettings.setValue("interval", interval);
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
    return qsettings.value("lock_time", QTime(0, 1)).toTime();
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
    QTime idleLimit = qsettings.value("idle_limit", QTime(0, 1)).toTime();
    if (idleLimit.isNull())
        idleLimit = QTime(0, 1);
    return idleLimit;
}

void Settings::setIdleLimit(QTime idleLimit)
{
    qsettings.setValue("idle_limit", idleLimit);
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
