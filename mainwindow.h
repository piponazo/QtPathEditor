#pragma once

#include <QMainWindow>
#include "pathreader.h"

namespace Ui {
class MainWindow;
}
class CPathReader;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CPathReader     m_reader;
    StringListT     m_pathList;
};
