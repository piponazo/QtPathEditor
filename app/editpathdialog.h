#pragma once

#include <QDialog>

namespace Ui {
class EditPathDialog;
}

class EditPathDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditPathDialog(const QString &path, QWidget *parent = 0);
    ~EditPathDialog();

    QString getPath() const;

private:
    Ui::EditPathDialog *ui;
};
