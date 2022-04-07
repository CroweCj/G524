#include "config_setting.h"
#include <QCoreApplication>
#include <QTextCodec>
ExinovaSettings::ExinovaSettings()
{
}

ExinovaSettings::~ExinovaSettings()
{
}

QSettings* ExinovaSettings::getSettings()
{
    static QSettings set(QString("%1/Config/config.ini").arg(QCoreApplication::applicationDirPath()), QSettings::IniFormat);
    return &set;
}

void ExinovaSettings::clear()
{
    getSettings()->clear();
}

void ExinovaSettings::sync()
{
    getSettings()->sync();
}

QSettings::Status ExinovaSettings::status()
{
    return getSettings()->status();
}

void ExinovaSettings::beginGroup(const QString& prefix)
{
    getSettings()->beginGroup(prefix);
}

void ExinovaSettings::endGroup()
{
    getSettings()->endGroup();
}

QString ExinovaSettings::group()
{
    return getSettings()->group();
}

int ExinovaSettings::beginReadArray(const QString& prefix)
{
    return getSettings()->beginReadArray(prefix);
}

void ExinovaSettings::beginWriteArray(const QString& prefix, int size)
{
    getSettings()->beginWriteArray(prefix, size);
}

void ExinovaSettings::endArray()
{
    getSettings()->endArray();
}

void ExinovaSettings::setArrayIndex(int i)
{
    return getSettings()->setArrayIndex(i);
}

QStringList ExinovaSettings::allKeys()
{
    return getSettings()->allKeys();
}

QStringList ExinovaSettings::childKeys()
{
    return getSettings()->childKeys();
}

QStringList ExinovaSettings::childGroups()
{
    return getSettings()->childGroups();
}

bool ExinovaSettings::isWritable()
{
    return getSettings()->isWritable();
}

void ExinovaSettings::setValue(const QString& key, const QVariant& value)
{
    return  getSettings()->setValue(key, value);
}

QVariant ExinovaSettings::value(const QString& key, const QVariant& defaultValue)
{
    return getSettings()->value(key, defaultValue);
}

void ExinovaSettings::remove(const QString& key)
{
    getSettings()->remove(key);
}

bool ExinovaSettings::contains(const QString& key)
{
    return getSettings()->contains(key);
}

void ExinovaSettings::setFallbacksEnabled(bool b)
{
    getSettings()->setFallbacksEnabled(b);
}

bool ExinovaSettings::fallbacksEnabled()
{
    return getSettings()->fallbacksEnabled();
}

QString ExinovaSettings::fileName()
{
    return getSettings()->fileName();
}

QSettings::Format ExinovaSettings::format()
{
    return getSettings()->format();
}

QSettings::Scope ExinovaSettings::scope()
{
    return getSettings()->scope();
}

QString ExinovaSettings::organizationName()
{
    return getSettings()->organizationName();
}

QString ExinovaSettings::applicationName()
{
    return getSettings()->applicationName();
}
