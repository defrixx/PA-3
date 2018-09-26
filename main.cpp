#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "authcontroller.h"
#include "cryptocontroller.h"
#include "db_controller.h"
#include "tcpcontroller.h"
#include <QQmlContext>

int FriendsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return all_friends.count();

}


QVariant FriendsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= all_friends.count())
            return QVariant();
    const Friends &itemToReturn = all_friends[index.row()];
    if (role == FriendNameRole)
        return itemToReturn.Friend();
    else if (role == PhotoRole)
        return itemToReturn.Photo();

    return QVariant();


}


QVariantMap FriendsModel::get(int idx) const
{
    QVariantMap map;
    foreach(int k, roleNames().keys())
    {
        map[roleNames().value(k)] = data(index(idx, 0), k);
    }
    return map;
}

QHash<int, QByteArray> FriendsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FriendNameRole] = "friendname";
    roles[PhotoRole] = "photo";
    return roles;

}


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    AuthController authController; // слот появляется здесь
    CryptoController cryptoController;
    //cryptoController.encryptFile();
    //cryptoController.decryptFile();

    db_controller database;
    //database.sendQuieries();

    tcpcontroller tcp;


    QQmlApplicationEngine engine; // создается движок-контейнер отрисовки QML
    // 3 - ТИП СВЯЗЫВАНИЯ: ВИДИМОСТЬ C++ ОБЪЕКТА В QML
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("authController", // строковое имя для QML
                                &authController); // перемещаемый объект
    context->setContextProperty("friends", // строковое имя для QML
                                    &authController.friendsModel);
    // Именно эта функция помещает в Контекст (область видимости)
      // QML сущность из C++
    context->setContextProperty("cryptoController",
                                &cryptoController);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml"))); // Стартовый QML-файл

    if (engine.rootObjects().isEmpty())
        return -1;

    // сигнал может возникнуть потенциально, начиная с этого места


    // 1 - ТИП СВЯЗЫВАНИЯ: ВИДИМОСТЬ QML-объекта из C++
    // можно вызывать только после загрузки движка и QML-файла

    // ссылка на QML-окно - обладатель сигнала
    QObject * appWindow = engine.rootObjects().first();

    // 2 - ТИП СВЯЗЫВАНИЯ: СВЯЗЬ QML-сигнала с C++ слотом
    // можно вызывать только после загрузки движка, QML-файла и объекта - обладателя слота
    QObject::connect(appWindow,
                     SIGNAL (sendAuth(QString, QString)), // чей и какой сигнал
                     &authController,
                     SLOT(Authentificate(QString, QString))); // к чьему и какому слоту

    QObject::connect(appWindow,
                     SIGNAL(doEncrypt()),
                     &cryptoController,
                     SLOT(encryptFile()));

    QObject::connect(appWindow,
                     SIGNAL(doDecrypt()),
                     &cryptoController,
                     SLOT(decryptFile()));
    QObject::connect(appWindow,
                     SIGNAL(sendFile(QString)),
                     &cryptoController,
                     SLOT(encryptfileUrl(QString)));
    QObject::connect(appWindow,
                     SIGNAL(sendFileD(QString)),
                     &cryptoController,
                     SLOT(decryptfileUrl(QString)));

    QObject::connect(appWindow,
                     SIGNAL(sendMes(QString)),
                     &tcp,
                     SLOT(sendMessag(QString)));

    QObject::connect(appWindow,
                     SIGNAL(dbCreate()),
                     &database,
                     SLOT(sendQuieries()));
    QObject::connect(appWindow,
                     SIGNAL(dbDelete()),
                     &database,
                     SLOT(deleteQuieries()));
    QObject::connect(appWindow,
                     SIGNAL(dbAdd(QString, QString)),
                     &database,
                     SLOT(addQuieries(QString, QString)));


    // 4 - ТИП СВЯЗЫВАНИЯ: РЕАКЦИЯ QML НА C++ СИГНАЛЫ
    // 1. Объявить кастомный сигнал в класссе в разделе signals
    // 2. Вызвать emit имя_сигнала();
    // 3. С помощью 3-ого способа сделать испускающий объект видимым в QML
    // 4. С помощью Connections в QML запустить JavaScript-код для сигнала onИмя_сигнала

    return app.exec();
}



/*
    Основа работы с Git
        1. Создать пустой репозиторий(локальный) в директории с проектом командой :
                >git init

        2. Добавить отслеживаемые файлы командами :
                >git add _
            _ - имя файла, тип файла и т.п.

        2/1. Зарегистрировать свой username и e-mail :
                >git config --global user.name "Oleg"
                >git config --global user.email "defrixx@gmail.com"

        3. Зафиксировать изменения в истории (т.е. создать "версию" или commit) :
                >git commit -m"Текст комментария"
        !!! Обязателен ввод комментария

        4. Связать локальный репозиторий с удаленным
                >git remote add псевдоним http://ссылка.git
                Пример:
                    >git remote add gitlab http://ссылка.git
                Проверить можно:
                    >git remote -v

        5. Последнюю созданную версию отправить на прикрепленный удаленный репозиторий :
                >git push
                    или
                >git push псевдоним название_ветки
                    Пример:
                        >git push gitlab master

        6. Копировать с удаленного репозитория командой :
                >git clone http://ссылка.git

        7. Если текущий локальный репозиторий отстал от удаленного, сделать его снова актуальным командой :
                >git pull

                    !!! TortoiseGit

*/


/* bat-file

cd C:\Users\Defrixx\Documents\QtDefrixx
git reset --mixed gitlab/master
git add *.qml
git add *.h
git add *.cpp
git add *.pro
git add *.bat
git add *.jpg
git add *.png
git add *.conf
git add *.qrc
git add *.ico
git add *.a
git add *.def
git add *.avi
git commit -am"I finished my work : %date%, %time%"
git push gitlab master
pause

*/

