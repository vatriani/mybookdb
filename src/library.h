#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QString>
#include <QList>

#include "sqlite3.h"
#include "version.h"



class library : public QObject
{
	Q_OBJECT
public:
	explicit library(QObject *parent = 0);
	~library();

	bool open(QString filename);
	QList<QList<QString> > query(QString query);
	QList<QString> querySingle(QString query);
	void close();


	QList<QString> getBooksFromAuthor(QString author);
	QList<QString> getBooksFromSeries(QString serie);

private:
	sqlite3 *db;
};

extern library *_library;

#endif // LIBRARY_H
