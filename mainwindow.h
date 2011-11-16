#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tsession.h"
#include "tprinter.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TPrinter *printer;
    TSession *session;

private slots:
    void createConnection();
    void connectionClose();
    void closeConnection();


};

#endif // MAINWINDOW_H
