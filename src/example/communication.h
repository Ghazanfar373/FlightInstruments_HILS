#ifndef COMMUNICATION_H
#define COMMUNICATION_H


#include <QObject>
#include <QtCore>
#include <QByteArray>

class QUdpSocket;

class Communication : public QObject
{
    Q_OBJECT

public:
    explicit Communication(QObject *parent = nullptr);


    QByteArray datagram = 0;
    //QByteArray  temp_datagram;


    bool bind=false;
    bool connect_result=false;
    int num=0;

public slots:

    QByteArray recieve_packet();
    void connectToPort();
    void disconnectFromPort();

private:

    QUdpSocket *socket;

};

#endif // COMMUNICATION_H
