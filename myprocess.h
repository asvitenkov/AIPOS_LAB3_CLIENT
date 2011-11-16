#ifndef MYPROCESS_H
#define MYPROCESS_H

#include <QObject>

#include <QProcess>

class myProcess : public QObject
{
    Q_OBJECT
public:
    explicit myProcess(QObject *parent = 0);
    QProcess myProc;

public slots:
        void startProcess();
        void showOutput();
        void runCommand(QByteArray cmd);
private:

        QString decodeProcessResp(QString);
signals:
        void started();
        void output(QString);


};

#endif // MYPROCESS_H
