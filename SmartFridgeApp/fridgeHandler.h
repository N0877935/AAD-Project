#ifndef FRIDGEHANDLER_H
#define FRIDGEHANDLER_H

#include <QObject>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include <string>
#include <QDebug>

class fridgeHandler : public QObject
{
    Q_OBJECT
public:
    explicit fridgeHandler (QObject* parent = 0 ) : QObject(parent) {}

    Q_INVOKABLE QString getDoorStatus(QString fridgeID){
        {

        QString status = NULL;
        QString front = NULL;
        QString rear = NULL;

        QSqlDatabase::removeDatabase("connectionFH");
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","connectionFH");
        db.setHostName("localhost");
        db.setPort(3306);
        db.setUserName("root");
        db.setPassword("admin");
        db.setDatabaseName("sf");

        db.open();

        QSqlQuery query(db);

        query.prepare("SELECT frontDoorOpen FROM fridge WHERE fridgeID = ?");
        query.addBindValue(fridgeID);


        if (!query.exec()){
             qDebug("Select front door status Action failed");
        }

        while (query.next()) {
              front = query.value(0).toString();
        }



        query.prepare("SELECT rearDoorOpen FROM fridge WHERE fridgeID = ?");
        query.addBindValue(fridgeID);

        if (!query.exec()){
             qDebug("Select rear door status Action failed");
        }

        while (query.next()) {
              rear = query.value(0).toString();
        }


        if(front == "0" && rear == "0"){
            return "OK";
        }
        else{
            return "";
        }


        }
    }


};

#endif // FRIDGEHANDLER_H
