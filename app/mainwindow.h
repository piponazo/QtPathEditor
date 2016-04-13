#pragma once

#include "pathreader.h"
#include "config_file.h"

#include <QMainWindow>
#include <QList>

namespace Ui {
class MainWindow;
}

class QTableWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /// Get paths from the registry and from the user configuration
    void getPaths();

private slots:
    /// Open the selected path in a new Windows Explorer
    void on_buttonBrowse_clicked();

    /// Add a new path to the list of paths
    void on_buttonAddPath_clicked();

    /// Remove an existing path from the list of paths
    void on_buttonDeletePath_clicked();

    void on_buttonSave_clicked();

    void itemPressed(QTableWidgetItem *item);

    void sectionMoved(int logicalIndex, int oldVisualIndex, int newVisualIndex);

    void copyRow();

    void pasteRow();


    void on_pushButton_clicked();

private:
    void addPathToTable(const QString &path, const bool enabled, const int row);
    void setupVisualAspect();
    void makeConnections();
    void saveRegistry();
    void saveConfigFile();
    void assignShortcuts();

    Ui::MainWindow *ui;

    CPathReader     m_reader;
    ConfigFile      m_config;
    QString         m_pathCopied;

    QList<QString>  m_pathsReg;     ///< Paths readed from registry

    // These are the variables read/write from/into the ConfigFile
    QList<QString>  m_paths;
    QList<int>      m_statuses;
    QList<int>      m_indexes;
};
