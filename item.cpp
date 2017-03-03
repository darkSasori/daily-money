#include "item.h"

Item::Item(QString desc, float value, QObject *parent)
    : QObject(parent)
    , m_desc(desc)
    , m_value(value)
{

}
