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

QBitArray ConfigFile::getStatus() const
{
	return m_settings->value("status").toBitArray();
}

QString ConfigFile::filePath() const
{
	return m_settings->fileName();
}

void ConfigFile::setPaths(const QStringList &paths)
{
	m_settings->setValue("paths", paths);
}

void ConfigFile::setStatus(const QBitArray &status)
{
	m_settings->setValue("status", status);
}
