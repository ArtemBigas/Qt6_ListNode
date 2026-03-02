#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "nodes.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    qmlRegisterType<Nodes>("nodes", 1, 0,"Nodes");
    engine.loadFromModule("Artem_Bigas_Junior_Ci", "Main");

    return app.exec();
}
