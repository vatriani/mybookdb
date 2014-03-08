/**
 * @file library.cpp
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



#include "library.h"
#include "version.h"


#include <QSettings>
#include <QMessageBox>
#include <QDebug>
#include <QList>

#include <iostream>
#include <vector>



library *_library = NULL;

library::library(QObject *parent) :
	QObject(parent)
{
	QSettings settings(APP_NAME,APP_CONFIG);
	QString dbFile = settings.fileName();
	dbFile.chop(strlen(APP_CONFIG)+5);
	dbFile.append("database");

	QByteArray string = dbFile.toLocal8Bit();

	this->open(string.data());
	querySingle("CREATE TABLE IF NOT EXISTS author (authors NUMERIC, book NUMERIC);");
	querySingle("CREATE TABLE IF NOT EXISTS authors (name TEXT UNIQUE, key INTEGER PRIMARY KEY);");
	querySingle("CREATE TABLE IF NOT EXISTS book (pages NUMERIC, language NUMERIC, description TEXT, serie NUMERIC, publisher NUMERIC, title TEXT, isbn TEXT, key INTEGER PRIMARY KEY);");
	querySingle("CREATE TABLE IF NOT EXISTS genre (key INTEGER PRIMARY KEY, name TEXT UNIQUE);");
	querySingle("CREATE TABLE IF NOT EXISTS genres (book NUMERIC, genre NUMERIC);");
	querySingle("CREATE TABLE IF NOT EXISTS keyword (keywords NUMERIC, book NUMERIC);");
	querySingle("CREATE TABLE IF NOT EXISTS keywords (key INTEGER PRIMARY KEY, name TEXT UNIQUE);");
	querySingle("CREATE TABLE IF NOT EXISTS languages (key INTEGER PRIMARY KEY, name TEXT UNIQUE);");
	querySingle("CREATE TABLE IF NOT EXISTS publisher (key INTEGER PRIMARY KEY, name TEXT UNIQUE);");
	querySingle("CREATE TABLE IF NOT EXISTS serie (key INTEGER PRIMARY KEY, name TEXT UNIQUE);");
}

library::~library()
{
	this->close();
}



bool library::open(QString filename)
{
	if(sqlite3_open(filename.toLocal8Bit(), &this->db) == SQLITE_OK)
		return true;

	return false;
}

QList<QList<QString> > library::query2LinkedLists(QString query)
{
	sqlite3_stmt *statement;
	QList<QList<QString> > results;

	if(sqlite3_prepare_v2(this->db, query.toLocal8Bit(), -1, &statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while(true)
		{
			result = sqlite3_step(statement);

			if(result == SQLITE_ROW)
			{
				QList<QString> values;
				for(int col = 0; col < cols; col++)
					values.push_back((char*)sqlite3_column_text(statement, col));
				results.push_back(values);
			}
			else
				break;
		}

		sqlite3_finalize(statement);
	}

	QString error = QString(sqlite3_errmsg(this->db));
	if(error != "not an error")qDebug() << error;

	return results;
}

QList<QString> library::queryLinkedList(QString query)
{
	sqlite3_stmt *statement;
	QList<QString> results;

	if(sqlite3_prepare_v2(this->db, query.toLocal8Bit(), -1, &statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while(true)
		{
			result = sqlite3_step(statement);

			if(result == SQLITE_ROW)
				for(int counter = 0; counter<cols;counter++)
					results.push_back(QString((char*)sqlite3_column_text(statement, counter)));
			else
				break;
		}

		sqlite3_finalize(statement);
	}

	QString error = QString(sqlite3_errmsg(this->db));
	if(error != "not an error")qDebug() << error;

	return results;
}
/**
 * @todo remove unused variable cols
 */
