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
    memset(optionsState,CONST_OFF,sizeof(optionsState));
    for(int i=0;i<40;i++) optionsState[i] = CONST_OFF;
    optionsState[1]=OFF;
    optionsState[3]=CONST_ON;
    connect(this,SIGNAL(readyRead()),this,SLOT(readServer()));
    connect(this,SIGNAL(connected()),this,SLOT(connectToServerSlot()));
}



void TSession::readServer(){
    QByteArray array=readAll();
    qDebug()<<QString::fromLocal8Bit(array);
    parseMessage(array);

}

//void TSession::connectToServerSlot(){
//    qDebug()<<"TSession::connectToServerSlot()";

//}


void TSession::parseMessage(QByteArray aMessage){
    qDebug()<<"TSession::parseMessage";
    if(aMessage.isEmpty()) return;
    QString str(aMessage);
    QByteArray answer;
    QByteArray backspace;
    backspace+=27; backspace+=91; backspace+=49; backspace+=68; backspace+=27; backspace+=91; backspace+=80;
    if(aMessage.indexOf(backspace)!=-1){
        aMessage.replace(backspace,QByteArray());
        emit deleteChar();
    }
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
    write(answer);
}


void TSession::keyPressedOnKeyboard(QKeyEvent *e, QString keyText){
    qDebug()<<"TSession::keyPressedOnKeyboard";
    if(optionsState[1]==OFF) emit printMessageSignal(keyText.toLocal8Bit());
    write(keyText.toLocal8Bit());
}



//void TSession::commandProcessed(QString str){
//    qDebug()<<str;
//}
