#pragma once

#include "pathreader.h"
#include "config_file.h"

#include <QMainWindow>
#include <QMap>

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
	void on_buttonAddPath_clicked();

	void on_buttonSave_clicked();

	void itemPressed(QTableWidgetItem *item);

private:
	void saveRegistry();
	void saveConfigFile();

	Ui::MainWindow *ui;

	CPathReader     m_reader;
	ConfigFile      m_config;

	QMap<QString, bool> m_paths; ///< Path + status (enabled/disabled)
};
