#ifndef TSESSION_H
#define TSESSION_H

#include <QTcpSocket>

class TSession : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TSession(QObject *parent = 0);

signals:

public slots:

};

#endif // TSESSION_H
