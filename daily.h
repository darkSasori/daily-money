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

    QList<QObject*> list() { return m_list; }
    QDate date() { return m_date; }
    float balance() { return m_balance; }

    void setList(QList<QObject*> l) { m_list = l; emit listChanged(); }
    void setDate(QDate d) { m_date = d; emit dateChanged(); }
    void setBalance(float b) { m_balance = b; emit balanceChanged(); }

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
