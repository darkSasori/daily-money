#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QUuid>

class Item : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString desc READ desc WRITE setDesc NOTIFY itemChanged)
public:
    explicit Item(QString desc, float value, QObject *parent = 0);
    explicit Item(QString uuid, QString desc, float value, QObject *parent=0);

    float value();
    void setValue(float);
    QString desc();
    void setDesc(QString);
    QString id();

signals:
    void valueChanged();
    void itemChanged(Item*);

public slots:

private:
    float m_value;
    QString m_desc;
    QString m_uuid;
};

#endif // ITEM_H
