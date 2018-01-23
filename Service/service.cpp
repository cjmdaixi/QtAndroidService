#include "service.h"
#include <QAbstractItemModelReplica>
#include <QTcpSocket>
#include <QHostAddress>

QString getLocalIP()
{
    QTcpSocket socket;
    // 通过连接外网IP地址，从而自动获得本机IP地址
    // comments again.
    socket.connectToHost("8.8.8.8", 53); // google DNS, or something else reliable
    if (socket.waitForConnected())
    {
        auto localIpAddr = socket.localAddress().toString();
        return localIpAddr;
    }
    return QStringLiteral("127.0.0.1");
}

Service::Service(QObject* parent)
    : ServiceSource(parent)
{
    m_loginTimer.setInterval(5000);
    m_loginTimer.setSingleShot(true);

    setupActions();
}

void Service::setupActions()
{
    connect(&m_loginTimer, &QTimer::timeout, [this]() {
//        qDebug() << "login timeout! log failed!";
        m_remoteNode->deleteLater();
        m_remoteNode = nullptr;
        emit connectTimeout();
//        emit info("timeout!");
    });
}

void Service::connectRemote(QString serverIP, int serverPort)
{
    // 每次重新连接时都需要将老的连接去掉
    if (m_remoteNode)
        m_remoteNode->deleteLater();

    m_loginTimer.start();

    auto remoteAddr = QString("tcp://%1:%2").arg(serverIP).arg(serverPort);
    m_remoteNode = new QRemoteObjectNode(QUrl(remoteAddr));
    QObject::connect(m_remoteNode->registry(), &QRemoteObjectReplica::initialized,
                     this, &Service::onRemoteRegistryInitialized);
}

void Service::test(QString msg)
{
    emit info(msg + " Hi~~");
}


void Service::onRemoteRegistryInitialized()
{
    if (m_loginTimer.isActive())
        m_loginTimer.stop();

    info("Registry initialized!");
    emit remoteConnected();

    m_clientServer = m_remoteNode->acquire<RemoteClientServerReplica>();
    m_printerList = m_remoteNode->acquireModel("RemotePrinterList");

    QObject::connect(m_remoteNode->registry(), &QRemoteObjectReplica::stateChanged,
        [this](QRemoteObjectReplica::State newState, QRemoteObjectReplica::State oldState)
    {
        if (oldState == QRemoteObjectReplica::Valid && newState == QRemoteObjectReplica::Suspect)
        {
            qDebug() << "Server disconnected!";
            m_remoteNode->deleteLater();
            m_remoteNode = nullptr;
            emit remoteDisconnected();
        }
    });

    QObject::connect(m_printerList, &QAbstractItemModelReplica::dataChanged,
        [this](const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
//        auto roleNames = m_printerList->roleNames();
//        auto imgIdx = roleNames.key("layerImage");
//        if (roles.contains(imgIdx))
//        {
//            for(auto rowIdx = topLeft.row(); rowIdx <= bottomRight.row(); ++rowIdx)
//                emit layerImageReload(rowIdx);
//        }
    });
}
