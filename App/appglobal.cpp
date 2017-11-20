#include "appglobal.h"
#include <QCoreApplication>
#include <QQmlEngine>
#include <QtDebug>
#include <QFontDatabase>
#include <QImage>
#include <QFileInfo>
#include <QAbstractItemModelReplica>
#include <QQmlContext>
#include <QTcpSocket>
#include <QHostAddress>

AppGlobal::AppGlobal(QQmlEngine* engine, QObject *parent)
    : QObject(parent), m_engine(engine)
{
	setupActions();
}

AppGlobal::~AppGlobal()
{
}

void AppGlobal::setupActions()
{

}

QObject * AppGlobal::globalObject(QString name) const
{
	return m_globalObjects.value(name, Q_NULLPTR);
}

void AppGlobal::setGlobalObject(QString name, QObject *object)
{
	m_globalObjects[name] = object;
}

void AppGlobal::setBusy(bool newBusy)
{
	if (m_busy == newBusy) return;
	m_busy = newBusy;
	emit busyChanged(m_busy);
}
