/**
 * @file groupboxcollapse.cpp
 * @brief Define a collapseable groupbox widget.
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

