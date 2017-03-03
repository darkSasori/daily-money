#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "daily.h"
#include "item.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Daily daily(10);
    daily.append(new Item("teste", 10));

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("today", &daily);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
