#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "manager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Manager manager;


    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("manager", &manager);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
