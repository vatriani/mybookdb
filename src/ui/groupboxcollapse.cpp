#include "groupboxcollapse.h"

#include "../uihelpers.h"

groupBoxCollapse::groupBoxCollapse(QWidget *parent) :
	QGroupBox(parent)
{
	this->setCheckable(true);
	this->isCollapse = false;

	this->LayoutVertical = new QVBoxLayout(this);
	this->LayoutHorizontal = new QHBoxLayout();
	this->HorizontalSpacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
	this->ListView = new QListView(this);
	this->ButtonAdd = new QPushButton(tr("add"),this);
	this->ButtonRemove = new QPushButton(tr("remove"),this);
	this->ButtonNew = new QPushButton(tr("new"),this);
	this->ComboBoxChooser = new QComboBox(this);

	this->LayoutHorizontal->addWidget(this->ComboBoxChooser);
	this->LayoutHorizontal->addWidget(this->ButtonAdd);
	this->LayoutHorizontal->addWidget(this->ButtonRemove);
	this->LayoutHorizontal->addSpacerItem(this->HorizontalSpacer);
	this->LayoutHorizontal->addWidget(this->ButtonNew);

	this->LayoutVertical->addWidget(this->ListView);
	this->LayoutVertical->addLayout(LayoutHorizontal);

	collapse();
}

void groupBoxCollapse::addToChooser(QList<QString> tmpList)
{
	this->ComboBoxChooser->addItems(tmpList);
}

void groupBoxCollapse::addToView(QList<QString> tmpList)
{
	this->ListView->setModel(getItemModelFromList(tmpList));
}

void groupBoxCollapse::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		this->isCollapse = !this->isCollapse;
		collapse();
	}
	event->accept();
}

void groupBoxCollapse::collapse()
{
	if(this->isCollapse)
	{
		this->ListView->setVisible(false);
		this->ButtonAdd->setVisible(false);
		this->ButtonNew->setVisible(false);
		this->ButtonRemove->setVisible(false);
		this->ComboBoxChooser->setVisible(false);
		this->setStyleSheet("QGroupBox::indicator { width: 13px; height: 13px; } QGroupBox::indicator:checked { image: url(:/toolbar/rightarrow.png); } QGroupBox { border: 0px; border-radius: 0px; }");
	}
	else
	{
		this->ListView->setVisible(true);
		this->ButtonAdd->setVisible(true);
		this->ButtonNew->setVisible(true);
		this->ButtonRemove->setVisible(true);
		this->ComboBoxChooser->setVisible(true);
		this->setStyleSheet("QGroupBox::indicator { width: 13px; height: 13px; } QGroupBox::indicator:checked { image: url(:/toolbar/downarrow.png); }");
		this->repaint();
	}
}
