#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TSession *session = new TSession(this);
    session->initialization();
    session->connectToHost(QHostAddress("127.0.0.1"),25,QIODevice::ReadWrite);
    QByteArray answer;
    answer+=255;
    answer+=252;
    answer+=31;
    answer+=255;
    answer+=254;
    answer+=31;
    session->write(answer);
    TPrinter *tmp=new TPrinter(this);
    ui->verticalLayout->addWidget(tmp);
    tmp->show();
    connect(session,SIGNAL(printMessageSignal(QByteArray)),tmp,SLOT(printMessageSlot(QByteArray)));
    connect(tmp,SIGNAL(keyReleaseSignal(QKeyEvent*,QString)),session,SLOT(keyPressedOnKeyboard(QKeyEvent*,QString)));
    connect(session,SIGNAL(escSeqSignal(QByteArray)),tmp,SLOT(parseEcsSeq(QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}



