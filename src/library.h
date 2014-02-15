#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>


class library : public QObject
{
	Q_OBJECT
public:
	explicit library(QObject *parent = 0);

signals:

public slots:

private:
	QSqlDatabase db;

};

#endif // LIBRARY_H
