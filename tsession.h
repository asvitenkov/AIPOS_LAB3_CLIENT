#ifndef TSESSION_H
#define TSESSION_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QKeyEvent>
#include "myprocess.h"

/**
 * @brief
 *
 */
class TSession : public QTcpSocket
{
    Q_OBJECT

    /**
     * @brief
     *
     */
    enum TTcommand {IAC=255,DONT=254, DO=253, WONT=252, WILL=251, SB=250, SE=240};
    /**
     * @brief
     *
     */
    enum OptionsState {UNKNOWN=-1,OFF=0, ON=1, TRY_SERVER=2, TRY_CLIENT=3, CONST_ON=4, CONST_OFF=5 };


public:

    static const TTcommand TCommand; /**< TODO */

    /**
     * @brief
     *
     * @param parent
     */
    explicit TSession(QObject *parent = 0);

    /**
     * @brief
     *
     */
    void initialization();

signals:
    /**
     * @brief
     *
     * @param aMessage
     */
    void printMessageSignal(QByteArray aMessage);
    /**
     * @brief
     *
     * @param aSeq
     */
    void escSeqSignal(QByteArray aSeq);
    /**
     * @brief
     *
     */
    void deleteChar();
public slots:
    /**
     * @brief
     *
     * @param e
     * @param keyText
     */
    void keyPressedOnKeyboard(QKeyEvent *e, QString keyText);
private slots:

    /**
     * @brief
     *
     */
    void readServer();
//    /**
//     * @brief
//     *
//     */
//    void connectToServerSlot();
//    /**
//     * @brief
//     *
//     * @param QString
//     */
//    void commandProcessed(QString);


private:
    OptionsState optionsState[40]; /**< TODO */
    /**
     * @brief
     *
     * @param aMessage
     */
    void parseMessage(QByteArray aMessage);
    /**
     * @brief
     *
     * @param aSuboptions
     */
    void parseSuboptions(QByteArray aSuboptions);
    /**
     * @brief
     *
     * @param aOptions
     */
    void parseOptions(QByteArray aOptions);
    bool echoMode; /**< TODO */
    char lastChar; /**< TODO */
    QByteArray outputData; /**< TODO */
    QByteArray terminalType; /**< TODO */
    myProcess *prc; /**< TODO */



};

#endif // TSESSION_H
