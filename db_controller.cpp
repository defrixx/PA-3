#include "db_controller.h"

/* цикл работы с SQLite БД:
 * 1) создать интерфейс БД (для нужного драйвера - "QSQLITE", "MYSQL", либо
 * 2) открыть с его помощью файл
 * 3) отправить запросы
 * 3.1) формируется строка запроса
 * 3.2) query.exec()
 * 4) закрыть БД
*/

db_controller::db_controller(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE"); // тип БД
    db.setDatabaseName("file.sqlite"); // имя файла бд
    db.open(); // пункт (2)
}

db_controller::~db_controller()
{
    db.close();
}

void db_controller::sendQuieries()
{
    emit dbcreate();
    QSqlQuery query("CREATE TABLE friends"
                    "(userID int ,"
                    "userName varchar(255));");
    query.exec();

    query.prepare("INSERT INTO friends (userID, userName) "
                  "VALUES (1, \'Ivan\');");
    query.exec();

    query.prepare("INSERT INTO friends (userID, userName) "
                  "VALUES (2, \'Alex\');");
    query.exec();

    query.prepare("INSERT INTO friends (userID, userName) "
                  "VALUES (100500, \'Peter\');");
    query.exec();
}

void db_controller::deleteQuieries()
{
    emit dbdelete();
    QSqlQuery query("DROP TABLE friends");
    query.exec();

}

void db_controller::addQuieries(QString queryID, QString queryTXT){

    emit dbadd();

    QSqlQuery query ("INSERT INTO friends (userID, userName)"
                   "VALUES ("
                     + queryID
                     +", \""
                     + queryTXT
                     +"\");");
    //query.exec();



}
