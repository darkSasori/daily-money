#include "daily.h"

Daily::Daily(DbConnection db, QDate date, float startBalance, QObject *parent)
    : QObject(parent)
    , m_date(date)
    , m_startBalance(startBalance)
    , m_balance(startBalance)
    , m_db(db)
{
    connect(this, SIGNAL(listChanged()), this, SLOT(updateBalance()));
    init();
}

void Daily::init()
{
    setList(m_db.getItems(m_date));
}

void Daily::append(Item *item)
{
    m_list.append(item);
    connect(item, SIGNAL(valueChanged()), this, SLOT(updateBalance()));
    connect(item, SIGNAL(itemChanged(Item*)), this, SLOT(updateItem(Item*)));
    emit listChanged();
}

void Daily::remove(int index)
{
    Item * item = qobject_cast<Item*>(m_list.at(index));
    m_db.removeItem(item);
    m_list.removeAt(index);
    emit listChanged();
}

void Daily::newItem(QString desc, float value)
{
    Item * item = new Item(desc, value);
    append(item);
    m_db.addItem(item, m_date);
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

void Daily::updateItem(Item *item)
{
    m_db.updateItem(item);
}

QList<QObject*> Daily::list()
{
    return m_list;
}

void Daily::setList(QList<QObject *> list)
{
    for (auto obj: list) {
        Item *item = qobject_cast<Item*>(obj);
        append(item);
    }
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
