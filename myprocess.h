#ifndef MYPROCESS_H
#define MYPROCESS_H

#include <QObject>

#include <QProcess>

/**
 * @brief
 *
 */
class myProcess : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit myProcess(QObject *parent = 0);
    QProcess myProc; /**< TODO */

public slots:
        /**
         * @brief
         *
         */
        void startProcess();
        /**
         * @brief
         *
         */
        void showOutput();
        /**
         * @brief
         *
         * @param cmd
         */
        void runCommand(QByteArray cmd);
private:

        /**
         * @brief
         *
         * @param QString
         */
        QString decodeProcessResp(QString);
signals:
        /**
         * @brief
         *
         */
        void started();
        /**
         * @brief
         *
         * @param QString
         */
        void output(QString);


};

#endif // MYPROCESS_H
