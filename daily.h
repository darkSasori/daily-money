#ifndef DAILY_H
#define DAILY_H

#include <QObject>
#include <QDateTime>
#include "item.h"

class Daily : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> list READ list WRITE setList NOTIFY listChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(float balance READ balance WRITE setBalance NOTIFY balanceChanged)
public:
    explicit Daily(float startBalance, QObject *parent = 0);

    void append(Item *);

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

private:
    QList<QObject*> m_list;
    QDate m_date;
    float m_balance;
    float m_startBalance;
};

#endif // DAILY_H
