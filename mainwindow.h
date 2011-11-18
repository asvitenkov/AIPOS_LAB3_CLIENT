#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tsession.h"
#include "tprinter.h"

namespace Ui {
    class MainWindow;
}

/**
 * @brief
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui; /**< TODO */
    TPrinter *printer; /**< TODO */
    TSession *session; /**< TODO */

private slots:
    /**
     * @brief
     *
     */
    void createConnection();
    /**
     * @brief
     *
     */
    void connectionClose();
    /**
     * @brief
     *
     */
    void closeConnection();


};

#endif // MAINWINDOW_H
