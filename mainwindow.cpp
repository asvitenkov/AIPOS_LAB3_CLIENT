#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    printer=new TPrinter(this);
    ui->verticalLayout->addWidget(printer);
    printer->show();
    session = NULL;
    connect(ui->connectButton,SIGNAL(clicked()),this,SLOT(createConnection()));
    connect(ui->disconnectButton,SIGNAL(clicked()),this,SLOT(closeConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::createConnection(){
    if(session!=NULL){
        session->close();
        session->abort();
        session->deleteLater();
    }
    printer->clear();
    session = new TSession(this);
    session->initialization();
    session->connectToHost(QHostAddress(ui->serverAdress->text()),ui->serverPort->value(),QIODevice::ReadWrite);
    connect(session,SIGNAL(printMessageSignal(QByteArray)),printer,SLOT(printMessageSlot(QByteArray)));
    connect(printer,SIGNAL(keyReleaseSignal(QKeyEvent*,QString)),session,SLOT(keyPressedOnKeyboard(QKeyEvent*,QString)));
    connect(session,SIGNAL(deleteChar()),printer,SLOT(deleteChar()));
    connect(session,SIGNAL(disconnected()),this,SLOT(connectionClose()));
}


void MainWindow::connectionClose(){
    qDebug()<<"con close";
    printer->append(QString("Connection close"));
}

void MainWindow::closeConnection(){
    if(session!=NULL){
        session->close();
        session->abort();
        session->deleteLater();
        session = NULL;
    }
    //printer->append(QString("Connection close"));
}
