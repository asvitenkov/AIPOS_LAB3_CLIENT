#ifndef TSESSION_H
#define TSESSION_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QKeyEvent>
#include "myprocess.h"

class TSession : public QTcpSocket
{
    Q_OBJECT

    enum TTcommand {IAC=255,DONT=254, DO=253, WONT=252, WILL=251, SB=250, SE=240};
    enum OptionsState {UNKNOWN=-1,OFF=0, ON=1, TRY_SERVER=2, TRY_CLIENT=3, CONST_ON=4, CONST_OFF=5 };


public:

    static const TTcommand TCommand;

    explicit TSession(QObject *parent = 0);

    void initialization();

signals:
    void printMessageSignal(QByteArray aMessage);
    void escSeqSignal(QByteArray aSeq);
public slots:
    void keyPressedOnKeyboard(QKeyEvent *e, QString keyText);
private slots:

    void readServer();
    void connectToServerSlot();


private:
    OptionsState optionsState[40];
    void parseMessage(QByteArray aMessage);
    void parseSuboptions(QByteArray aSuboptions);
    void parseOptions(QByteArray aOptions);
    bool echoMode;
    char lastChar;
    QByteArray outputData;
    QByteArray terminalType;
    QByteArray& clearData(QByteArray &aData);
    myProcess *prc;
    void commandProcessed(QString);


};

#endif // TSESSION_H
