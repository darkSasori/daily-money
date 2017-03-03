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

    float value();
    void setValue(float);
    QString desc();
    void setDesc(QString);

signals:
    void valueChanged();
    void descChanged();

public slots:

private:
    float m_value;
    QString m_desc;
};

#endif // ITEM_H
