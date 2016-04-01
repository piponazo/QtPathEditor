#include "config_file.h"

#include <QSettings>

ConfigFile::ConfigFile(const QString &appName) :
    m_settings(new QSettings(QSettings::IniFormat, QSettings::UserScope, "CompanyName", appName))
{
}

ConfigFile::~ConfigFile()
{
    delete m_settings;
}

QStringList ConfigFile::getPaths() const
{
    return m_settings->value("paths", QStringList()).toStringList();
}

QList<int> ConfigFile::getStatus() const
{
    QList<QVariant> tmp = m_settings->value("status").toList();
    QList<int> list;
    bool ok;
    foreach (QVariant idx, tmp)
    {
        list.push_back(idx.toInt(&ok));
        if (!ok)
        {
            throw std::runtime_error("Wrong 'status' list of integers in the config file");
        }
    }
    return list;
}

QList<int> ConfigFile::getOrder() const
{
    QList<QVariant> tmp = m_settings->value("order").toList();
    QList<int> list;
    bool ok;
    foreach (QVariant idx, tmp)
    {
        list.push_back(idx.toInt(&ok));
        if (!ok)
        {
            throw std::runtime_error("Wrong 'order' list of integers in the config file");
        }
    }
    return list;
}

QString ConfigFile::filePath() const
{
    return m_settings->fileName();
}

void ConfigFile::setPaths(const QStringList &paths)
{
    m_settings->setValue("paths", paths);
}

void ConfigFile::setStatus(const QList<int> &status)
{
    QList<QVariant> statusVariant;
    foreach (int idx, status)
    {
        statusVariant.push_back(idx);
    }
    m_settings->setValue("status", statusVariant);
}

void ConfigFile::setOrder(const QList<int> &order)
{
    QList<QVariant> orderVariant;
    foreach (int idx, order)
    {
        orderVariant.push_back(idx);
    }
    m_settings->setValue("order", orderVariant);
}
