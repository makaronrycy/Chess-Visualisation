#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <chesscontroler.h>
#include <fileloader.h>
#include <dataparser.h>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    FileLoader file;
    DataParser parser;

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("POiGK1", "Main");

    return app.exec();
}

