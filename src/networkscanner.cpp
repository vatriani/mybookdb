#include "networkscanner.h"
#include <QDebug>

networkscanner::networkscanner(QObject *parent) :
	QObject(parent)
{
	this->manager = new QNetworkAccessManager(this);
	this->server = new QTcpServer(this);
	this->openPort();
}

networkscanner::~networkscanner()
{
	this->closePort();
	delete this->server;
	delete this->manager;
}

void networkscanner::openPort()
{
	connect(this->server,SIGNAL(newConnection()),this,SLOT(newClient()));
	this->server->listen(QHostAddress::Any,50007);
}

void networkscanner::closePort()
{
	this->server->close();
}

void networkscanner::newClient()
{
	QTcpSocket *tmp = this->server->nextPendingConnection();
	tmp->open(QIODevice::ReadOnly);
	tmp->waitForReadyRead();
	QString recv = tmp->readAll();
	tmp->close();
	recv.remove(QRegExp("<[^>]*>*"));
	recv.remove("\n");
	emit newBarcode(recv);
}
