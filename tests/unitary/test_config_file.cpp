#include "config_file.h"
#include "types.h"

#include <gtest/gtest.h>

#include <QStringList>
#include <QSettings>
#include <QDir>
#include <QDebug>

namespace
{
	const QStringList goodPaths { "C:\\Program Files (x86)\\CMake\\bin",
							  "C:\\Python27",
							  "C:\\Program Files (x86)\\Vim\\vim74",
							  "C:\\Qt\\4.8.7\\bin",
							  "E:\\Dev\\Libs\\external\\dllsDebug",
							  "E:\\Dev\\Libs\\external\\dllsRelease"};

	QBitArray pathsStatus (6, false);
}

class ConfigFileTestsReading : public ::testing::Test
{
protected:
	void SetUp()
	{
		QSettings settings(QSettings::IniFormat, QSettings::UserScope,
						   "CompanyName", "Test");

		settingsFile = settings.fileName();

		pathsStatus[1] = true;
		pathsStatus[3] = true;
		pathsStatus[5] = true;

		EXPECT_EQ(goodPaths.size(), pathsStatus.size());
		settings.setValue("paths", goodPaths);
		settings.setValue("status", pathsStatus);
	}

	void TearDown()
	{
		EXPECT_TRUE(QFile::remove(settingsFile));
	}
	QString settingsFile;
};

TEST_F(ConfigFileTestsReading, shouldObtainPathsList)
{
	ConfigFile config ("Test");
	QStringList paths = config.getPaths();
	EXPECT_EQ(6, paths.size());
	EXPECT_EQ(goodPaths, paths);
}

TEST_F(ConfigFileTestsReading, shouldObtainStatusList)
{
	ConfigFile config ("Test");
	QBitArray status = config.getStatus();
	EXPECT_EQ(pathsStatus, status);
}

class ConfigFileTestsWriting : public ::testing::Test
{
protected:
	void SetUp()
	{
		config = new ConfigFile ("Test");
		settingsFile = config->filePath();
	}

	void TearDown()
	{
		delete config;
		config = nullptr;
		EXPECT_TRUE(QFile::remove(settingsFile));
	}

	ConfigFile * config {nullptr};
	QString settingsFile;
};

TEST_F(ConfigFileTestsWriting, shouldWritePaths)
{
	config->setPaths(goodPaths);
	const auto obtainedPaths = config->getPaths();
	EXPECT_EQ(goodPaths, obtainedPaths);
}

TEST_F(ConfigFileTestsWriting, shouldWriteStatus)
{
	QBitArray statusConst (4, false);
	QBitArray statusRead (4, true);

	config->setStatus(statusConst);

	statusRead = config->getStatus();
	EXPECT_EQ(statusConst, statusRead);
}
