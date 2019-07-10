#include "communication.h"
#include <QMessageBox>
#include <QDebug>
#include <QUdpSocket>
#include <QtCore>
#include <QTime>
#include <QStringList>
#include <QtEndian>
#include <my_parameters.h>

Communication::Communication(QObject *parent) : QObject(parent)
{

    socket = new QUdpSocket(this);
}

void Communication::connectToPort()
{

    QString string("192.168.1.1");
    QHostAddress address(QHostAddress::AnyIPv4);
    address.setAddress(string);

    bind = socket->bind(52150);
    connect_result= connect(socket, SIGNAL(readyRead()),
                this, SLOT(recieve_packet()),Qt::QueuedConnection);
    qDebug()<< connect_result;
    //qDebug()<<portnumber;
    qDebug()<< bind;

}

QByteArray Communication::recieve_packet()

{
       // while(socket->hasPendingDatagrams()){
            //datagram.clear();
           datagram.resize(29);
           QHostAddress addr = QHostAddress::LocalHost;
           uint16_t port_num = 52150;
           socket->readDatagram(datagram.data(), 29, &addr , &port_num);

        //}
        return datagram;
}


void Communication::disconnectFromPort()
{
    socket->close();
}

