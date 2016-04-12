#include "editpathdialog.h"
#include "ui_editpathdialog.h"

#include <QCompleter>
#include <QDirModel>

EditPathDialog::EditPathDialog(const QString &path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPathDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(path);

    QCompleter *completer = new QCompleter(this);
    completer->setModel(new QDirModel(completer));
    ui->lineEdit->setCompleter(completer);
}

EditPathDialog::~EditPathDialog()
{
    delete ui;
}

QString EditPathDialog::getPath() const
{
    return ui->lineEdit->text();
}
