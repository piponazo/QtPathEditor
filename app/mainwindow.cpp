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
  , m_config("QtPathEditor")
{
	ui->setupUi(this);
	getPaths();

	ui->tableWidget->setRowCount(m_paths.size());

	const QIcon tick(":/icons/tick.png");
	const QIcon cross(":/icons/cross.png");
	int itemIdxInTable = 0;

	for(auto it = m_paths.begin(); it != m_paths.end(); ++it)
	{
		QString pathQt = it.key();

		QTableWidgetItem *itemEn   = new QTableWidgetItem(); // enabled
		QTableWidgetItem *itemPath = new QTableWidgetItem(pathQt);
		QTableWidgetItem *itemEx   = new QTableWidgetItem(); // exist

		itemEn->setCheckState(it.value() ? Qt::Checked : Qt::Unchecked);
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
	on_buttonSave_clicked();
	delete ui;
}

void MainWindow::getPaths()
{
	StringListT     m_pathList;
	m_reader.Read(m_pathList);

	// Read from the registry (all must be enabled)
	for(const auto & path : m_pathList)
	{
		QString pathQt = QString::fromWCharArray(path.c_str());
		m_paths[pathQt]= true;
	}

	// Read from the config file (it can override the status of the previous paths)
	const QStringList paths    = m_config.getPaths();
	const QBitArray   statuses = m_config.getStatus();
	Q_ASSERT (paths.size() == statuses.size());

	for (int i = 0; i < paths.size(); ++i)
	{
		m_paths[paths[i]] = statuses[i];
	}
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

void MainWindow::on_buttonSave_clicked()
{
	saveRegistry();
	saveConfigFile();
}

void MainWindow::saveRegistry()
{

}

void MainWindow::saveConfigFile()
{
	m_config.setPaths(m_paths.keys());

	const auto statuses = m_paths.values();
	QBitArray array (statuses.size());
	for (int i = 0; i < statuses.size(); ++i)
	{
		array.setBit(i, statuses[i]);
	}

	m_config.setStatus(array);
}
