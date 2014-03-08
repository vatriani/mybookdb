/**
 * @file networkscanner.cpp
 * @brief Class for fetching infos from GCstarScanner from your phone.
 * @copyright
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author	Niels Neumann <vatriani.nn@googlemail.com>
 * @version 1.0
 */



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
