/**
 * @file library.h
 * @brief Class for lSQL handling.
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

/**
 * @addtogroup NGUI Non GUI classes
 * @{
 */
#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>

#include "sqlite3.h"

/**
 * @defgroup DB Database Structure
 * @{
 *
 * @brief Small explanation about the database structure.
 *
 * @dot
 * digraph example {
 *   fontname = "Bitstream Vera Sans"
 *   fontsize = 8
 *
 *   node [
 *     fontname = "Bitstream Vera Sans"
 *     fontsize = 8
 *     shape = "record"
 *   ]
 *
 *   edge [
 *     fontname = "Bitstream Vera Sans"
 *     fontsize = 8
 *     arrowhead = "none"
 *   ]
 *
 *   authors [ label="{authors|author : NUMERIC\lbook : NUMERIC\l}" ];
 *   author [ label="{author|key : NUMERIC\lname : TEXT\l}" ];
 *   book [ label="{book|key : NUMERIC\lpages : NUMERIC\llanguage : NUMERIC\ldescription : TEXT\lserie : NUMERIC\lpublisher : NUMERIC\ltitle : TEXT\lisbn : TEXT\lpublish_date : TEXT\lreaded : NUMERIC\ladded_date : TEXT\ltranslation : NUMERIC\lprint_version : NUMERIC\lformat : NUMERIC\lbuying_date : TEXT\lcomments : TEXT\lmy_favorit : NUMERIC\limage : TEXT\lrating : NUMERIC\l}" ];
 *   genre [ label="{genre|key : NUMERIC\lname : TEXT\l}" ];
 *   genres [ label="{genres|book : NUMERIC\lgenre : NUMERIC\l}" ];
 *   keyword [ label="{keyword|key : NUMERIC\lname : TEXT\l}" ];
 *   keywords [ label="{keywords|book : NUMERIC\lkeyword : NUMERIC\l}" ];
 *   languages [ label="{languages|key : NUMERIC\lname : TEXT\l}" ];
 *   publisher [ label="{publisher|key : NUMERIC\lname : TEXT\l}" ];
 *   serie [ label="{serie|key : NUMERIC\lname : TEXT\l}" ];
 *   mark [ label="{mark|key : NUMERIC\lname TEXT\l}" ];
 *   marks [ label="{marks|mark : NUMERIC\lbook : NUMERIC\l}" ];
 *   translator [ label="{translator|key : NUMERIC\lname : TEXT\l}" ];
 *   translators [ label="{translators|translator : NUMERIC\lbook : NUMERIC\l}" ];
 *   rent [ label="{rent|key : NUMERIC\luser : TEXT\lbook : NUMERIC\lrent_date : TEXT\lback_date : TEXT\l}" ];
 *
 *   author -> authors [ taillabel="key 1", headlabel="authors 1..*" ];
 *   genre -> genres [ taillabel="key 1", headlabel="genre 1..*" ];
 *   keyword -> keywords [ taillabel="key 1", headlabel="keyword 1..*" ];
 *   mark -> marks [ taillabel="key 1", headlabel="mark 1..*" ];
 *   translator -> translators [ taillabel="key 1", headlabel="translators 1..*" ];
 *   authors -> book [ taillabel="book 1..*", headlabel="" ];
 *   genres -> book [ taillabel="book 1..*", headlabel="" ];
 *   keywords -> book [ taillabel="book 1..*", headlabel="" ];
 *   translators -> book [ taillabel="book 1..*", headlabel=""  ];
 *   marks -> book [ taillabel="book 1..*", headlabel="" ];
 *
 *   book -> rent [ taillabel="key 1", headlabel="book 1" ];
 *   book -> languages [ taillabel="language 1", headlabel="key 1" ];
 *   book -> publisher [ taillabel="publisher 1", headlabel="key 1" ];
 *   book -> serie [ taillabel="serie 1", headlabel="key 1" ];
 * }
 * @enddot
 *
 * @}
 */

/**
 * @brief Enumerating table fields from db.
 *
 * Only for developing and make new cols to table easier.
 */
enum {
	DB_BOOK_KEY = 0,
	DB_BOOK_PAGES,
	DB_BOOK_LANGUAGE,
	DB_BOOK_DESCRIPTION,
	DB_BOOK_SERIE,
	DB_BOOK_PUBLISHER,
	DB_BOOK_TITLE,
	DB_BOOK_ISBN,
	DB_BOOK_PUBLISH_DATE,
	DB_BOOK_READED,
	DB_BOOK_ADDED_DATE,
	DB_BOOK_TRANSLATION,
	DB_BOOK_PRINT_VERSION,
	DB_BOOK_FORMAT,
	DB_BOOK_BUYING_DATE,
	DB_BOOK_COMMENTS,
	DB_BOOK_FAVORIT,
	DB_BOOK_IMAGE,
	DB_BOOK_RATING,
	DB_BOOK_SERIENO,
	DB_BOOK_COUNT,
};

/**
 * @brief Enumerating for QStringList fields for get the right translation.
 */
enum {
	BOOK_KIND_PAPERBACK,
	BOOK_KIND_HARDCOVER,
	BOOK_KIND_GRIDLEBOOK,
	BOOK_KIND_ONDEMAND,
	BOOK_KIND_SOFTCOVER,
	BOOK_KIND_E_BOOK,
	BOOK_KIND_FAKSIMILE,
	BOOK_KIND_CODEX,
	BOOK_KIND_LOOSELEAF,
	BOOK_KIND_MINIATURE,
	BOOK_KIND_CONCESSIONAL,
	BOOK_KIND_COUNT,
};

/**
 * @brief _book_kind holds Translateable strings for book art.
 */
extern QStringList _book_kind;

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
	QList<QString> getGenresOfBook(QString);
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
	QList<QString> getAllLanguages();
	QList<QString> getAllGenres();
	/**
	 * @brief Returns all authors listed by the database.
	 *
	 * This function is generally only for building up the overviewtree.
	 * @return Double-linked list of QStrings as result.
	 * @see query2LinkedLists(QString)
	 */
	QList<QString> getAllAuthors();
	QList<QList<QString> > getAllAuthorsWithKey();
	/**
	 * @brief Returns all authors of a book.
	 * @param bookkey Key from book->key.
	 * @return Linked list of QStrings as result, containing authors->key.
	 * @see queryLinkedList(QString)
	 */
	QList<QString> getAuthorsOfBook(QString);
	void removeAuthor(QString);
	void addAuthorToBook(QString);
	QList<QString> getAllPublishers();
	QList<QString> getAllCollections();
	QString getSerieNameFromKey(QString);
	QString getLanguageFromKey(QString);
	QString getPublisherFromKey(QString);
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
	/**
	 * @brief Helperfunction for inserting a value in database.
	 * @param sqlstatement Statement to query.
	 * @return False if data couldn't been set.
	 */
	bool queryInsert(QString);
	/**
	 * @brief Helperfunction for update an value in database.
	 * @param sqlstatement Statement to query.
	 * @return False if no fields are updated.
	 */
	bool queryUpdate(QString);
	/**
	 * @brief Helperfunction for deleting an value in database.
	 * @param sqlstatement Statement to query.
	 * @return False if no fields are deleted.
	 */
	bool queryDelete(QString);
};

/**
 * @brief Global library instance for getting everywhere infos.
 */
extern library *_library;


#endif // LIBRARY_H
/**
 * @}
 */
