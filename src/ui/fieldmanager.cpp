#include "fieldmanager.h"

#include "../uihelpers.h"

fieldManager::fieldManager(QWidget *parent) :
	groupBoxCollapse(parent)
{
	this->model = NULL;

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

	connect(this->ButtonAdd,SIGNAL(clicked()),this,SLOT(addButtonClicked()));
	connect(this->ButtonNew,SIGNAL(clicked()),this,SLOT(newButtonClicked()));
	connect(this->ButtonRemove,SIGNAL(clicked()),this,SLOT(removeButtonClicked()));
}

void fieldManager::addToChooser(QList<QString> tmpList)
{
	this->ComboBoxChooser->addItems(tmpList);
}

void fieldManager::addToView(QList<QString> tmpList)
{
	if(this->model != NULL)
		delete this->model;
	this->model=new QStandardItemModel(getItemModelFromList(tmpList));
	this->ListView->setModel(this->model);
}

void fieldManager::addButtonClicked()
{
	QStandardItem *tmp = new QStandardItem(this->ComboBoxChooser->currentText());
	this->model->appendRow(tmp);
	delete tmp;
}

void fieldManager::removeButtonClicked()
{

}

void fieldManager::newButtonClicked()
{

}

void fieldManager::chooserComboBoxCommit()
{

}

void fieldManager::expand()
{
	this->ListView->setVisible(true);
	this->ButtonAdd->setVisible(true);
	this->ButtonNew->setVisible(true);
	this->ButtonRemove->setVisible(true);
	this->ComboBoxChooser->setVisible(true);
}

void fieldManager::collapse()
{
	this->ListView->setVisible(false);
	this->ButtonAdd->setVisible(false);
	this->ButtonNew->setVisible(false);
	this->ButtonRemove->setVisible(false);
	this->ComboBoxChooser->setVisible(false);
}
