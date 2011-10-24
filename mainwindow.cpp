#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    new TSession(this);
    TPrinter *tmp=new TPrinter(this);
    ui->verticalLayout->addWidget(tmp);
    tmp->show();
    //ui->printer->setUndoRedoEnabled(false);
//    ui->printer->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
//    ui->printer->setLineWrapMode(QTextEdit::FixedColumnWidth);
//    ui->printer->setLineWrapColumnOrWidth(40);
    //ui->printer->setAcceptRichText(false);



}

MainWindow::~MainWindow()
{
    delete ui;
}



