#ifndef SERVICE_H
#define SERVICE_H

#include <QTimer>
#include <QRemoteObjectNode>
#include <QRemoteObjectRegistry>
#include <QRemoteObjectHost>
#include "rep_service_source.h"
#include "rep_remoteclientserver_replica.h"

class Service : public ServiceSource
{
    Q_OBJECT
public:
    Service(QObject* parent = nullptr);

public slots:
    virtual void connectRemote(QString serverIP, int serverPort) override;
    virtual void test(QString msg) override;
private slots:
    void setupActions();
    void onRemoteRegistryInitialized();
private:
    QTimer m_loginTimer;
    QRemoteObjectNode* m_remoteNode = nullptr;
    RemoteClientServerReplica* m_clientServer = nullptr;
    QAbstractItemModelReplica* m_printerList = nullptr;
};

#endif // SERVICE_H
