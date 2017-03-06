#include "manager.h"
#include <algorithm>

bool toSort(QObject *o1, QObject *o2)
{
    QDate d1 = qobject_cast<Daily*>(o1)->date();
    QDate d2 = qobject_cast<Daily*>(o2)->date();
    return d1 > d2;
}

Manager::Manager(DbConnection db, QObject *parent)
    : QObject(parent)
    , m_db(db)
{
    QList<QDate> list = m_db.getDates();
    for (auto it: list) {
        Daily *day = new Daily(m_db, it, 50);
        m_list.append(day);
    }
    updateToday();
}

QObject* Manager::today()
{
    return m_today;
}

void Manager::setToday(QObject *today)
{
    m_today = today;
    qobject_cast<Daily*>(today)->init();
    emit todayChanged();
}

QList<QObject*> Manager::list()
{
    return m_list;
}

void Manager::setList(QList<QObject *> list)
{
    m_list = list;
    emit listChanged();
}

void Manager::updateToday()
{
    QDate today = QDate::currentDate();
    for (auto it: m_list) {
        auto i = qobject_cast<Daily*>(it);
        if (i->date() == today) {
            setToday(i);
            return;
        }
    }

    Daily *daily = new Daily(m_db, today, 50);
    m_list.append(daily);
    setToday(daily);

    std::sort(m_list.begin(), m_list.end(), toSort);
    emit listChanged();
}
