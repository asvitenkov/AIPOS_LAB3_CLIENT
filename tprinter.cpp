#include "tprinter.h"
#include <QDebug>
#include <QCursor>
#include <QTextCursor>

TPrinter::TPrinter(QWidget *parent) :
    QTextEdit(parent)
{
    //ui->printer->setUndoRedoEnabled(false);
//    ui->printer->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
//    ui->printer->setLineWrapMode(QTextEdit::FixedColumnWidth);
//    ui->printer->setLineWrapColumnOrWidth(40);
    //ui->printer->setAcceptRichText(false);
    //disconnect(this,SIGNAL(textChanged()),0,0);

    connect(this,SIGNAL(textChanged()),this,SLOT(textChangedSlot()));

    //disconnect(this,SIGNAL(textChanged()))
    //this->setText("1231235");
    //this->setReadOnly(true);
    this->setCursor(Qt::IBeamCursor);

//    this->keyPressEvent();
//    this->keyReleaseEvent();

}

void TPrinter::textChangedSlot(){
    //disconnect(this,SIGNAL(textChanged()),this,SLOT(textChangedSlot()));
    qDebug()<<"TPrinter::textChangedSlot()";
//    QTextCursor curs = this->textCursor();
//    curs.deletePreviousChar();
}

//void TPrinter::append(const QString &text){
//    qDebug()<<"TPrinter::append(const QString &text)";
//}

//void TPrinter::paste(){
//    qDebug()<<"TPrinter::paste()";
//}

//void TPrinter::setPlainText(const QString &text){
//    qDebug()<<"TPrinter::setPlainText";
//}

//void TPrinter::setText(const QString &text){
//    qDebug()<<"TPrinter::setText";
//}

void TPrinter::keyReleaseEvent(QKeyEvent *e){
    qDebug()<<"TPrinter::keyReleaseEvent";
    if(e->key()==Qt::Key_Backspace)
        this->textCursor().deletePreviousChar();
    else
        this->textCursor().insertText(e->text());
}

void TPrinter::keyPressEvent(QKeyEvent *e){
    qDebug()<<"TPrinter::keyPressEvent";
    qDebug()<<e->text();
}


void TPrinter::mouseMoveEvent(QMouseEvent *e){

}
