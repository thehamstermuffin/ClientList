#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <controllers/master-controller.h>
#include <QQmlContext>
#include <framework/command.h>
#include <controllers/command-controller.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<cm::controllers::MasterController>("CM", 1, 0, "MasterController");
    qmlRegisterType<cm::controllers::NavigationController>("CM", 1, 0, "NavigationController");
    qmlRegisterType<cm::controllers::CommandController>("CM", 1, 0, "CommandController");
    qmlRegisterType<cm::framework::Command>("CM", 1, 0, "Command");

    cm::controllers::MasterController masterController;

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/");
    engine.rootContext()->setContextProperty("masterController",
    &masterController);
    engine.load(QUrl(QStringLiteral("qrc:views/MasterView.qml")));

    return app.exec();
}
