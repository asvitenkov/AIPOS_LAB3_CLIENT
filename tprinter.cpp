#include "tprinter.h"
#include <QDebug>
#include <QCursor>
#include <QTextCursor>
#include <myprocess.h>
#include <QFile>
#include <QTextCodec>
#include <QTextStream>

TPrinter::TPrinter(QWidget *parent) :
    QTextEdit(parent)
{


//    this->setTextColor(QColor(Qt::red));
//    QPalette pal;
//    pal.setColor(QPalette::Base,Qt::black);
//    this->setPalette(pal);




}

void TPrinter::textChangedSlot(){

}

void TPrinter::keyReleaseEvent(QKeyEvent *e){
    qDebug()<<"TPrinter::keyReleaseEvent";
    if(e->count()==Qt::Key_Shift) return;
    if(e->count()==Qt::Key_Backspace){
        QByteArray ar;
        ar+=8;
        emit keyReleaseSignal(e,QString(QByteArray(ar)));
        qDebug()<<e->key();

    }
    emit keyReleaseSignal(e,e->text());
    qDebug()<<e->text();
    qDebug()<<e->key();
}



void TPrinter::printMessageSlot(QByteArray aMessage){
    qDebug()<<"TPrinter::printMessageSlot";
    QString str;
    if(!aMessage.isEmpty())
        if(aMessage.at(0)==(char)8){
            deleteChar();
            return;
        }
    QTextCodec *codec = QTextCodec::codecForName("CP866");
    str = codec->toUnicode(aMessage);
    qDebug()<<str;
    this->textCursor().insertText(str);
    QTextCursor curs = this->textCursor();
    curs.movePosition(QTextCursor::End);
    this->setTextCursor(curs);
}






void TPrinter::deleteChar(){
    this->textCursor().deletePreviousChar();
}




