#ifndef TPRINTER_H
#define TPRINTER_H

#include <QTextEdit>
#include <QKeyEvent>


class TPrinter : public QTextEdit
{
    Q_OBJECT
public:
    explicit TPrinter(QWidget *parent = 0);

signals:

public slots:
//    void append(const QString &text);
//    void paste();
//    void setPlainText(const QString &text);
//    void setText(const QString &text);
    void keyReleaseEvent(QKeyEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e){}
    void mousePressEvent(QMouseEvent *e){}
    void mouseReleaseEvent(QMouseEvent *e){}
private slots:
    void textChangedSlot();

};

#endif // TPRINTER_H
