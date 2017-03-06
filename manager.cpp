#include "manager.h"

Manager::Manager(DbConnection db, QObject *parent)
    : QObject(parent)
    , m_db(db)
{
    updateToday();
}

QObject* Manager::today()
{
    return m_today;
}

void Manager::setToday(QObject *today)
{
    m_today = today;
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
        }
    }

    Daily *daily = new Daily(m_db, today, 50);
    m_list.append(daily);
    setToday(daily);
    emit listChanged();
}
