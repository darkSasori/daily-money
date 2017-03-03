#ifndef ITEM_H
#define ITEM_H

#include <QObject>

class Item : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString desc READ desc WRITE setDesc NOTIFY descChanged)
public:
    explicit Item(QString desc, float value, QObject *parent = 0);

    float value() { return m_value; }
    void setValue(float v) { m_value = v; emit valueChanged(); }
    QString desc() { return m_desc; }
    void setDesc(QString d) { m_desc = d; emit descChanged(); }

signals:
    void valueChanged();
    void descChanged();

public slots:

private:
    float m_value;
    QString m_desc;
};

#endif // ITEM_H
