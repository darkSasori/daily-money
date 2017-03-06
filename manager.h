#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QDate>
#include "daily.h"
#include "dbconnection.h"

class Manager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* today READ today WRITE setToday NOTIFY todayChanged)
    Q_PROPERTY(QList<QObject*> list READ list WRITE setList NOTIFY listChanged)
public:
    explicit Manager(DbConnection db, QObject *parent = 0);

    QObject* today();
    void setToday(QObject *);

    QList<QObject*> list();
    void setList(QList<QObject*>);

    Q_INVOKABLE void updateToday();

signals:
    void todayChanged();
    void listChanged();

public slots:

private:
    DbConnection m_db;
    QList<QObject*> m_list;
    QObject *m_today;
};

#endif // MANAGER_H
