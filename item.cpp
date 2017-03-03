#include "item.h"

Item::Item(QString desc, float value, QObject *parent)
    : QObject(parent)
    , m_value(value)
    , m_desc(desc)
{
}

float Item::value()
{
    return m_value;
}

void Item::setValue(float v)
{
    m_value = v;
    emit valueChanged();
}

QString Item::desc()
{
    return m_desc;
}

void Item::setDesc(QString d)
{
    m_desc = d;
    emit descChanged();
}
