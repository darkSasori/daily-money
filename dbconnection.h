#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QObject>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>
#include "item.h"

class DbConnection
{
public:
    DbConnection(const QString);

    void init();

    void addItem(Item *, QDate);
    void updateItem(Item *);
    void removeItem(Item *);
    QList<QObject*> getItems(QDate);
    QList<QDate> getDates();

private:
    QSqlDatabase m_db;
};

#endif // DBCONNECTION_H
