#ifndef RATINGBAR_H
#define RATINGBAR_H

#include <QWidget>
#include <QLabel>

class ratingbar : public QWidget
{
	Q_OBJECT
public:
	explicit ratingbar(QWidget *parent = 0);
	~ratingbar();

signals:

public slots:

private:
	void createUi();

	QLabel *stars[10];

};

#endif // RATINGBAR_H
