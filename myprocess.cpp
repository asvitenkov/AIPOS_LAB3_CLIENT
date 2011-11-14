#include "myprocess.h"
#include <QDebug>
#include <QTextCodec>

/**
* ����������� ��������
* @param parent ������������ ������
*/
myProcess::myProcess(QObject *parent) :
    QObject(parent)
{
    connect(&myProc,SIGNAL(readyReadStandardOutput()),this,SLOT(showOutput()));
    connect(&myProc,SIGNAL(readyReadStandardError()),this,SLOT(showOutput()));
}

/**
* ��������� ������� (cmd.exe)
* � ������ ��������� ������� �������� ������ � ������ ��������
*/
void myProcess::startProcess()
{
        QString prog="C:\\Windows\\System32\\cmd.exe";
        myProc.start(prog);
        if(myProc.waitForStarted())
                emit started();
        else
                qDebug()<<QString("Can't start program <b>%1</b>");
}

/**
* �������� � ������� ��������� ��� ���������
* @param com �������, ������� ���������� ���������
*/
void myProcess::runCommand(QString com)
{
        QString s=com+"\n";
        if(myProc.write(s.toAscii())!=-1) qDebug()<<"OK";
}

/**
* ������ ����� �������� � �������� ������ � ��������� ������
*/
void myProcess::showOutput()
{
    QString retStr;
    QTextCodec::setCodecForTr(QTextCodec::codecForName("CP866"));
    retStr = tr(myProc.readAllStandardOutput());
    emit output(retStr);
}


QString myProcess::decodeProcessResp(QString str){



    return str;

}
