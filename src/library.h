#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QString>
#include <QList>

#include "sqlite3.h"
#include "version.h"



/**
 * Handles db querys and db connection
 * @brief The library class
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
	sqlite3 *db /** handles database connection*/;
};

/**
 * @brief _library
 */
extern library *_library;

#endif // LIBRARY_H
