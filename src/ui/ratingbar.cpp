#include "ratingbar.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPicture>
#include <QIcon>
#include <QDebug>
#include <QMouseEvent>

ratingbar::ratingbar(QWidget *parent) :
	QWidget(parent)
{
	this->rating=0;
	this->createUi();
	this->setToolTip("Change with mousewheel");
}

ratingbar::~ratingbar()
{
	for(int counter = 0; counter < 10; counter++)
		delete this->stars[counter];
}

int ratingbar::getRating()
{
	return this->rating;
}

void ratingbar::changeRating()
{
	QIcon* starOff = new QIcon(":/toolbar/star_off.png");
	QIcon* starOn = new QIcon(":/toolbar/star_on.png");

	for(int counter = 1; counter < 10; counter++)
	{
		if(counter<=this->rating)
			this->stars[counter]->setPixmap(starOn->pixmap(QSize(18,18)));
		else
			this->stars[counter]->setPixmap(starOff->pixmap(QSize(18,18)));
	}
}

void ratingbar::wheelEvent(QWheelEvent *event)
{
	QPoint numDegrees = event->angleDelta() / 8;

	if(!numDegrees.isNull()) {
		QPoint numSteps = numDegrees / 15;
		if(numSteps.y() < 0 && this->rating != 0)
			this->rating--;
		if(numSteps.y() > 0 && this->rating < 10)
			this->rating++;
		this->changeRating();
	}

	event->accept();
}

void ratingbar::createUi()
{
	QHBoxLayout *layout=new QHBoxLayout;
	layout->setSpacing(2);
	layout->setMargin(0);

	for(int counter = 0; counter < 10; counter++)
	{
		this->stars[counter] = new QLabel(this);
		layout->addWidget(this->stars[counter]);
	}
	layout->addStretch();
	this->setLayout(layout);
	this->changeRating();
}
