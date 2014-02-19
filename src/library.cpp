#include "library.h"

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
	query("CREATE TABLE IF NOT EXISTS author (authors NUMERIC, book NUMERIC);");
	query("CREATE TABLE IF NOT EXISTS authors (name TEXT, key INTEGER PRIMARY KEY);");
	query("CREATE TABLE IF NOT EXISTS book (language NUMERIC, description TEXT, serie NUMERIC, publisher NUMERIC, title TEXT, isbn TEXT, key INTEGER PRIMARY KEY);");
	query("CREATE TABLE IF NOT EXISTS genre (key INTEGER PRIMARY KEY, name TEXT);");
	query("CREATE TABLE IF NOT EXISTS genres (book NUMERIC, genre NUMERIC);");
	query("CREATE TABLE IF NOT EXISTS keyword (keywords NUMERIC, book NUMERIC);");
	query("CREATE TABLE IF NOT EXISTS keywords (key INTEGER PRIMARY KEY, name TEXT);");
	query("CREATE TABLE IF NOT EXISTS languages (key INTEGER PRIMARY KEY, name TEXT);");
	query("CREATE TABLE IF NOT EXISTS publisher (key INTEGER PRIMARY KEY, name TEXT);");
	query("CREATE TABLE IF NOT EXISTS serie (key INTEGER PRIMARY KEY, name TEXT);");
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


QList<QList<QString> > library::query(QString query)
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

QList<QString> library::querySingle(QString query)
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



void library::close()
{
	sqlite3_close(this->db);
}

QList<QString> library::getBooksFromAuthor(QString author)
{

}

QList<QString> library::getBooksFromSeries(QString serie)
{

}
