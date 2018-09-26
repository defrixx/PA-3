#include "authcontroller.h"



AuthController::AuthController(QObject *parent) : QObject(parent)
{
    na_manager = new QNetworkAccessManager();
}


    QStringList list;
    QStringList list2;
    QString strFriends;
    QString first_friend;
    QString second_friend;
    QString third_friend;
    QString fourth_friend;
    QString fifth_friend;
    QString first_photo;
    QString second_photo;
    QString third_photo;
    QString fourth_photo;
    QString fifth_photo;

Friends::Friends(const QString &Friend, const QString &Photo):
    friendsname(Friend),
    friendphoto(Photo){}

QString Friends::Friend() const {
    return friendsname;
}

QString Friends::Photo() const {
    return friendphoto;
}

void AuthController::Authentificate(QString login, QString password)
{
    friends_names.clear();
    friends_photos.clear();
    qDebug() << "\n\nСработал слот Authentificate: login = "
             << login
             << ", password = "
             << password;

    emit authsuccess();


    // данные три строчки служат для ожидания ответа от сервера
    // не выходя из функции (синхронная обработка)
    // в отличии от Асинхронной с виджетами, банками и слотами/сигналами
    QEventLoop loop;
    connect(na_manager, SIGNAL(finished(QNetworkReply*)),
            &loop, SLOT(quit()));
    //loop.exec();

    QString clientID = "6476764";
    QNetworkReply * reply = na_manager->get(
                QNetworkRequest(
                    QUrl(
                        "https://oauth.vk.com/authorize"
                        "?client_id=" + clientID +
                        "&display=mobile"
                        "&redirect_uri=https://oauth.vk.com/blank.html"
                        "&scope=friends"
                        "&response_type=token"
                        "&v=5.37"
                        "&state=123456"
                        )
                    )
                );
    //https://oauth.vk.com/authorize?client_id=6444409&..

    loop.exec();

    //Должна была прийти форма авторизации
    QString str(reply->readAll());
    qDebug() << "ответ от сервера = " << str;

    //Находим параметры из формы авторизации
    int tag_position = str.indexOf("ip_h");
    tag_position = str.indexOf("value=\"", tag_position);
    QString ip_h = str.mid(tag_position + 7, str.indexOf('\"',tag_position + 7) - tag_position - 7);
    qDebug() << "ip_h = " << ip_h;

    tag_position = str.indexOf("_origin");
    tag_position = str.indexOf("value=\"", tag_position);
    QString _origin = str.mid(tag_position + 7, str.indexOf('\"',tag_position + 7) - tag_position - 7);
    qDebug() << "_origin = " << _origin;

    tag_position = str.indexOf("lg_h");
    tag_position = str.indexOf("value=\"", tag_position);
    QString lg_h = str.mid(tag_position + 7, str.indexOf('\"',tag_position + 7) - tag_position - 7);
    qDebug() << "lg_h = " << lg_h;

    tag_position = str.indexOf("\"to");
    tag_position = str.indexOf("value=\"", tag_position);
    QString to = str.mid(tag_position + 7, str.indexOf('\"',tag_position + 7) - tag_position - 7);
    qDebug() << "to = " << to;





    //Отправим новый запрос с параметрами и логином, паролем
    QString authrequest = "https://login.vk.com/"
                          "?act=login"
                          "&soft=1"
                          "&utf8=1"
                          "&_origin=" + _origin +
            "&lg_h=" + lg_h +
            "&ip_h=" + ip_h +
            "&to=" + to +
            "&email=" + login +
            "&pass=" + QUrl::toPercentEncoding(password);

    qDebug() << "\n\nТУТА Я" << authrequest << "\n\n";

    //QEventLoop loop;
    connect(na_manager,SIGNAL(finished(QNetworkReply*)),&loop,SLOT(quit()));

    QNetworkReply * reply2 = na_manager->get(
                QNetworkRequest(
                    QUrl(authrequest)
                    )
                );

    loop.exec();

    str = reply2->header(QNetworkRequest::LocationHeader).toString();
    // str2(reply2->readAll());
    qDebug() << "Oтвет от сервера2 Header= " << str;


    QNetworkReply * reply3 = na_manager->get(
                QNetworkRequest(
                    QUrl(reply2->header(QNetworkRequest::LocationHeader).toString())
                    )
                );

    loop.exec();

    str = reply3->header(QNetworkRequest::LocationHeader).toString();
    qDebug() << "ответ от сервера3 Header= " << str;
    QString trap1(reply3->readAll());
    qDebug() << "ответ от сервера3 Body= " << trap1;



    QNetworkReply * reply4 = na_manager->get(
                QNetworkRequest(
                    QUrl(reply3->header(QNetworkRequest::LocationHeader).toString())
                    )
                );

    loop.exec();

    str = reply4->header(QNetworkRequest::LocationHeader).toString();
    qDebug() << "ответ от сервера4 Header= " << str;
    QString trap(reply4->readAll());
    qDebug() << "ответ от сервера4 Body= " << trap;

    tag_position = str.indexOf("access_token=") + 13;

    QString token = str.mid(tag_position, 85);
    qDebug() << "access_token = " << token;
    //получение списка 10 контактов ВК
    reply = na_manager->get(
                QNetworkRequest(
                    QUrl("https://api.vk.com/method/friends.get"
                         "?out=0"
                         "&v=5.37"
                         "&order=hints"
                         "&access_token=" + token)));

    loop.exec();

    strFriends= reply ->readAll();
    qDebug() << "*** Результат 2 запроса BODY" << strFriends;

    //Вся строка JSON  грузится в QJsonDocument
    QJsonDocument itemDoc = QJsonDocument::fromJson(strFriends.toUtf8());
    QJsonObject itemObject = itemDoc.object();
    qDebug()<<"** itemObject.keys()" << itemObject.keys();

    QJsonObject responseObject;
    QJsonArray itemArray;

    qDebug()<<"*** itemObject[\"response\"].type()" << itemObject["response"].type();
    if (itemObject.contains("response") && itemObject["response"].isObject())
    {
        responseObject = itemObject["response"].toObject();
        qDebug()<<"*** responseObject"<<responseObject;
    }
    else
    {
        qDebug() << "Поле \"response\" не содержим объекта";
        //return itemArray;
    }
    if (responseObject.contains("items") && responseObject["items"].isArray())
    {
        itemArray = responseObject["items"].toArray();
        qDebug()<<"*** itemArray"<<itemArray;
    }
    else
    {
        qDebug() << "Поле \"items\" не содержим массива";
        //return itemArray;
    }
    qint32 i;
    for (i=0; i<=4;i = i + 1)
    {
        qintptr id = itemArray[i].toInt();
        qDebug() <<"***itemArray[i]" << id;
        QString id2 = str.setNum(id);
        qDebug()<<"*** id2 =" << id2;
        QNetworkReply * reply =
                na_manager->get(
                    QNetworkRequest(
                        QUrl("https://api.vk.com/method/users.get?out=0&v=5.37&order=hints&access_token="+ token +"&user_ids=" + id2)));
        loop.exec();
        //QString info( reply->readAll() );
        QString textName = reply->readAll();
        qDebug() << "*** name = " << textName;

        tag_position = textName.indexOf("first_name\":\"");
        QString first_name = textName.mid(tag_position + 13, textName.indexOf('\"',tag_position + 13) - tag_position - 13);
        //qDebug() << "first_name =  " << first_name;

        tag_position = textName.indexOf("last_name\":\"");
        QString last_name = textName.mid(tag_position + 12, textName.indexOf('\"',tag_position + 12) - tag_position - 12);
        //qDebug() << "last_name =  " << last_name;

        QString full_name = first_name + " " + last_name;
        qDebug() << "full_name =" << full_name;
        list<< full_name;
        friends_names.append(full_name);

        QNetworkReply * reply5 =
                na_manager->get(
                    QNetworkRequest(
                        QUrl("https://api.vk.com/method/photos.get?out=0&v=5.37&order=hints&access_token="+ token +"&owner_id="+
                                id2 +"&album_id=profile&rev=1&count=1")));
        loop.exec();
        //QString info( reply->readAll() );
        str = reply5->readAll();
        tag_position = str.indexOf("\"photo_75\"");
        QString photo_profile = str.mid(tag_position + 12, str.indexOf('\"',tag_position + 12) - tag_position - 12);
        qDebug() << "*** photo_profile = " << str;
        list2 << photo_profile.replace("\\","");
        friends_photos.append(photo_profile.replace("\\",""));
        Sleep(1000);
    }
    for (int i = 0; i <= 4; i++) {
        friendsModel.addFriend(Friends(friends_names[i], friends_photos[i]));
    }

    first_friend = list[0];
    second_friend = list[1];
    third_friend = list[2];
    fourth_friend = list[3];
    fifth_friend = list[4];

    first_photo = list2[0];
    second_photo = list2[1];
    third_photo = list2[2];
    fourth_photo = list2[3];
    fifth_photo = list2[4];


    qDebug() << first_friend;
    qDebug() << first_photo;
    qDebug() << second_friend;
    qDebug() << second_photo;
    qDebug() << third_friend;
    qDebug() << third_photo;
    qDebug() << fourth_friend;
    qDebug() << fourth_photo;
    qDebug() << fifth_friend;
    qDebug() << fifth_photo;
}

FriendsModel::FriendsModel(QObject *parent)
{

}

void FriendsModel::addFriend(const Friends &newFriend)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    all_friends << newFriend;
    endInsertRows();
}

void FriendsModel::clearModel()
{
    beginRemoveRows(QModelIndex(), 0, rowCount());
    endRemoveRows();
    all_friends.clear();
}
