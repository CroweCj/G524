#ifndef EXINOVA_G524_CONFIG_SETTING_H__
#define EXINOVA_G524_CONFIG_SETTING__H__
/*****************************************************************************
* @FileName:config_setting.h
* @Author: chujiajun
* @CreatTime: 2022/4/7
* @Descriptions:全局配置文件
* @Version: ver 1.0
*****************************************************************************/
#include <QSettings>

class ExinovaSettings
{
public:
    ~ExinovaSettings();

    static void clear();

    static void sync();

    static QSettings::Status status();

    static void beginGroup(const QString& prefix);

    static void endGroup();

    static QString group();

    static int beginReadArray(const QString& prefix);

    static void beginWriteArray(const QString& prefix, int size = -1);

    static void endArray();

    static void setArrayIndex(int i);

    static QStringList allKeys();

    static QStringList childKeys();

    static QStringList childGroups();

    static bool isWritable();

    static void setValue(const QString& key, const QVariant& value);

    static QVariant value(const QString& key, const QVariant& defaultValue = QVariant());

    static void remove(const QString& key);

    static bool contains(const QString& key);

    static void setFallbacksEnabled(bool b);

    static bool fallbacksEnabled();

    static QString fileName();

    static QSettings::Format format();

    static QSettings::Scope scope();

    static QString organizationName();

    static QString applicationName();
private:
    ExinovaSettings();

    static QSettings* getSettings();
};
#endif // EXINOVA_G524_CONFIG_SETTING__H__
