#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

enum class TableColum : int
{
	Enabled,
	Path,
	Exists
};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_reader(HKEY_CURRENT_USER)
{
	ui->setupUi(this);

	m_reader.Read(m_pathList);
	int itemIdx = 0;

	qDebug() << "paths detected: " << m_pathList.size();
	ui->tableWidget->setRowCount(static_cast<int>(m_pathList.size()));

	for(const auto & path : m_pathList)
	{
		QTableWidgetItem *newItem = new QTableWidgetItem(QString::fromWCharArray(path.c_str()));
		ui->tableWidget->setItem(itemIdx++, static_cast<int>(TableColum::Path), newItem);
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_buttonAddPath_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Select path to add"),
		QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if (!dir.isEmpty())
	{
		int rowIndex = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(rowIndex);
		QTableWidgetItem *newItem = new QTableWidgetItem(dir);
		ui->tableWidget->setItem(rowIndex, static_cast<int>(TableColum::Path), newItem);
	}
}
