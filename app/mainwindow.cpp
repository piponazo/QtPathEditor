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
	m_pathList.push_back(L"C:\\PathInventado");
	int itemIdxInTable = 0;

	qDebug() << "paths detected: " << m_pathList.size();
	ui->tableWidget->setRowCount(static_cast<int>(m_pathList.size()));

	QIcon tick(":/icons/tick.png");
	QIcon cross(":/icons/cross.png");

	for(const auto & path : m_pathList)
	{
		QString pathQt = QString::fromWCharArray(path.c_str());

		QTableWidgetItem *itemEn   = new QTableWidgetItem(); // enabled
		QTableWidgetItem *itemPath = new QTableWidgetItem(pathQt);
		QTableWidgetItem *itemEx   = new QTableWidgetItem(); // exist

		itemEn->setCheckState(Qt::Checked);
		itemEn->setTextAlignment(Qt::AlignHCenter);
		itemEx->setIcon(QFile::exists(pathQt) ? tick : cross);

		ui->tableWidget->setItem(itemIdxInTable,   static_cast<int>(TableColum::Enabled), itemEn);
		ui->tableWidget->setItem(itemIdxInTable,   static_cast<int>(TableColum::Path), itemPath);
		ui->tableWidget->setItem(itemIdxInTable++, static_cast<int>(TableColum::Exists), itemEx);
	}

	ui->tableWidget->setColumnWidth(static_cast<int>(TableColum::Enabled),  50);
	ui->tableWidget->resizeColumnToContents(static_cast<int>(TableColum::Path));
	ui->tableWidget->setColumnWidth(static_cast<int>(TableColum::Exists),   50);
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
