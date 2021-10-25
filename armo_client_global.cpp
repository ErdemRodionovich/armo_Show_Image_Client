#include "armo_client_global.h"

armo_Client_Global::armo_Client_Global(QObject *parent) : QObject(parent)
{

}

void armo_Client_Global::onEngineCreated(QObject *obj, const QUrl &objUrl){

    if(!obj){
        QCoreApplication::exit(-1);
        return;
    }

    proot = obj;

    QObject::connect(proot, SIGNAL(showImage(QString, QString)),
                     this, SLOT(onShowImage(QString, QString)),
                     Qt::QueuedConnection);

}

void armo_Client_Global::callShowImage(CORBA::Object_ptr objServ, QString filename){

    armoShowImage_var echoref = armoShowImage::_narrow(objServ);

    if (CORBA::is_nil(echoref)) {
      qDebug() << "Can't narrow reference to type armoShowImage (or it was nil)." << endl;
      return;
    }

    QString fff = filename;
    fff.replace("//", "/");
    QUrl fileURL(fff);
    QString pathOfFile = fileURL.path();
    QFileInfo finf(pathOfFile);
    QString extension = finf.suffix();
    QImage imageFromFile(pathOfFile);
    QJsonObject js;
    QPixmap mp = QPixmap::fromImage(imageFromFile);
    QByteArray bytes;
    QBuffer buff(&bytes);
    buff.open(QIODevice::WriteOnly);
    QByteArray ba_ext = extension.toLocal8Bit();
    mp.save(&buff, ba_ext.data());
    js["data"] = QLatin1String(buff.data().toBase64());
    js["ext"] = extension;

    QJsonDocument jdoc(js);
    QString jstring = jdoc.toJson();
    QByteArray ba_jstring = jstring.toLocal8Bit();
    CORBA::String_var ans;
    ans = echoref->showImageByString(ba_jstring.data());

}

void armo_Client_Global::onShowImage(QString srvID, QString filename){

    try {
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

        QByteArray ba_srvID = srvID.toLocal8Bit();
        CORBA::Object_var obj = orb->string_to_object(ba_srvID.data());
        callShowImage(obj, filename);

        orb->destroy();
      }
      catch (CORBA::TRANSIENT&) {
        qDebug() << "Caught system exception TRANSIENT -- unable to contact the " << "server." << endl;
      }
      catch (CORBA::SystemException& ex) {
        qDebug() << "Caught a CORBA::" << ex._name() << endl;
      }
      catch (CORBA::Exception& ex) {
        qDebug() << "Caught CORBA::Exception: " << ex._name() << endl;
      }

}

void armo_Client_Global::setArgs(int argcount, char **arguments){

    argc = argcount;
    argv = arguments;

}
