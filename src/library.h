/**
 * @file library.h
 * @brief Class for lSQL handling.
 * @copyright
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author	Niels Neumann <vatriani.nn@googlemail.com>
 * @version 1.0
 */

/**
 * @addtogroup NGUI non GUI classes
 * @{
 */
#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QString>
#include <QList>

#include "sqlite3.h"
#include "version.h"



/**
 * @brief Handles db querys and db connection.
 */
class library : public QObject
{
	Q_OBJECT
public:
	explicit library(QObject *parent = 0);
	~library();

	bool open(QString filename);
	QList<QList<QString> > query2LinkedLists(QString /**query*/);
	QList<QString> queryLinkedList(QString /**query*/);
	QString querySingle(QString /**query*/);
	void close();

	QList<QList<QString> > getAllAuthors();
	QList<QString> getBooksFromAuthorKey(QString /**authorKey*/);
	QList<QString> getBooksFromSeries(QString /**serie*/);
	QList<QString> getAuthorsOfBook(QString /**book*/);
	QList<QString> getFullBookByKey(QString /**key*/);
	QString getBookKeyByTitle(QString /**title*/);

private:
	/**
	 * Handles database connection.
	 */
	sqlite3 *db;
};

/**
 * @brief _library
 */
extern library *_library;

#endif // LIBRARY_H
/**
 * @}
 */
