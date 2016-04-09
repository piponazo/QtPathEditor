#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShortcut>
#include <QHeaderView>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>

#include <cstdlib>

/// \todo Right now the application has too much logic inside. I should try to move all that logic
/// to the library so I can test it properly.

namespace
{
    QString getStringWithoutEnv (const QString &str);

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
    removeToolBar(ui->mainToolBar);

    getPaths();

    ui->tableWidget->setRowCount(m_paths.size());

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
    ui->tableWidget->blockSignals(true);
    QTableWidgetItem *itemEn   = new QTableWidgetItem(); // enabled
    QTableWidgetItem *itemPath = new QTableWidgetItem(path);
    QTableWidgetItem *itemEx   = new QTableWidgetItem(); // exist
    itemEn->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    itemEx->setFlags(Qt::NoItemFlags | Qt::ItemIsEnabled);

    itemEn->setCheckState(enabled ? Qt::Checked : Qt::Unchecked);
    itemEn->setTextAlignment(Qt::AlignHCenter);
    itemEx->setIcon(QFile::exists(path) ? QIcon(":/icons/tick.png") : QIcon(":/icons/cross.png"));

    itemEn->setData(Qt::UserRole, row);
    itemPath->setData(Qt::UserRole, row);

    ui->tableWidget->setItem(row, COL_ENABLED,  itemEn);
    ui->tableWidget->setItem(row, COL_PATH,     itemPath);
    ui->tableWidget->setItem(row, COL_EXISTS,   itemEx);
    ui->tableWidget->blockSignals(false);
}

MainWindow::~MainWindow()
{
    /// \todo detect changes and ask if the user wants to save the new configuration
//    on_buttonSave_clicked();
    delete ui;
}

void MainWindow::getPaths()
{
    // Read from the config file (it can override the status of the previous paths)
    const QStringList paths = m_config.getPaths();

    if (!paths.empty())     // Previous configuration does not exist
    {
        const QList<int>  statuses = m_config.getStatus();

        for(int i = 0; i < paths.size(); ++i)
        {
            m_paths     << getStringWithoutEnv(paths[i]);
            m_statuses  << statuses[i];
            m_indexes   << i;
        }
    }
    else                    // Previous configuration does exist
    {
        StringListT  listFromRegistry;
        m_reader.Read(listFromRegistry);

        // Read from the registry (all must be enabled)
        for(int i = 0; i < static_cast<int>(listFromRegistry.size()); ++i)
        {
            m_paths     << getStringWithoutEnv(QString::fromWCharArray(listFromRegistry[i].c_str()));
            m_statuses  << 1;
        }
    }

}

void MainWindow::on_buttonSave_clicked()
{
    saveConfigFile();
//    saveRegistry();
}

void MainWindow::itemPressed(QTableWidgetItem *item)
{
    const int row = item->data(Qt::UserRole).toInt();
    if (item->column() == COL_ENABLED)
    {
        const bool checked = item->checkState() == Qt::Checked;
        m_statuses[row] = checked;
    }
    else if (item->column() == COL_PATH)
    {
        m_paths[row] = item->text();
        ui->tableWidget->item(row, COL_EXISTS)->setIcon(
            QFile::exists(item->text()) ? QIcon(":/icons/tick.png") : QIcon(":/icons/cross.png"));
    }
}

void MainWindow::sectionMoved(int logicalIndex, int oldVisualIndex, int newVisualIndex)
{
    m_paths.move(oldVisualIndex, newVisualIndex);
    m_statuses.move(oldVisualIndex, newVisualIndex);
    m_indexes.move(oldVisualIndex, newVisualIndex);

    ui->tableWidget->blockSignals(true);
    for (int i = 0; i < m_indexes.size(); i++)
    {
        const int idx = m_indexes[i];
        ui->tableWidget->item(idx, COL_ENABLED)->setData(Qt::UserRole, i);
        ui->tableWidget->item(idx, COL_PATH)->setData(Qt::UserRole, i);
    }
    ui->tableWidget->blockSignals(false);
}

void MainWindow::copyRow()
{
    const int row = ui->tableWidget->currentItem()->row();
    m_pathCopied = ui->tableWidget->item(row, COL_PATH)->text();
}

void MainWindow::pasteRow()
{
    if (m_pathCopied.isEmpty())
        return;

    const int row = ui->tableWidget->rowCount();

    m_paths     << m_pathCopied;
    m_statuses  << true;
    m_indexes   << row;

    ui->tableWidget->insertRow(row);
    addPathToTable(m_pathCopied, true, row);
}

void MainWindow::saveRegistry()
{
    StringListT listToRegistry;

    for(int i = 0; i < m_paths.size(); ++i)
    {
        if(m_statuses[i])
        {
            listToRegistry.push_back(m_paths[i].toStdWString());
        }
    }

    m_reader.Write(listToRegistry);
}

void MainWindow::saveConfigFile()
{
    m_config.setPaths(m_paths);
    m_config.setStatus(m_statuses);
}

void MainWindow::assignShortcuts()
{
    QShortcut *deleteRow = new QShortcut(QKeySequence("Del"), this);
    connect(deleteRow, SIGNAL(activated()), this, SLOT(on_buttonDeletePath_clicked()));

    QShortcut *copyRow = new QShortcut(QKeySequence("Ctrl+c"), this);
    connect(copyRow, SIGNAL(activated()), this, SLOT(copyRow()));

    QShortcut *pasteRow = new QShortcut(QKeySequence("Ctrl+v"), this);
    connect(pasteRow, SIGNAL(activated()), this, SLOT(pasteRow()));
}

void MainWindow::on_buttonBrowse_clicked()
{
    const int row = ui->tableWidget->currentItem()->row();
    const QString text = QDir::fromNativeSeparators(ui->tableWidget->item(row, COL_PATH)->text());

    if(QFile::exists(text))
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(text));
    }
    else
    {
        QMessageBox::critical(this, "Non existing path",
            "The path does not exist in your system. The system explorer cannot be opened with a "
            "non-existing path");
    }
}

void MainWindow::setupVisualAspect()
{
    ui->tableWidget->verticalHeader()->setSectionsMovable(true);
    ui->tableWidget->verticalHeader()->setDragEnabled(true);
    ui->tableWidget->verticalHeader()->setDragDropMode(QAbstractItemView::InternalMove);

    ui->tableWidget->setColumnWidth(COL_ENABLED,  60);
    ui->tableWidget->resizeColumnToContents(COL_PATH);
    ui->tableWidget->setColumnWidth(COL_EXISTS,   60);
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
        const int row = ui->tableWidget->rowCount();

        m_paths     << dir;
        m_statuses  << true;
        m_indexes   << row;

        ui->tableWidget->insertRow(row);
        addPathToTable(dir, true, row);
    }
}

void MainWindow::on_buttonDeletePath_clicked()
{
    const int row = ui->tableWidget->currentItem()->row();
    const int idx = ui->tableWidget->currentItem()->data(Qt::UserRole).toInt();
    m_paths.removeAt(idx);
    m_statuses.removeAt(idx);
    m_indexes.removeAt(idx);
    ui->tableWidget->removeRow(row);
}

namespace
{
    QString getStringWithoutEnv (const QString &str)
    {
        QRegExp rx("%(.*)%");
        if (rx.indexIn(str) != -1)
        {
            QString out = str;
            out.replace(rx, getenv(rx.cap(1).toUtf8().constData()));
            return out;
        }
        return str;
    }
}
