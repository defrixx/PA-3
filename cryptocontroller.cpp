#include "cryptocontroller.h"
#include <QFile>


CryptoController::CryptoController(QObject *parent) : QObject(parent)
{

}

void CryptoController::encryptFile(){

    emit encryptsuccess();
    //QByteArray FileURL = fileUrl->toUtf8();
    unsigned char in_buf[1024] = {0},
            out_buf[1024] = {0};
    unsigned char key[] = "123456789";
    unsigned char iv[] = "123456789";

    QString in_file_name, out_file_name;


#ifdef Q_OS_ANDROID
    in_file_name = "/storage/emulated0/Download/f0.txt";
    out_file_name = "/storage/emulated0/Download/f_encrypted.txt"
        #else
    in_file_name = "f.txt";
    out_file_name = "f_encrypted.txt";
#endif

    QFile f_in(in_file_name);
    QFile f_out(out_file_name);
    f_in.open(QIODevice::ReadOnly);
    f_out.open(QIODevice::WriteOnly
               | QIODevice::Truncate);

    EVP_CIPHER_CTX * ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx,
                       EVP_aes_256_cbc(),
                       NULL,
                       key,
                       iv);
    int ln1 = f_in.read((char*)in_buf, 1024);
    int ln2 = 1024, tmpln = 0;

    while (ln1>0)
    {
        if(!EVP_EncryptUpdate(ctx,
                              out_buf, //выходной параметр : ссылка, куда
                              &ln2,
                              in_buf, // входной параметр: что шифровать
                              ln1)) // входной параметр : длина входных данных

        {
            /* Error */
            return;
        }

        f_out.write((char*)out_buf, ln2);
        ln1 = f_in.read((char*)in_buf,1024);
    }


    if (!EVP_EncryptFinal_ex(ctx, out_buf, &tmpln))
    {
        /* Error */
        return;
    }

    f_out.write((char*)out_buf, tmpln);
    EVP_CIPHER_CTX_free(ctx);
    f_out.close();
    f_in.close();
    return;

    /*
    f0.open(QIODevice::ReadOnly);
    f_encrypted.open(QIODevice::WriteOnly
                     | QIODevice::Truncate);

    char buffer[256] = { 0 };
    char out_buf[256] = { 0 };
    EVP_CIPHER_CTX * ctx = EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(ctx, // структура, заполняемая настройками
                       EVP_aes_256_cbc(), // 1) метод шифрования
                       // cbc - независимое шифрование порций
                       // наиболее простая и наименее защищенная схема
                       // зато любая порция может быть расшифрована независима
                       NULL, // 2)...

                       // 3) в виде массива unsigned char заносится пароль
                       // используется (приведение типов *)
                       (unsigned char *)key.toStdString().c_str(),

                       // 4) iv - initialization vector
                       // заносится аналогичным образом из строки

                       (unsigned char *)iv.toStdString().c_str());
    int len1 = 0;
    int len2 = f0.read(buffer, 256);
    while (!f0.atEnd()) // цикл, пока позиция read() менее длины файла
    {
        // шифрование порции
        EVP_EncryptUpdate(ctx, // объект с настройками

                                // выходной буфер с шифрованными данными и его длина
                          (unsigned char *)out_buf, //выходной параметр : ссылка, куда
                          &len1, // выходной параметр: длина полученного шифра

                                // входной буфер с фрагментов файла и его длина
                          (unsigned char*)buffer, // входной параметр: что шифровать
                          len2); // входной параметр : длина входных данных

        // вывод зашифрованной порции в файл
        f_encrypted.write(out_buf, len1);
        // считывание следующей порции

        // QFile::read() не только считывает данные,
        // но и двигает текущую "позицию" в QFile
        len2 = f0.read(buffer, 256);
    }
    EVP_EncryptFinal_ex(ctx, (unsigned char *)out_buf, &len1);
    f_encrypted.write(out_buf, len1);

    f_encrypted.close();
    f0.close();

*/
}

void CryptoController::decryptFile(){

    emit decryptsuccess();

    unsigned char in_buf[1024] = {0},
            out_buf[1024] = {0};
    unsigned char key[] = "123456789";
    unsigned char iv[] = "123456789";

    QString in_file_name, out_file_name;

    // команды для компилятора, не переводятся в бинарный код, просто инструкции
    // (комментарии) для компилятора

    //Называется условной компиляцией

#ifdef Q_OS_ANDROID
    in_file_name = "/storage/emulated0/Download/f_encrypted.txt";
    out_file_name = "/storage/emulated0/Download/f_decrypted.txt"
        #else
    in_file_name = "f_encrypted.txt";
    out_file_name = "f_decrypted.txt";
#endif

    QFile f_in(in_file_name),
            f_out(out_file_name);
    f_in.open(QIODevice::ReadOnly);
    f_out.open(QIODevice::WriteOnly
               | QIODevice::Truncate);

    EVP_CIPHER_CTX * ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx,
                       EVP_aes_256_cbc(),
                       NULL,
                       key,
                       iv);
    int ln1 = f_in.read((char*)in_buf, 1024);
    int ln2 = 1024, tmpln = 0;

    while (ln1>0)
    {
        if(!EVP_DecryptUpdate(ctx,
                              out_buf, //выходной параметр : ссылка, куда
                              &ln2,
                              in_buf, // входной параметр: что шифровать
                              ln1)) // входной параметр : длина входных данных

        {
            /* Error */
            return;
        }

        f_out.write((char*)out_buf, ln2);
        ln1 = f_in.read((char*)in_buf,1024);
    }


    if (!EVP_DecryptFinal_ex(ctx, out_buf, &tmpln))
    {
        /* Error */
        return;
    }

    f_out.write((char*)out_buf, tmpln);
    EVP_CIPHER_CTX_free(ctx);
    f_out.close();
    f_in.close();
    return;

}

