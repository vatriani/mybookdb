/**
 * @file library.cpp
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
	querySingle("CREATE TABLE IF NOT EXISTS authors (author NUMERIC, book NUMERIC);");
	querySingle("CREATE TABLE IF NOT EXISTS author (key INTEGER PRIMARY KEY, name TEXT);");
	querySingle("CREATE UNIQUE INDEX IF NOT EXISTS author_index ON author(name ASC);");
	querySingle("CREATE TABLE IF NOT EXISTS book (key INTEGER PRIMARY KEY, pages NUMERIC, language NUMERIC, description TEXT, serie NUMERIC, publisher NUMERIC, title TEXT, isbn TEXT, publish_date TEXT, readed NUMERIC, added_date TEXT, translation NUMERIC, print_version NUMERIC, format NUMERIC, buying_date TEXT, comments TEXT, my_favorit NUMERIC);");
	querySingle("CREATE TABLE IF NOT EXISTS genre (key INTEGER PRIMARY KEY, name TEXT);");
	querySingle("CREATE UNIQUE INDEX IF NOT EXISTS genre_index ON genre(name ASC);");
	querySingle("CREATE TABLE IF NOT EXISTS genres (book NUMERIC, genre NUMERIC);");
	querySingle("CREATE TABLE IF NOT EXISTS keywords (keyword NUMERIC, book NUMERIC);");
	querySingle("CREATE TABLE IF NOT EXISTS keyword (key INTEGER PRIMARY KEY, name TEXT);");
	querySingle("CREATE UNIQUE INDEX IF NOT EXISTS keyword_index ON keyword(name ASC);");
	querySingle("CREATE TABLE IF NOT EXISTS language (key INTEGER PRIMARY KEY, name TEXT);");
	querySingle("CREATE UNIQUE INDEX IF NOT EXISTS languages_index ON language(name ASC);");
	querySingle("CREATE TABLE IF NOT EXISTS publisher (key INTEGER PRIMARY KEY, name TEXT);");
	querySingle("CREATE UNIQUE INDEX IF NOT EXISTS publisher_index ON publisher(name ASC);");
	querySingle("CREATE TABLE IF NOT EXISTS serie (key INTEGER PRIMARY KEY, name TEXT);");
	querySingle("CREATE UNIQUE INDEX IF NOT EXISTS serie_index ON serie(name ASC);");
	querySingle("CREATE TABLE IF NOT EXISTS marks (mark NUMERIC, book NUMERIC);");
	querySingle("CREATE TABLE IF NOT EXISTS mark (key INTEGER PRIMARY KEY, name TEXT);");
	querySingle("CREATE UNIQUE INDEX IF NOT EXISTS mark_index ON mark(name ASC);");
	querySingle("CREATE TABLE IF NOT EXISTS translators (translator NUMERIC, book NUMERIC);");
	querySingle("CREATE TABLE IF NOT EXISTS translator (key INTEGER PRIMARY KEY, name TEXT);");
	querySingle("CREATE UNIQUE INDEX IF NOT EXISTS translator_index ON translator(name ASC);");
	querySingle("CREATE TABLE IF NOT EXISTS rent (key INTEGER PRIMARY KEY, user TEXT, book NUMERIC, rent_date TEXT, back_date TEXT);");
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
	QString booktitle = "SELECT book.title FROM book JOIN authors ON authors.book = book.key WHERE authors.author LIKE '";
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
	QString bookQuery ="SELECT author.name FROM author JOIN authors ON author.key = authors.author WHERE authors.book LIKE '";
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
	return this->queryLinkedList("SELECT name FROM language;");
}

QList<QString> library::getAllGenres()
{
	return this->queryLinkedList("SELECT name FROM genre;");
}

QList<QString> library::getAllAuthors()
{
	return this->queryLinkedList("SELECT name FROM author;");
}

QList<QList<QString> > library::getAllAuthorsWithKey()
{
	return this->query2LinkedLists("SELECT * FROM author;");
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
	QString bookKey = "SELECT name FROM language WHERE key LIKE '";
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
