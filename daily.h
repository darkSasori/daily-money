#ifndef DAILY_H
#define DAILY_H

#include <QObject>
#include <QDateTime>
#include "item.h"
#include "dbconnection.h"

class Daily : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> list READ list WRITE setList NOTIFY listChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(float balance READ balance WRITE setBalance NOTIFY balanceChanged)
public:
    explicit Daily(DbConnection db, QDate date, float startBalance, QObject *parent = 0);

    void append(Item *);

    Q_INVOKABLE void init();
    Q_INVOKABLE void remove(int);
    Q_INVOKABLE void newItem(QString, float);

    QList<QObject*> list();
    void setList(QList<QObject*>);
    QDate date();
    void setDate(QDate);
    float balance();
    void setBalance(float b);

signals:
    void listChanged();
    void dateChanged();
    void balanceChanged();

public slots:
    void updateBalance();
    void updateItem(Item*);

private:
    QList<QObject*> m_list;
    QDate m_date;
    float m_startBalance;
    float m_balance;
    DbConnection m_db;
    bool m_initialized;
};

#endif // DAILY_H
