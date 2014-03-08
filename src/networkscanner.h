/**
 * @file networkscanner.h
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
#ifndef NETWORKSCANNER_H
#define NETWORKSCANNER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QTcpServer>

/**
 * @addtogroup NGUI Non GUI classes
 * @{
 */

/**
 * @brief The networkscanner class work together with GCStarScanner.
 *
 * This class provides the functionallity for communicate with the GCStarScanner
 * app from android store. It inserts ISBN numbers from your handy cam.
 */
class networkscanner : public QObject
{
	Q_OBJECT
public:
	/**
	 * @brief Default constructor for setting up server instance.
	 */
	explicit networkscanner(QObject *parent = 0);
	/**
	 * @brief Default destructor for closing server instance.
	 */
	~networkscanner();


signals:
	/**
	 * @brief Emitted by barcode recieved by a client through GCStarScanner app.
	 * @param barcode QString of the barcode.
	 */
	void newBarcode(QString barcode);

public slots:
	/**
	 * @brief New client appeared.
	 */
	void newClient();

private:
	QNetworkAccessManager *manager;
	QTcpServer *server;

	/**
	 * @brief openPort
	 */
	void openPort();
	/**
	 * @brief closePort
	 */
	void closePort();
};
/**
 * @}
 */
#endif // NETWORKSCANNER_H
