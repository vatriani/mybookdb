#ifndef ENTRY_H
#define ENTRY_H

#include <QObject>
#include <QString>
#include <QList>

class entry : public QObject
{
	Q_OBJECT
public:
	explicit entry(QObject *parent = 0);

	QString Title;
	QList<QString> Autors;
	enum Binding {HARBACK,PAPERBACK,TRADE_PAPERBACK,E_BOOK,MAGAZINE,JOURNAL};
	QString Publisher;
	QString Edition;
	QString Copyright_Year;
	QString Publication_Year;
	QString ISBN;
	QList<QString> Genre;
	QList<QString> Keywords;
	QString Cover;
	QString Comment;
	unsigned short int Rating;

signals:

public slots:

};

#endif // ENTRY_H
