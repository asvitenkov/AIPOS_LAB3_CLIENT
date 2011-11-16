#include "tprinter.h"
#include <QDebug>
#include <QCursor>
#include <QTextCursor>
#include <myprocess.h>

TPrinter::TPrinter(QWidget *parent) :
    QTextEdit(parent)
{
    connect(this,SIGNAL(textChanged()),this,SLOT(textChangedSlot()));
    this->setTextColor(Qt::white);
    QPalette pal;
    pal.setColor(QPalette::Base,Qt::black);
    this->setPalette(pal);
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

void TPrinter::keyPressEvent(QKeyEvent *e){
    //qDebug()<<"TPrinter::keyPressEvent";
    //QTextEdit::keyPressEvent(e);
}


void TPrinter::mouseMoveEvent(QMouseEvent *e){
    QTextEdit::mouseMoveEvent(e);
}


void TPrinter::printMessageSlot(QByteArray aMessage){
    qDebug()<<"TPrinter::printMessageSlot";
    this->textCursor().insertText(QString::fromLocal8Bit(aMessage));
    QTextCursor curs = this->textCursor();
    curs.movePosition(QTextCursor::End);
    this->setTextCursor(curs);
    //parseEcsSeq(aMessage);
}






void TPrinter::deleteChar(){
    this->textCursor().deletePreviousChar();
}
