#include "tcpcontroller.h"






/*
 * Цикл работы с Tcp-сервером
 * 1) создать объект
 * 2) создать слот-обработчик данных с сервера
 * 3) привязать слот для обработки поступающих данных
 * QObject::connect(&имя_сервера, SIGNAL(finished()),
 *                  &имя сервера, SLOT(...))
 * 4) запустить "прослушку" serv.listen(ip-address, port)
 *
 *
 * Цикл работы с Tcp-сокетом
 * 1) создат сокет
 * 2) отправить данные socket.write(), либо считать socket.read()
*/



tcpcontroller::tcpcontroller(QObject *parent) : QObject(parent)
{
    serv = new QTcpServer();
    client_sock = new QTcpSocket();
    server_sock = new QTcpSocket();

    // пункт (3) привязка сигнала к слоту
    QObject::connect(serv, SIGNAL (newConnection()),
                     this, SLOT(newConnection()));

    serv->listen(QHostAddress::LocalHost, // "127.0.0.1"
                33333); // запуск бесконечного цикла прослушки (пункт (4) конспекта)


    //client_sock.bind(QHostAddress::LocalHost,33333);
    // из-за ограниченности условий имитуруем входящее подключение вторым сокетом на localhost
    QObject::connect(client_sock, SIGNAL (readyRead()),
                     this, SLOT(clientReady()));
    client_sock->connectToHost(QHostAddress::LocalHost,33333);
}

void tcpcontroller::newConnection() // пункт (2) конспекта
{
    // получение и хранение ссылки на сокет нового входящего соединения
    // который себе уже создал сервер
    //qDebug() << "*** \n\nСработал слот newConnection ***";

    server_sock = serv->nextPendingConnection();



}

void tcpcontroller::clientReady() // слот для обработки содержимого клиентского сокета, имитуруещего
{
}


void tcpcontroller::sendMessag(QString message)
{
    //qDebug() << "*** Мессага от клиента = " << message;
    emit sendMessage();
    QByteArray messag = message.toUtf8();
    client_sock->write(messag);

    qDebug() << "*** Что отправил клиент = " << client_sock;
    server_sock->readAll();
    qDebug() << "*** Что пришло серверу = " << server_sock;
}



