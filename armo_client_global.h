#ifndef ARMO_CLIENT_GLOBAL_H
#define ARMO_CLIENT_GLOBAL_H

#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QImage>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QPixmap>
#include <QBuffer>
#include <QFileInfo>
#include <QUrl>
#include "../armo_Image/armoShowImage.hh"

class armo_Client_Global : public QObject
{
    Q_OBJECT

private:
    QObject* proot;
    int argc;
    char **argv;

    void callShowImage(CORBA::Object_ptr obj, QString filename);

public:
    explicit armo_Client_Global(QObject *parent = nullptr);

    void setArgs(int argcount, char** arguments);

signals:

public slots:
    void onEngineCreated(QObject *obj, const QUrl &objUrl);
    void onShowImage(QString srvID, QString filename);

};

#endif // ARMO_CLIENT_GLOBAL_H
