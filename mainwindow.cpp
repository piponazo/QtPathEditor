#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

enum class TableColum : int
{
    Enabled,
    Path,
    Exists
};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_reader(HKEY_CURRENT_USER, L"Environment", L"Path")
{
    ui->setupUi(this);

    m_reader.Read(m_pathList);
    int itemIdx = 0;

    qDebug() << "paths detected: " << m_pathList.size();
    ui->tableWidget->setRowCount(5);

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
