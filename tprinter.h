#ifndef TPRINTER_H
#define TPRINTER_H

#include <QTextEdit>
#include <QKeyEvent>
#include <QByteArray>


class TPrinter : public QTextEdit
{
    Q_OBJECT
    //class QByteArray;
public:
    explicit TPrinter(QWidget *parent = 0);

signals:
    void keyReleaseSignal(QKeyEvent *e, QString keyText);

public slots:
    void keyReleaseEvent(QKeyEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e){}
    void mousePressEvent(QMouseEvent *e){}
    void mouseReleaseEvent(QMouseEvent *e){}
    void printMessageSlot(QByteArray aMessage);
    void deleteChar();

private slots:
    void textChangedSlot();


private:


};

#endif // TPRINTER_H
