#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <controllers/master-controller.h>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<cm::controllers::MasterController>("CM", 1, 0, "MasterController");

    cm::controllers::MasterController masterController;
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/views/MasterView")));


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("masterController",
    &masterController);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(QUrl(QStringLiteral("qrc:views/MasterView.qml")));

    return app.exec();
}
