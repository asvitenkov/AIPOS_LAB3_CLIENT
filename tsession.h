#ifndef TSESSION_H
#define TSESSION_H

#include <QTcpSocket>
#include <QHostAddress>

class TSession : public QTcpSocket
{
    Q_OBJECT

    //static const char IAC = 255;
    //static const char IAC = 255;

    enum TTcommand {IAC=255,DONT=254, DO=253, WONT=252, WILL=251, SB=250, SE=240};


public:

    static const TTcommand Tcommand;

    explicit TSession(QObject *parent = 0);

signals:

public slots:

private slots:

    void readServer();
    void connectToServerSlot();


private:
    void parseMessage(QByteArray aMessage);
    bool echoMode;
    char lastChar;
    QByteArray outputData;


};

#endif // TSESSION_H
