#pragma once

#include "pathreader.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_buttonAddPath_clicked();

private:
	Ui::MainWindow *ui;
	CPathReader     m_reader;
	StringListT     m_pathList;
};
