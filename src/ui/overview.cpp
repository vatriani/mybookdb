/**
 * @file overview.cpp
 * @brief Represents the collection overview.
 * @copyright
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author	Niels Neumann <vatriani.nn@googlemail.com>
 * @version 1.0
 */



#include "overview.h"
#include "ui_overview.h"

#include <QDebug>

#include "../library.h"

overview::overview(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::overview)
{
	ui->setupUi(this);
	ui->treeView->setStyleSheet("QTreeView::branch:has-children:!has-siblings:closed, QTreeView::branch:closed:has-children:has-siblings { border-image: none; image: url(:/toolbar/rightarrow.png); } QTreeView::branch:open:has-children:!has-siblings, QTreeView::branch:open:has-children:has-siblings  { border-image: none; image: url(:/toolbar/downarrow.png);}");

	this->ui->dockWidgetContents->setWindowFlags(Qt::SubWindow);

	this->listview = new QStandardItemModel(this);
	buildTree();
	this->ui->treeView->setModel(this->listview);

	QItemSelectionModel *selectionModel= this->ui->treeView->selectionModel();
	connect(selectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)),
			 this, SLOT(selectionChanged(const QModelIndex &, const QModelIndex &)));
}

overview::~overview()
{
	delete ui;
}

void overview::initialModel(QList<QList<QString> > tmp)
{

}

void overview::buildTree()
{
	QList<QList<QString> > tmp =_library->getAllAuthorsWithKey();
	QStandardItem *tmpItem[tmp.length()];

	for(int counter=0; counter<tmp.length(); counter++) {
		if(tmp[counter][0] != 0)
		{
			tmpItem[counter] = new QStandardItem(tmp[counter][0]);
			tmpItem[counter]->setIcon(QIcon(":/main/person.png"));

			QList<QString> tmpBooks = _library->getBooksFromAuthorKey(tmp[counter][1]);

			QStandardItem *tmpItemBooks[tmpBooks.length()];

			for(int counterB=0; counterB<tmpBooks.length(); counterB++) {
				if(tmpBooks[counter].length() != 0)
				{
					tmpItemBooks[counterB] = new QStandardItem(tmpBooks[counterB]);
					tmpItemBooks[counterB]->setIcon(QIcon(":/main/book.png"));
					tmpItem[counter]->appendRow(tmpItemBooks[counterB]);
				}
			}

			this->listview->appendRow(tmpItem[counter]);
		}
	}

	this->listview->sort(0);
}

void overview::selectionChanged(const QModelIndex &, const QModelIndex &)
{
	const QModelIndex index = ui->treeView->selectionModel()->currentIndex();
	QString selectedText = index.data(Qt::DisplayRole).toString();

	int hierarchyLevel=1;
	QModelIndex seekRoot = index;
	while(seekRoot.parent() != QModelIndex())
	{
		seekRoot = seekRoot.parent();
		hierarchyLevel++;
	}

	if(hierarchyLevel>1)
	{
		emit this->openBook(_library->getBookKeyByTitle(selectedText));
	}
}
