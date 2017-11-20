#ifndef _APP_GLOBAL_H
#define _APP_GLOBAL_H

#include <QObject>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QColor>
#include <QThread>
#include <QRemoteObjectNode>
#include <QRemoteObjectReplica>
#include <QRemoteObjectHost>
#include <QQuickItem>
#include <QTimer>
#include <QAbstractListModel>
#include <QQuickImageProvider>
#include <QAndroidJniObject>
#include <QtAndroid>
#include "rep_service_replica.h"

class AppGlobal : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QColor titleBarColor MEMBER m_titleBarColor NOTIFY titleBarColorChanged)
    Q_PROPERTY(QColor accentColor MEMBER m_accentColor NOTIFY accentColorChanged)
	Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)

    explicit AppGlobal(QQmlEngine* engine, QObject *parent = 0);
    ~AppGlobal();

    Q_INVOKABLE QObject* globalObject(QString name) const;
    Q_INVOKABLE void setGlobalObject(QString name, QObject *object);

	bool busy() const { return m_busy; }
	void setBusy(bool newBusy);


public slots:

signals:
    void titleBarColorChanged();
    void accentColorChanged();
    void quit();
	void busyChanged(bool);

private slots:
private:
	void setupActions();
	void setupConnections();
private:
    QQmlEngine* m_engine = nullptr;
    QString m_currentState = "";
    QMap<QString, QObject*> m_globalObjects;

    QColor m_titleBarColor = QColor(77, 86, 95);
    QColor m_accentColor = QColor(50, 168, 232);

	bool m_busy = false;
};

#endif // _APP_GLOBAL_H
