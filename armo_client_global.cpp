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

void armo_Client_Global::callShowImage(CORBA::Object_ptr obj, QString filename){

    armoShowImage_var echoref = armoShowImage::_narrow(obj);

    if (CORBA::is_nil(echoref)) {
      qDebug() << "Can't narrow reference to type armoShowImage (or it was nil)." << endl;
      return;
    }

    QByteArray ba_filename = filename.toLocal8Bit();
    CORBA::String_var ans;
    ans = echoref->showImageByString(ba_filename.data());
    qDebug()<<" get ans="<<ans;

}

void armo_Client_Global::onShowImage(QString srvID, QString filename){

    try {
        qDebug()<<" start send show srvID="<<srvID<<"   fileName="<<filename;
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

        QByteArray ba_srvID = srvID.toLocal8Bit();
        CORBA::Object_var obj = orb->string_to_object(ba_srvID.data());
        callShowImage(obj, filename);

        orb->destroy();
      }
      catch (CORBA::TRANSIENT&) {
        qDebug() << "Caught system exception TRANSIENT -- unable to contact the "
             << "server." << endl;
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
