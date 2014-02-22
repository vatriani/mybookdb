#include "ratingbar.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPicture>
#include <QIcon>
#include <QDebug>

ratingbar::ratingbar(QWidget *parent) :
	QWidget(parent)
{
	this->createUi();
}

ratingbar::~ratingbar()
{
	for(int counter = 0; counter < 10; counter++)
		delete this->stars[counter];
}

void ratingbar::createUi()
{
	QHBoxLayout *layout=new QHBoxLayout;
	layout->setSpacing(2);
	layout->setMargin(0);

	QIcon* starOff = new QIcon(":/toolbar/star_off.png");

	for(int counter = 0; counter < 10; counter++)
	{
		this->stars[counter] = new QLabel(this);
		this->stars[counter]->setPixmap(starOff->pixmap(QSize(18,18)));
		layout->addWidget(this->stars[counter]);
	}

	this->setLayout(layout);
}
