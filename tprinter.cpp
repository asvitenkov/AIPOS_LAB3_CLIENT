#include "tprinter.h"
#include <QDebug>
#include <QCursor>
#include <QTextCursor>

TPrinter::TPrinter(QWidget *parent) :
    QTextEdit(parent)
{
    connect(this,SIGNAL(textChanged()),this,SLOT(textChangedSlot()));
    //this->setCursor(Qt::IBeamCursor);
    //this->setText("123123123l123k;12l3k12;l3k1;2l3k2;1l3k12;l3k12;l3k12;l3k12;3l12k3l;12k3;l12k3;l12k3;2l1k");
    //QTextCursor curs=this->cursorForPosition(QPoint(50,8));
    //this->setTextCursor(curs);
    w=80;
    h=10;
    x=1;
    y=1;
    display.resize(w*h+1);
    display.fill(' ');
    this->setReadOnly(true);
}

void TPrinter::textChangedSlot(){

    //qDebug()<<"TPrinter::textChangedSlot()";
}

void TPrinter::keyReleaseEvent(QKeyEvent *e){
    qDebug()<<"TPrinter::keyReleaseEvent";
    if(e->count()==Qt::Key_Shift) return;
    emit keyReleaseSignal(e,e->text());
    qDebug()<<e->text();
}

void TPrinter::keyPressEvent(QKeyEvent *e){
    //qDebug()<<"TPrinter::keyPressEvent";
    QTextEdit::keyPressEvent(e);
}


void TPrinter::mouseMoveEvent(QMouseEvent *e){
    QTextEdit::mouseMoveEvent(e);
}


void TPrinter::printMessageSlot(QByteArray aMessage){
    qDebug()<<"TPrinter::printMessageSlot";
    this->textCursor().insertText(QString::fromLocal8Bit(aMessage));
    //parseEcsSeq(aMessage);
}




void TPrinter::execCMD(QByteArray aCMD){
    qDebug()<<"TPrinter::execCMD";
    if(aCMD.isEmpty()) return;
    switch (aCMD[aCMD.size()-1]){
    case (int)'J':
        display.fill(' ');
        break;
    case (int)'m':
        break;
    case (int)'H':
        changePositions((int)aCMD[0],(int)aCMD[2]);
        break;
    }

}


void TPrinter::changePositions(int aX, int aY){
    qDebug()<<"TPrinter::changePositions";
    x=aX;
    y=aY;
}


void TPrinter::parseEcsSeq(QByteArray aData){
    qDebug()<<"TPrinter::parseEcsSeq";
    QByteArray array; array+=27;array+=91;
    int pos = aData.indexOf(array);
    while(pos!=-1){

        if(pos!=0){
            // последовательность не в начале, а где то в середине
            // нужно вырезать предыдущий текст и отправить на печать
            QByteArray copy = aData.mid(0,pos);
            aData.remove(0,pos);
            printMessage(copy);
        }


        int posEndH=aData.indexOf('H',pos+1);
        int posEndJ=aData.indexOf('J',pos+1);
        int posEndM=aData.indexOf('m',pos+1);
        if (posEndH==-1)posEndH=aData.size()+1;
        if (posEndJ==-1)posEndJ=aData.size()+1;
        if (posEndM==-1)posEndM=aData.size()+1;
        int posEnd = qMin(qMin(posEndH,posEndJ),posEndM);
        QByteArray escSeq;
        escSeq= aData.mid(pos+2,posEnd-pos-1);
        aData = aData.remove(pos,posEnd-pos+1);
        execCMD(escSeq);
        pos = aData.indexOf(array);
    }
    printMessage(aData);
    printDisplay();

}

void TPrinter::printMessage(QByteArray aMessage){
    qDebug()<<"TPrinter::printMessage";
    int pos=(y-1)*w+x-1;
    int i;
    for(i=0;i<aMessage.size();i++)
        display[pos+i]=aMessage.at(i);
    changePositions((pos+i+1)%w,(int)((pos+i+1)/w)+1);
}


void TPrinter::printDisplay(){
    qDebug()<<"TPrinter::printDisplay()";
    this->clear();
    int i=0;
    for(i;i<display.size();i++){
        //qDebug()<<QString(*pDisplay[i]);
        this->textCursor().insertText(QString(QString(display.at(i)).toLocal8Bit()));
        if((i % w)==0){
            this->append("");
        }
    }
    qDebug()<<this->textCursor().position();
    QTextCursor curs = this->textCursor();
    curs.movePosition(QTextCursor::PreviousCharacter,QTextCursor::MoveAnchor,this->textCursor().position()-(y-1)*(w)-x - 1);
    this->setTextCursor(curs);
    qDebug()<<this->textCursor().position();
}
