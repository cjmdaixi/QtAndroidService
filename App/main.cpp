#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QRemoteObjectNode>
#include "rep_service_replica.h"
#include "appglobal.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("EPlus3D");
    app.setOrganizationDomain("eplus3d.tech");
    app.setApplicationName("SunStone Client");

    QAndroidJniObject::callStaticMethod<void>("eplus3d/MyService",
                                              "startMyService",
                                              "(Landroid/content/Context;)V",
                                              QtAndroid::androidActivity().object());

    QQmlApplicationEngine *engine = new QQmlApplicationEngine();

    QRemoteObjectNode repNode;
    repNode.connectToNode(QUrl(QStringLiteral("local:service")));
    QSharedPointer<ServiceReplica> rep(repNode.acquire<ServiceReplica>());
    engine->rootContext()->setContextProperty("$service", rep.data());
    bool res = rep->waitForSource();
    Q_ASSERT(res);

    auto appGlobal = new AppGlobal(engine);
    engine->rootContext()->setContextProperty("$app", appGlobal);

    engine->load(QUrl(QLatin1String("qrc:/main.qml")));
    auto result = app.exec();

    delete engine;
    delete appGlobal;

    return result;
}
