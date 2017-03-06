#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardPaths>
#include "manager.h"
#include "dbconnection.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

#ifdef Q_OS_ANDROID
    QString path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/daily.db";
#else
    QString path = app.applicationDirPath() + "/daily.db";
#endif
    DbConnection db(path);
    Manager manager(db);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("manager", &manager);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
