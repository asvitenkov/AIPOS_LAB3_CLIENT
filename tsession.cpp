#include "tsession.h"
TSession::TSession(QObject *parent) :
    QTcpSocket(parent)
{
    qDebug()<<"run";

}

void TSession::initialization(){

    echoMode = false;
    lastChar='\0';
    outputData.clear();
    terminalType.clear();
    memset(optionsState,5,sizeof(optionsState));
    optionsState[31]=CONST_OFF;
    optionsState[24]=CONST_ON;
    optionsState[1]=CONST_ON;
    optionsState[3]=CONST_ON;
    connect(this,SIGNAL(readyRead()),this,SLOT(readServer()));
    connect(this,SIGNAL(connected()),this,SLOT(connectToServerSlot()));

}



void TSession::readServer(){
    QByteArray array=readAll();
    qDebug()<<QString::fromLocal8Bit(array);
    //clearData(array);
    parseMessage(array);

}

void TSession::connectToServerSlot(){
    qDebug()<<"TSession::connectToServerSlot()";

}


void TSession::parseMessage(QByteArray aMessage){
    qDebug()<<"TSession::parseMessage";
    if(aMessage.isEmpty()) return;
    QString str(aMessage);
    QByteArray answer;
    int pos=aMessage.indexOf((char)IAC);
    while(pos!=-1){
        // всё что до 255 записываем на принтер
        lastChar = aMessage[pos];
        outputData += aMessage.mid(0,pos);
        aMessage = aMessage.remove(0,pos+1);
        // удалили разбираем дальше
        // за 255 может быть подопция опция или символ 255
        if(aMessage[0]==(char)SB){
            // подопция
            // извлекаем
            QByteArray subOptions;
            int indexSE=aMessage.indexOf(SE);
            subOptions = aMessage.mid(0,indexSE+1);
            aMessage = aMessage.remove(0,indexSE+1);
        }
        else if (aMessage[0]!=(char)255){
            // опция
            QByteArray options;
            options+=aMessage[0];
            options+=aMessage[1];
            parseOptions(options);
            aMessage.remove(0,2);

        }
        else{
            // символ 255
            outputData+=255;
            aMessage.remove(0,1);
        }


        pos = aMessage.indexOf(IAC);
    }
    outputData+=aMessage;
    emit printMessageSignal(outputData);
    outputData.clear();
}



void TSession::parseSuboptions(QByteArray aSuboptions){
    qDebug()<<"TSession::parseSuboptions";
}

void TSession::parseOptions(QByteArray aOptions){
    qDebug()<<"TSession::parseOptions";
    // вообще то может на какие то опции нужно отвечать и подругому - хз
    QByteArray answer;
    int option=(int)aOptions[1];
    int param = (int)aOptions[0]+256;
    answer+=255;
    switch(param){
    case 251: // WILL
        // сервер хочет включить эту опцию
        // проверяем состояние этой опции
        if(optionsState[option]==CONST_ON){
            // опция может быть вкдючена
            answer+=WILL;
        }
        else if(optionsState[option]==CONST_OFF){
            // опцию нельзя включить
            answer+=WONT;
        }
        else{
            // меняем состояние опции
            optionsState[option]=ON;
            answer+=DO;
        }
        break;
    case 252: //WONT
        if(optionsState[option]==CONST_OFF){
            answer+=DONT;
        }
        else{
            optionsState[option]=OFF;
            answer+=DONT;
        }
        break;
    case 253: // DO
        if(optionsState[option]==CONST_OFF){
            answer+=WONT;
        }
        else if(optionsState[option]==CONST_ON){
            answer+=WILL;
        }
        else{
            optionsState[option]=ON;
            answer+=WILL;
        }
        break;
    case 254: // DONT
        if(optionsState[option]==CONST_OFF){
            answer+=WONT;
        }
        else{
            optionsState[option]=OFF;
            answer+=WONT;
        }
        break;
    }
    answer+=option;
    if(option==31){
        answer+=255;
        answer+=WONT;
        answer+=31;
        answer+=255;
        answer+=DONT;
        answer+=31;
    }
    write(answer);
}


void TSession::keyPressedOnKeyboard(QKeyEvent *e, QString keyText){
    qDebug()<<"TSession::keyPressedOnKeyboard";
    write(keyText.toLocal8Bit());
}



QByteArray& TSession::clearData(QByteArray &aData){
    qDebug()<<"TSession::clearData";
    QByteArray array; array+=27;array+=91;
    int pos = aData.indexOf(array);
    while(pos!=-1){

        int posEndH=aData.indexOf('H',pos+1);
        int posEndJ=aData.indexOf('J',pos+1);
        int posEndM=aData.indexOf('m',pos+1);
        if (posEndH==-1)posEndH=aData.size()+1;
        if (posEndJ==-1)posEndJ=aData.size()+1;
        if (posEndM==-1)posEndM=aData.size()+1;
        int posEnd = qMin(qMin(posEndH,posEndJ),posEndM);
        QByteArray escSeq;
        escSeq= aData.mid(pos+2,posEnd-pos-1);
        aData.remove(pos,posEnd-pos+1);


        emit escSeqSignal(escSeq);
        pos = aData.indexOf(array);
    }
    return aData;
}
