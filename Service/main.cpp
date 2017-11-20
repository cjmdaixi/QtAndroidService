#include <QCoreApplication>
#include <QRemoteObjectHost>
#include <QtDebug>
#include "service.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    qDebug() << "Hello from service";

    QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:service")));
    Service service;
    srcNode.enableRemoting(&service);

    return app.exec();
}
