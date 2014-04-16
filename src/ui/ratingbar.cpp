/**
 * @file ratingbar.cpp
 * @brief Own widget with 10 stars to represent rating of a book.
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
	this->iconSize=18;
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

void ratingbar::setRating(int rating)
{
	this->rating = rating;
	changeRating();
}

void ratingbar::setImageSize(int size)
{
	this->iconSize = size;

	changeRating();
}


void ratingbar::changeRating()
{
	QIcon* starOff = new QIcon(":/toolbar/star_off.png");
	QIcon* starOn = new QIcon(":/toolbar/star_on.png");

	/** @todo Adding fallback stars  from theme */
	/*if(starOff == NULL && starON == NULL)
	{

	}
*/
	for(int counter = 0; counter < 10; counter++)
	{
		if(counter+1 <= this->rating)
			this->stars[counter]->setPixmap(starOn->pixmap(QSize(this->iconSize,this->iconSize)));
		else
			this->stars[counter]->setPixmap(starOff->pixmap(QSize(this->iconSize,this->iconSize)));
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
