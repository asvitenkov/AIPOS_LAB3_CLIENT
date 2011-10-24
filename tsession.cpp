#include "tsession.h"

TSession::TSession(QObject *parent) :
    QTcpSocket(parent)
{
    qDebug()<<"run";
    connect(this,SIGNAL(readyRead()),this,SLOT(readServer()));
    connect(this,SIGNAL(connected()),this,SLOT(connectToServerSlot()));
    //connectToHost(QHostAddress("94.100.177.1"),25,QIODevice::ReadWrite);
    connectToHost(QHostAddress("127.0.0.1"),23,QIODevice::ReadWrite);
    lastChar='\0';
    outputData.clear();
}



void TSession::readServer(){
    QByteArray array=readAll();
    qDebug()<<(QString::fromLocal8Bit(array)).replace("\r\n","");
    parseMessage(array);

}

void TSession::connectToServerSlot(){
    qDebug()<<"TSession::connectToServerSlot()";

}


void TSession::parseMessage(QByteArray aMessage){
    if(aMessage.isEmpty()) return;
    int pos=aMessage.indexOf(IAC);
    while(pos!=-1){
        lastChar = aMessage[pos];
        //aMessage = aMessage.remove(pos,1);
        outputData += aMessage.mid(0,pos);
        aMessage = aMessage.remove(0,pos+1);



        pos = aMessage.indexOf(IAC);
    }
}