QString library::querySingle(QString query)
{
	sqlite3_stmt *statement;
	QString results;

	if(sqlite3_prepare_v2(this->db, query.toLocal8Bit(), -1, &statement, 0) == SQLITE_OK)
	{
		int cols = sqlite3_column_count(statement);
		int result = 0;
		while(true)
		{
			result = sqlite3_step(statement);

			if(result == SQLITE_ROW)
					results=(QString((char*)sqlite3_column_text(statement, 0)));
			else
				break;
		}

		sqlite3_finalize(statement);
	}

	QString error = QString(sqlite3_errmsg(this->db));
	if(error != "not an error")qDebug() << error;

	return results;
}

bool library::queryInsert(QString)
{
	/** @todo Needs implementation */
}

bool library::queryUpdate(QString)
{
	/** @todo Needs implementation */
}

bool library::queryDelete(QString)
{
	/** @todo Needs implementation */
}

void library::close()
{
	sqlite3_close(this->db);
}



QList<QString> library::getBooksFromAuthorKey(QString authorKey)
{
	QString booktitle = "SELECT book.title FROM book JOIN author ON author.book = book.key WHERE author.authors LIKE '";
	booktitle.append(authorKey);
	booktitle.append("' ORDER BY book.title;");
	return this->queryLinkedList(booktitle);
}

QList<QString> library::getBooksFromSeries(QString serie)
{
	/** @todo Needs implementation */
}

QList<QString> library::getAuthorsOfBook(QString bookKey)
{
	QString bookQuery ="SELECT authors.name FROM authors JOIN author ON authors.key = author.authors WHERE author.book LIKE '";
	bookQuery.append(bookKey);
	bookQuery.append("';");

	return this->queryLinkedList(bookQuery);
}

void library::removeAuthor(QString authorText)
{
	QString query ="'";
	query.append(authorText);
	query.append("';");

	this->queryDelete(query);
}

void library::addAuthorToBook(QString)
{
	/** @todo Needs implementation */
}

QList<QString> library::getGenresOfBook(QString bookKey)
{
	QString bookQuery ="SELECT genre.name FROM genre JOIN genres ON genre.key = genres.genre WHERE genres.book LIKE '";
	bookQuery.append(bookKey);
	bookQuery.append("';");

	return this->queryLinkedList(bookQuery);
}

QList<QString> library::getFullBookByKey(QString key)
{
	QString bookQuery = "SELECT * FROM book WHERE book.key LIKE '";
	bookQuery.append(key);
	bookQuery.append("';");

	return this->queryLinkedList(bookQuery);
}

QString library::getBookKeyByTitle(QString title)
{
	QString bookKey = "SELECT book.key FROM book WHERE book.title LIKE '";
	bookKey.append(title);
	bookKey.append("';");
	return this->querySingle(bookKey);
}

QList<QString> library::getAllLanguages()
{
	return this->queryLinkedList("SELECT name FROM languages;");
}

QList<QString> library::getAllGenres()
{
	return this->queryLinkedList("SELECT name FROM genre;");
}

QList<QString> library::getAllAuthors()
{
	return this->queryLinkedList("SELECT name FROM authors;");
}

QList<QList<QString> > library::getAllAuthorsWithKey()
{
	return this->query2LinkedLists("SELECT * FROM authors;");
}

QList<QString> library::getAllPublishers()
{
	return this->queryLinkedList("SELECT name FROM publisher;");
}

QList<QString> library::getAllCollections()
{
	return this->queryLinkedList("SELECT name from serie;");
}

QString library::getSerieNameFromKey(QString key)
{
	QString bookKey = "SELECT name FROM serie WHERE key LIKE '";
	bookKey.append(key);
	bookKey.append("';");
	return this->querySingle(bookKey);
}

QString library::getLanguageFromKey(QString key)
{
	QString bookKey = "SELECT name FROM languages WHERE key LIKE '";
	bookKey.append(key);
	bookKey.append("';");
	return this->querySingle(bookKey);
}

QString library::getPublisherFromKey(QString key)
{
	QString bookKey = "SELECT name FROM publisher WHERE key LIKE '";
	bookKey.append(key);
	bookKey.append("';");
	return this->querySingle(bookKey);
}
