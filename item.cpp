#include "item.h"

Item::Item(QString desc, float value, QObject *parent)
    : QObject(parent)
    , m_value(value)
    , m_desc(desc)
    , m_uuid(QUuid::createUuid().toString())
{
}

Item::Item(QString uuid, QString desc, float value, QObject *parent)
    : QObject(parent)
    , m_value(value)
    , m_desc(desc)
    , m_uuid(uuid)
{
}

float Item::value()
{
    return m_value;
}

void Item::setValue(float v)
{
    if (m_value == v) {
        return;
    }

    m_value = v;
    emit valueChanged();
    emit itemChanged(this);
}

QString Item::desc()
{
    return m_desc;
}

void Item::setDesc(QString d)
{
    if (m_desc == d) {
        return;
    }

    m_desc = d;
    emit itemChanged(this);
}

QString Item::id()
{
    return m_uuid;
}
