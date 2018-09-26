#ifndef DB_CONTROLLER_H
#define DB_CONTROLLER_H

#include <QObject>
#include <QSqlDatabase> // интерфейс для связи с СУБД
#include <QSqlQuery>

// класс, инкапсулирующий
// 1) строку SQL-запроса
// 2) сигналы и слоты готовности СУБД
// 3) результат, возвращаемый СУБД
// 4)
// 5) прочий второстепенный функционал



class db_controller : public QObject
{
    Q_OBJECT
public:
    explicit db_controller(QObject *parent = nullptr);
    QSqlDatabase db;
    ~db_controller();

signals:
    dbcreate();
    dbdelete();
    dbadd();
public slots:
    void sendQuieries();
    void deleteQuieries();
    void addQuieries(QString queryID, QString queryTXT);
private:

};

#endif // DB_CONTROLLER_H
