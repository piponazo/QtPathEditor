#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShortcut>
#include <QHeaderView>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

namespace
{
    enum TableColum
    {
        COL_ENABLED,
        COL_PATH,
        COL_EXISTS
    };

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_reader(HKEY_CURRENT_USER)
    , m_config("QtPathEditor")
{
    ui->setupUi(this);
    getPaths();

    ui->tableWidget->setRowCount(m_paths.size());

    /// \todo use the indexes
    for(int i = 0; i < m_paths.size(); ++i)
    {
        addPathToTable(m_paths[i], m_statuses[i], i);
    }

    setupVisualAspect();
    makeConnections();
    assignShortcuts();
}

void MainWindow::addPathToTable(const QString &path, const bool enabled, const int row)
{
    QTableWidgetItem *itemEn   = new QTableWidgetItem(); // enabled
    QTableWidgetItem *itemPath = new QTableWidgetItem(path);
    QTableWidgetItem *itemEx   = new QTableWidgetItem(); // exist
    itemEn->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    itemEx->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);

    itemEn->setCheckState(enabled ? Qt::Checked : Qt::Unchecked);
    itemEn->setTextAlignment(Qt::AlignHCenter);
    itemEx->setIcon(QFile::exists(path) ? QIcon(":/icons/tick.png") : QIcon(":/icons/cross.png"));

    ui->tableWidget->setItem(row, COL_ENABLED,  itemEn);
    ui->tableWidget->setItem(row, COL_PATH,     itemPath);
    ui->tableWidget->setItem(row, COL_EXISTS,   itemEx);
}

MainWindow::~MainWindow()
{
    on_buttonSave_clicked();
    delete ui;
}

void MainWindow::getPaths()
{
    StringListT  listFromRegistry;
    m_reader.Read(listFromRegistry);

    // Read from the registry (all must be enabled)
    for(int i = 0; i < static_cast<int>(listFromRegistry.size()); ++i)
    {
        m_paths     << QString::fromWCharArray(listFromRegistry[i].c_str());
        m_statuses  << true;
        m_indexes   << i;
    }

    // Read from the config file (it can override the status of the previous paths)
    const QStringList paths    = m_config.getPaths();
    const QBitArray   statuses = m_config.getStatus();
    Q_ASSERT(paths.size() == statuses.size());

    for(int i = 0; i < paths.size(); ++i)
    {
        const int idx = m_paths.indexOf(paths[i]);

        if(idx != -1)  // Already in the list -> update the status
        {
            m_statuses[i] = statuses[i];
        }
        else
        {
            m_paths     << paths[i];
            m_statuses  << statuses[i];
            m_indexes   << (m_paths.size() - 1);
        }
    }
}

void MainWindow::on_buttonSave_clicked()
{
    saveConfigFile();
    saveRegistry();
}

void MainWindow::itemPressed(QTableWidgetItem *item)
{
    switch(item->column())
    {
        case COL_ENABLED :
        {
            const int idx = m_indexes[item->row()];
            const bool checked = item->checkState() == Qt::Checked;
            m_statuses[idx] = checked;
            qDebug() << "Path changed its status to: " << checked;
            break;
        }

        default:
        {
            qDebug() << "itemPressed. Action not implemented with colum: " << item->column();
        }
    }
}

void MainWindow::saveRegistry()
{
    StringListT listToRegistry;

    for(int i = 0; i < m_paths.size(); ++i)
    {
        const int idx = m_indexes[i];

        if(m_statuses[idx])
        {
            listToRegistry.push_back(m_paths[idx].toStdWString());
        }
    }

    m_reader.Write(listToRegistry);
}

void MainWindow::saveConfigFile()
{
    m_config.setPaths(m_paths);
    m_config.setOrder(m_indexes);

    QBitArray array(m_statuses.size());

    for(int i = 0; i < m_statuses.size(); ++i)
    {
        array.setBit(i, m_statuses[i]);
    }

    m_config.setStatus(array);
}

void MainWindow::assignShortcuts()
{
    QShortcut *shortcut = new QShortcut(QKeySequence("Del"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_buttonDeletePath_clicked()));
}

void MainWindow::on_buttonBrowse_clicked()
{
    const int idx = m_indexes[ui->tableWidget->currentRow()];

    if(m_statuses[idx])
    {
        QDesktopServices::openUrl(m_paths[idx]);
    }
    else
    {
        qDebug() << "Non existing path will be not opened";
    }
}

void MainWindow::sectionMoved(int logicalIndex, int oldVisualIndex, int newVisualIndex)
{
    qDebug() << "Section moved: " << logicalIndex << oldVisualIndex << newVisualIndex;
}


void MainWindow::setupVisualAspect()
{
    ui->tableWidget->verticalHeader()->setSectionsMovable(true);
    ui->tableWidget->verticalHeader()->setDragEnabled(true);
    ui->tableWidget->verticalHeader()->setDragDropMode(QAbstractItemView::InternalMove);

    ui->tableWidget->setColumnWidth(COL_ENABLED,  50);
    ui->tableWidget->resizeColumnToContents(COL_PATH);
    ui->tableWidget->setColumnWidth(COL_EXISTS,   50);
}

void MainWindow::makeConnections()
{
    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(itemPressed(QTableWidgetItem *)));
    connect(ui->tableWidget->verticalHeader(), SIGNAL(sectionMoved(int, int, int)),
            this, SLOT(sectionMoved(int, int, int)));
}

void MainWindow::on_buttonAddPath_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select path to add"),
                  QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty())
    {
        /// \todo check if the path exists?
        m_paths     << dir;
        m_statuses  << true;
        m_indexes   << (m_paths.size() - 1);
        const int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        addPathToTable(dir, true, row);
    }
}

void MainWindow::on_buttonDeletePath_clicked()
{
    const int dataIndex = m_indexes[ui->tableWidget->currentRow()];
    m_paths.erase(m_paths.begin() + m_indexes[dataIndex]);
    m_statuses.erase(m_statuses.begin() + m_indexes[dataIndex]);
    m_indexes.erase(m_indexes.begin() + dataIndex);
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());

}