void CryptoController::encryptfileUrl(QString fileUrl){
    qDebug() << "\n\nСработал слот FileURL: Url = "
             << fileUrl;

    emit encryptfile();

    unsigned char in_buf[1024] = {0},
            out_buf[1024] = {0};
    unsigned char key[] = "123456789";
    unsigned char iv[] = "123456789";

    QString in_file_name, out_file_name;
    int tag_position = fileUrl.indexOf("Debug");
    tag_position = fileUrl.indexOf("Debug/", tag_position);
    QString url = fileUrl.mid(tag_position + 6, fileUrl.indexOf('/', -1) - tag_position - 6);
    qDebug() << "url после изменения = " << url;


#ifdef Q_OS_ANDROID
    in_file_name = "/storage/emulated0/Download/f0.txt";
    out_file_name = "/storage/emulated0/Download/f_encrypted.txt"
        #else
    in_file_name = url;
    out_file_name = (url + "-E.txt");
#endif

    QFile f_in(in_file_name);
    QFile f_out(out_file_name);
    f_in.open(QIODevice::ReadOnly);
    f_out.open(QIODevice::WriteOnly
               | QIODevice::Truncate);

    EVP_CIPHER_CTX * ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx,
                       EVP_aes_256_cbc(),
                       NULL,
                       key,
                       iv);
    int ln1 = f_in.read((char*)in_buf, 1024);
    int ln2 = 1024, tmpln = 0;
    while (ln1>0)
    {
        if(!EVP_EncryptUpdate(ctx,
                              out_buf, //выходной параметр : ссылка, куда
                              &ln2,
                              in_buf, // входной параметр: что шифровать
                              ln1)) // входной параметр : длина входных данных

        {
            /* Error */
            return;
        }

        f_out.write((char*)out_buf, ln2);
        ln1 = f_in.read((char*)in_buf,1024);
    }


    if (!EVP_EncryptFinal_ex(ctx, out_buf, &tmpln))
    {
        /* Error */
        return;
    }

    f_out.write((char*)out_buf, tmpln);
    EVP_CIPHER_CTX_free(ctx);
    f_out.close();
    f_in.close();
    return;

}

void CryptoController::decryptfileUrl(QString fileUrlD){
    qDebug() << "\n\nСработал слот FileURLdecrypt: Url = "
             << fileUrlD;
    emit decryptsuccess();

    unsigned char in_buf[1024] = {0},
            out_buf[1024] = {0};
    unsigned char key[] = "123456789";
    unsigned char iv[] = "123456789";

    QString in_file_name, out_file_name;
    int tag_position = fileUrlD.indexOf("Debug");
    tag_position = fileUrlD.indexOf("Debug/", tag_position);
    QString url2 = fileUrlD.mid(tag_position + 6, fileUrlD.indexOf('/', -1) - tag_position - 6);
    qDebug() << "url после изменения = " << url2;

    // команды для компилятора, не переводятся в бинарный код, просто инструкции
    // (комментарии) для компилятора

    //Называется условной компиляцией

#ifdef Q_OS_ANDROID
    in_file_name = "/storage/emulated0/Download/f_encrypted.txt";
    out_file_name = "/storage/emulated0/Download/f_decrypted.txt"
        #else
    in_file_name = url2;
    out_file_name = (url2 + "-D.txt");
#endif

    QFile f_in(in_file_name),
            f_out(out_file_name);
    f_in.open(QIODevice::ReadOnly);
    f_out.open(QIODevice::WriteOnly
               | QIODevice::Truncate);

    EVP_CIPHER_CTX * ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx,
                       EVP_aes_256_cbc(),
                       NULL,
                       key,
                       iv);
    int ln1 = f_in.read((char*)in_buf, 1024);
    int ln2 = 1024, tmpln = 0;

    while (ln1>0)
    {
        if(!EVP_DecryptUpdate(ctx,
                              out_buf, //выходной параметр : ссылка, куда
                              &ln2,
                              in_buf, // входной параметр: что шифровать
                              ln1)) // входной параметр : длина входных данных

        {
            /* Error */
            return;
        }

        f_out.write((char*)out_buf, ln2);
        ln1 = f_in.read((char*)in_buf,1024);
    }


    if (!EVP_DecryptFinal_ex(ctx, out_buf, &tmpln))
    {
        /* Error */
        return;
    }

    f_out.write((char*)out_buf, tmpln);
    EVP_CIPHER_CTX_free(ctx);
    f_out.close();
    f_in.close();
    return;
}
