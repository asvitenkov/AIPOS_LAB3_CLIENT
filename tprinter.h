#ifndef TPRINTER_H
#define TPRINTER_H

#include <QTextEdit>
#include <QKeyEvent>
#include <QByteArray>


/**
 * @brief
 *
 */
class TPrinter : public QTextEdit
{
    Q_OBJECT
    //class QByteArray;
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit TPrinter(QWidget *parent = 0);

signals:
    /**
     * @brief
     *
     * @param e
     * @param keyText
     */
    void keyReleaseSignal(QKeyEvent *e, QString keyText);

public slots:
    /**
     * @brief
     *
     * @param e
     */
    void keyReleaseEvent(QKeyEvent *e);
    /**
     * @brief
     *
     * @param e
     */
    void keyPressEvent(QKeyEvent *e){}
    /**
     * @brief
     *
     * @param e
     */

    void mouseReleaseEvent(QMouseEvent *e){}
    /**
     * @brief
     *
     * @param aMessage
     */
    void printMessageSlot(QByteArray aMessage);
    /**
     * @brief
     *
     */
    void deleteChar();

private slots:
    /**
     * @brief
     *
     */
    void textChangedSlot();


private:


};

#endif // TPRINTER_H
