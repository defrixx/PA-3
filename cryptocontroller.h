#ifndef CRYPTOCONTROLLER_H
#define CRYPTOCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QApplication>


#include <openssl/conf.h> // функции, структуры и константы настройки OpenSSL
#include <openssl/evp.h> // сами криптогрфические функции https://wiki.openssl.org/index.php/EVP
#include <openssl/err.h> // коды внутренних ошибок OpenSSL и их расшифровка
#include <openssl/aes.h>


class CryptoController : public QObject
{
    Q_OBJECT
public:
    explicit CryptoController(QObject *parent = nullptr);
    QString * fileUrl;

signals:
    encryptsuccess();
    decryptsuccess();
    encryptfile();
    decryptfile();


public slots:
    void encryptFile();
    void decryptFile();
    void encryptfileUrl(QString fileUrl);
    void decryptfileUrl(QString fuleUrlD);
};

#endif // CRYPTOCONTROLLER_H
