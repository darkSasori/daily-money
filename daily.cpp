#include "daily.h"

Daily::Daily(float startBalance, QObject *parent)
    : QObject(parent)
    , m_startBalance(startBalance)
    , m_balance(0)
    , m_date(QDate::currentDate())
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
    auto item = m_list.at(index);
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
