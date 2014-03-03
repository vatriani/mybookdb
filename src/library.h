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
 * @defgroup DB Database Structure
 * @{
 *
 * @brief Small explanation about the database structure.
 *
 * @todo adding more fields for more gui informations.
 *
 * @section LABEL_DB List of tables in database
 *
 * @dot
 * digraph example {
 *     node [shape=record, fontname=Helvetica, fontsize=10];
 *     a [ label="author" ];
 *     b [ label="authors" ];
 *     c [ label="book" ];
 *     d [ label="genre" ];
 *     e [ label="genres" ];
 *     f [ label="keyword" ];
 *     g [ label="keywords" ];
 *     h [ label="languages" ];
 *     i [ label="publisher" ];
 *     j [ label="serie" ];
 *     a -> b [ arrowhead="open", style="solid" ];
 *     d -> e [ arrowhead="open", style="solid" ];
 *     f -> g [ arrowhead="open", style="solid" ];
 *     b -> c [ arrowhead="open", style="solid" ];
 *     e -> c [ arrowhead="open", style="solid" ];
 *     g -> c [ arrowhead="open", style="solid" ];
 *     c -> h [ arrowhead="open", style="solid" ];
 *     c -> i [ arrowhead="open", style="solid" ];
 *     c -> j [ arrowhead="open", style="solid" ];
 * }
 * @enddot
 *
 * @subsection author
 *     - authors @a NUMERIC
 *     - book @a NUMERIC
 * @subsection authors
 *     - name @a TEXT
 *     - key @a NUMERIC
 * @subsection book
 *     - pages @a NUMERIC
 *     - language @a NUMERIC
 *     - description @a TEXT
 *     - serie @a NUMERIC
 *     - publisher @a NUMERIC
 *     - title @a TEXT
 *     - isbn @a TEXT
 *     - key @a NUMERIC
 * @subsection genre
 *     - key  @a NUMERIC
 *     - name @a TEXT
 * @subsection genres
 *     - book @a NUMERIC
 *     - genre @a NUMERIC
 * @subsection keyword
 *     - key @a NUMERIC
 *     - name @a TEXT
 * @subsection keywords
 *     - key @a NUMERIC
 *     - name @a TEXT
 * @subsection languages
 *     - key @a NUMERIC
 *     - name @a TEXT
 * @subsection publisher
 *     - key @a NUMERIC
 *     - name @a TEXT
 * @subsection serie
 *     - key @a NUMERIC
 *     - name @a TEXT
 * @}
 */



/**
 * @brief Handles db querys and db connection.
 */
class library : public QObject
{
	Q_OBJECT
public:
	/**
	 * @brief Default constructor.
	 *
	 * Creates tables and database file if it not exists and opened the
	 * databasefile.
	 */
	explicit library(QObject *parent = 0);
	/**
	 * @brief Default destructor.
	 *
	 * Do some cleanup and close the databasefile.
	 */
	~library();

	/**
	 * @brief Returns all authors listed by the database.
	 *
	 * This function is generally only for building up the overviewtree.
	 * @return Double-linked list of QStrings as result.
	 * @see query2LinkedLists(QString)
	 */
	QList<QList<QString> > getAllAuthors();
	/**
	 * @brief Returns all books from one author.
	 * @param authorkey Key from author->key.
	 * @return Linked list of QStrings as result, containing book->title.
	 * @see queryLinkedList(QString)
	 */
	QList<QString> getBooksFromAuthorKey(QString);
	/**
	 * @brief Returns all books from a serie.
	 * @param serieskey Key from series->key.
	 * @return Linked list of QStrings as result, containing book->title.
	 * @see queryLinkedList(QString)
	 */
	QList<QString> getBooksFromSeries(QString);
	/**
	 * @brief Returns all authors of a book.
	 * @param bookkey Key from book->key.
	 * @return Linked list of QStrings as result, containing authors->key.
	 * @see queryLinkedList(QString)
	 */
	QList<QString> getAuthorsOfBook(QString);
	/**
	 * @brief Returns all values from the given book of the book-table.
	 * @param bookkey Key from book->key.
	 * @return Linked list of QStrings as result, containing all book values.
	 * @see queryLinkedList(QString)
	 */
	QList<QString> getFullBookByKey(QString);
	/**
	 * @brief Return all books matched search string.
	 * @param booktitle QString contains a search key.
	 * @return Linked list of QStrings as result, containing bookkeys.
	 * @see querySingle(QString)
	 */
	QString getBookKeyByTitle(QString);

private:
	/**
	 * @brief Handles database connection.
	 *
	 * Containing the database sqlite3 handler.
	 */
	sqlite3 *db;

	/**
	 * @brief Helperfunction for opening sqlite3 database.
	 * @param filename Path and Filename.
	 * @return true if sucssess, false if some error detected.
	 */
	bool open(QString filename);
	/**
	 * @brief Helperfunction for closing sqlite3 database.
	 */
	void close();
	/**
	 * @brief Helperfunctions to get NxN-dimensional result.
	 * @param sqlstatement Statement to query.
	 * @return Double linked list of QStrings, contains the result.
	 */
	QList<QList<QString> > query2LinkedLists(QString);
	/**
	 * @brief Helperfunction to get N results.
	 * @param sqlstatement Statement to query.
	 * @return Linked list of QStrings, contains the result.
	 */
	QList<QString> queryLinkedList(QString);
	/**
	 * @brief Helperfunction to get a single result.
	 * @param sqlstatement Statement to query.
	 * @return QString as result.
	 */
	QString querySingle(QString);
};

/**
 * @brief Global library instance for getting everywhere infos.
 */
extern library *_library;


#endif // LIBRARY_H
/**
 * @}
 */
