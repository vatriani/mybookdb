/**
 * @file fieldmanager.cpp
 * @brief Gui widget to display a QListView with editing options.
 *
 * Editing is provided by choosing an value or enter a new one over QComboBox
 * and clicking on the add Button. To remove an entry, select the value in
 * ListView and clicking the remove Button.
 *
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



#include "fieldmanager.h"

#include "../uihelpers.h"

#include <QDebug>

fieldManager::fieldManager(QWidget *parent) :
	groupBoxCollapse(parent)
{
	this->itemModel = NULL;

	this->LayoutVertical = new QVBoxLayout(this);
	this->LayoutHorizontal = new QHBoxLayout();
	this->HorizontalSpacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);
	this->ListView = new QListView(this);
	this->ButtonAdd = new QPushButton(tr("add"),this);
	this->ButtonAdd->setIcon(QIcon(":/toolbar/edit_add.png"));
	this->ButtonRemove = new QPushButton(tr("remove"),this);
	this->ButtonRemove->setIcon(QIcon(":/toolbar/editdelete.png"));
	this->ComboBoxChooser = new QComboBox(this);
	this->ComboBoxChooser->setEditable(true);

	this->LayoutHorizontal->addWidget(this->ComboBoxChooser);
	this->LayoutHorizontal->addSpacerItem(this->HorizontalSpacer);
	this->LayoutHorizontal->addWidget(this->ButtonAdd);
	this->LayoutHorizontal->addWidget(this->ButtonRemove);

	this->LayoutVertical->addWidget(this->ListView);
	this->LayoutVertical->addLayout(LayoutHorizontal);

	connect(this->ButtonAdd,SIGNAL(clicked()),this,SLOT(addButtonClicked()));
	connect(this->ButtonRemove,SIGNAL(clicked()),this,SLOT(removeButtonClicked()));
}

fieldManager::~fieldManager()
{

	delete this->ComboBoxChooser;
	delete this->ButtonAdd;
	delete this->ButtonRemove;
	if(this->itemModel != NULL)
		delete this->itemModel;
	delete this->ListView;
	delete this->LayoutHorizontal;
	delete this->LayoutVertical;
}

void fieldManager::addToChooser(QList<QString> tmpList)
{
	this->ComboBoxChooser->addItems(tmpList);
}

void fieldManager::addToView(QList<QString> tmpList)
{
	if(this->itemModel != NULL)
	{
		this->ListView->setModel(NULL);
		delete this->itemModel;
		this->itemModel = NULL;
	}

	this->itemModel = getItemModelFromList(tmpList);
	this->ListView->setModel(this->itemModel);
}

void fieldManager::addButtonClicked()
{
	if(this->itemModel == NULL)
	{
		this->itemModel = new QStandardItemModel();
		this->ListView->setModel(this->itemModel);
	}

	QStandardItem *tmp = new QStandardItem(this->ComboBoxChooser->currentText());
	this->itemModel->appendRow(tmp);

	emit this->valueAdded(this->ComboBoxChooser->currentText());
}

void fieldManager::removeButtonClicked()
{
	QItemSelectionModel *selectionModel = this->ListView->selectionModel();
	QModelIndexList indexes = selectionModel->selectedIndexes();
	QModelIndex index;

	foreach(index, indexes)
	{
		emit this->valueRemoved(this->itemModel->data(index).toString());
		this->itemModel->removeRow(index.row());
	}
}

void fieldManager::expand()
{
	this->ListView->setVisible(true);
	this->ButtonAdd->setVisible(true);
	this->ButtonRemove->setVisible(true);
	this->ComboBoxChooser->setVisible(true);
}

void fieldManager::collapse()
{
	this->ListView->setVisible(false);
	this->ButtonAdd->setVisible(false);
	this->ButtonRemove->setVisible(false);
	this->ComboBoxChooser->setVisible(false);
}
