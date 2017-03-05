#include "daily.h"

Daily::Daily(float startBalance, QObject *parent)
    : QObject(parent)
    , m_date(QDate::currentDate())
    , m_startBalance(startBalance)
    , m_balance(startBalance)
{
    connect(this, SIGNAL(listChanged()), this, SLOT(updateBalance()));
}

void Daily::append(Item *item)
{
    m_list.append(item);
    connect(item, SIGNAL(valueChanged()), this, SLOT(updateBalance()));
    emit listChanged();
}

void Daily::remove(int index)
{
    m_list.removeAt(index);
    emit listChanged();
}

void Daily::newItem(QString desc, float value)
{
    append(new Item(desc, value));
    emit listChanged();
}

void Daily::updateBalance()
{
    m_balance = m_startBalance;
    for (auto obj: m_list) {
        auto i = qobject_cast<Item*>(obj);
        m_balance -= i->value();
    }
    emit balanceChanged();
}

QList<QObject*> Daily::list()
{
    return m_list;
}

void Daily::setList(QList<QObject *> l)
{
    m_list = l;
    emit listChanged();
}

QDate Daily::date()
{
    return m_date;
}

void Daily::setDate(QDate d)
{
    m_date = d;
    emit dateChanged();
}

float Daily::balance()
{
    return m_balance;
}

void Daily::setBalance(float b)
{
    m_balance = b;
    emit balanceChanged();
}
