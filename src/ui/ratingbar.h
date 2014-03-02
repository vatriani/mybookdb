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
	void changeRating();

protected:
	void wheelEvent(QWheelEvent *event);

private:
	void createUi();

	QLabel *stars[10];
	unsigned int rating;
};

#endif // RATINGBAR_H
