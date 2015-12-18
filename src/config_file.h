#pragma once

#include "PathLib_export.h"
#include <QStringList>
#include <QBitArray>

class QSettings;

/// Will handle the paths stored in the application configuration file
class PATHLIB_EXPORT ConfigFile
{
public:
	ConfigFile(const QString &appName);
	~ConfigFile();

	QStringList getPaths() const;
	QBitArray   getStatus() const;
	QString     filePath() const;

	void setPaths(const QStringList &paths);
	void setStatus(const QBitArray &status);

private:
	QSettings* m_settings;
};
