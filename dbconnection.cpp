#include "dbconnection.h"

DbConnection::DbConnection(const QString path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << m_db.lastError().text();
    }

    init();
}

void DbConnection::init()
{
    if (!m_db.isOpen()) {
        return;
    }

    QSqlQuery query = m_db.exec("CREATE TABLE IF NOT EXISTS lanc(id text primary key, `date` date, `desc` text, `value` float)");
    if (!query.isValid() && query.lastError().type()) {
        qDebug() << query.lastError().text();
    }
}

void DbConnection::addItem(Item *item, QDate date)
{
    if (!m_db.isOpen()) {
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO lanc VALUES(:id, :date, :desc, :value)");
    query.bindValue(":id", item->id());
    query.bindValue(":date", date.toString(Qt::ISODate));
    query.bindValue(":desc", item->desc());
    query.bindValue(":value", item->value());
    if (!query.exec()) {
        qDebug() << query.lastError().text();
    }
}

QList<QObject*> DbConnection::getItems(QDate date)
{
    QList<QObject*> list;

    if (!m_db.isOpen()) {
        return list;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM lanc WHERE `date` = :date");
    query.bindValue(":date", date.toString(Qt::ISODate));
    if (query.exec()) {
        while (query.next()) {
            QString uuid = query.value("id").toString();
            QString desc = query.value("desc").toString();
            float value = query.value("value").toFloat();
            list.append(new Item(uuid, desc, value));
        }
    }

    return list;
}

void DbConnection::updateItem(Item *item)
{
    if (!m_db.isOpen()) {
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE lanc SET `desc` = :desc, `value` = :value WHERE id = :id");
    query.bindValue(":id", item->id());
    query.bindValue(":desc", item->desc());
    query.bindValue(":value", item->value());
    if (!query.exec()) {
        qDebug() << query.lastError().text();
    }
}

void DbConnection::removeItem(Item *item)
{
    if (!m_db.isOpen()) {
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM lanc WHERE id = :id");
    query.bindValue(":id", item->id());
    if (!query.exec()) {
        qDebug() << query.lastError().text();
    }
}
