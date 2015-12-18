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

	QBitArray goodStatuses (6, false);
}

class ConfigFileTestsReading : public ::testing::Test
{
protected:
	void SetUp()
	{
		QSettings settings(QSettings::IniFormat, QSettings::UserScope,
						   "CompanyName", "Test");

		settingsFile = settings.fileName();

		goodStatuses[0] = false;
		goodStatuses[1] = true;
		goodStatuses[2] = false;
		goodStatuses[3] = true;
		goodStatuses[4] = false;
		goodStatuses[5] = true;

		EXPECT_EQ(goodPaths.size(), goodStatuses.size());
		settings.setValue("paths", goodPaths);
		settings.setValue("status", goodStatuses);
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
	EXPECT_EQ(6, status.size());
	EXPECT_EQ(goodStatuses, status);
}

TEST_F(ConfigFileTestsReading, shouldNotHaveTheSameStatuses)
{
	ConfigFile config ("Test");
	QBitArray status = config.getStatus();
	QBitArray badStatuses (6, false);

	EXPECT_EQ(6, status.size());
	EXPECT_NE(badStatuses, status);
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
