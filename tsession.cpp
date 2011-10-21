#include "tsession.h"

TSession::TSession(QObject *parent) :
    QTcpSocket(parent)
{
}
