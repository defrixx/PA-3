#ifndef TCPCONTROLLER_H
#define TCPCONTROLLER_H

#include <QObject>
#include <QList>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include <QTcpServer>

/* класс, инкапсулирующий
 * 1) сокет (конечную точку с буфером, связанную с сетевым адаптером)
 * 2) бесконечный цикл попыток чтения из сокета (т.н. "прослушка")
 * 3) генерация сигналов при поступлении каких-то данных на сокет сервера
 * 4) поддержка нескольких соединений
*/

#include <QTcpSocket>

/* класс, инкапсулирующий
 * 1) буфер данных, который будет отправляться/считываться с адаптера
 * 2) функции для чтения/записи
 * 3) остальной функционал типичного устройства
 * ввода/вывода (наподобие QFile, QIODevice и т.д.) */

class tcpcontroller : public QObject
{
    Q_OBJECT
public:
    explicit tcpcontroller(QObject *parent = nullptr);
    QTcpServer * serv; // пункт (1) конспекта
    QTcpSocket * client_sock;
    QTcpSocket * server_sock;
    QString * message;





    /*QList<QTcpSocket *> sockets; // получатели данных
    QTcpSocket *firstSocket; // вещатель*/
   // QList<QTcpSocket*> socket_list; - на случай необходимости поддержки нескольких соединений

signals:
    sendMessage();

public slots:
    void sendMessag(QString message);
    void newConnection();
    void clientReady();

    /*void incommingConnection(); // обработчик входящего подключения
        void readyRead(); // обработчик входящих данных
        void stateChanged(QAbstractSocket::SocketState stat); // обработчик изменения состояния вещающего сокета (т.к. всегда есть вещатель)*/
};


#endif // TCPCONTROLLER_H
