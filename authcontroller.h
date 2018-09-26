#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <windows.h>
#include <QApplication>
#include <QAbstractListModel>
#include <QStringList>


class Friends {
    public:
        Friends(const QString &Friend,
                       const QString &Photo);

        QString Friend() const;
        QString Photo() const;
    private:
        QString friendsname;
        QString friendphoto;
};

class FriendsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {FriendNameRole,
                PhotoRole};
    FriendsModel(QObject *parent = 0);

    void addFriend(const Friends & newFriend);
    virtual int rowCount(const QModelIndex &parent= QModelIndex()) const;
    Q_INVOKABLE void clearModel();
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariantMap get(int idx) const;
    //virtual QVariant data(const QModelIndex &index, int role) const;
protected:
       QHash<int, QByteArray> roleNames() const;

private:
    //QStringList m_data;
    QList<Friends> all_friends;

};

class AuthController : public QObject
{
    Q_OBJECT
public:
    FriendsModel friendsModel;
    explicit AuthController(QObject *parent = nullptr);
    QNetworkAccessManager * na_manager;
    QStringList friends_names;
    QStringList friends_photos;

signals:
    authsuccess();

public slots:
    void Authentificate(QString login, QString password); // параметры такие же, как в сигнале
//private:
//    QStringList m_data;
};


#endif // AUTHCONTROLLER_H
