#include "groupboxcollapse.h"

groupBoxCollapse::groupBoxCollapse(QWidget *parent) :
	QGroupBox(parent)
{
	this->setCheckable(true);
	this->isCollapse = false;

	change();
}

void groupBoxCollapse::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		this->isCollapse = !this->isCollapse;
		change();
	}
	event->accept();
}

void groupBoxCollapse::change()
{
	if(this->isCollapse)
	{
		collapse();
		this->setStyleSheet("QGroupBox::indicator:checked { image: url(:/toolbar/rightarrow.png); } QGroupBox { border: 0px; border-radius: 0px; }");
	}
	else
	{
		expand();
		this->setStyleSheet("QGroupBox::indicator:checked { image: url(:/toolbar/downarrow.png); }");
	}
}

void groupBoxCollapse::expand()
{

}

void groupBoxCollapse::collapse()
{

}

