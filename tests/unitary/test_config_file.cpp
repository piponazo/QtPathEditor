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

    const QList<QVariant> goodStatuses {0, 1, 0, 1, 0, 1};
    const QList<QVariant> goodOrder {0, 2, 1, 4, 5, 3};
}

/// This fixture writes values in a config file using directly QSettings. Then we create an
/// instance of ConfigFile for reading those values.
class ConfigFileTestsReading : public ::testing::Test
{
protected:
    static void SetUpTestCase()
    {
        QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                           "CompanyName", "Test");

        settingsFile = settings.fileName(); // copy absolute file path

        EXPECT_EQ(goodPaths.size(), goodStatuses.size());
        EXPECT_EQ(goodPaths.size(), goodOrder.size());

        settings.setValue("paths",  goodPaths);
        settings.setValue("status", goodStatuses);
        settings.setValue("order",  goodOrder);
    }

    static void TearDownTestCase()
    {
        EXPECT_TRUE(QFile::remove(settingsFile));
    }

    static QString settingsFile;
    static ConfigFile config;
};

QString ConfigFileTestsReading::settingsFile;
ConfigFile ConfigFileTestsReading::config ("Test");

TEST_F(ConfigFileTestsReading, shouldObtainPathsList)
{
    QStringList paths = config.getPaths();
    EXPECT_EQ(6, paths.size());
    EXPECT_EQ(goodPaths, paths);
}

TEST_F(ConfigFileTestsReading, shouldObtainStatusList)
{
    QList<int> status = config.getStatus();
    EXPECT_EQ(6, status.size());
    for (int i = 0; i < status.size(); ++i)
    {
       EXPECT_EQ(goodStatuses[i].toInt(), status[i]);
    }
}

TEST_F(ConfigFileTestsReading, shouldObtainOrderList)
{
    QList<int> order = config.getOrder();
    EXPECT_EQ(6, order.size());
    for (int i = 0; i < order.size(); ++i)
    {
       EXPECT_EQ(order[i], goodOrder[i].toInt());
    }
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
    QList<int> statusConst ({0, 0, 0, 0, 0, 0});
    QList<int> statusRead ({1, 1, 1, 1, 1, 1});

    config->setStatus(statusConst);

    statusRead = config->getStatus();
    EXPECT_EQ(statusConst, statusRead);
}
