#include "overview.h"
#include "ui_overview.h"

#include <QDebug>

#include "../library.h"

overview::overview(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::overview)
{
	ui->setupUi(this);

	ui->tab->setWindowIcon(QIcon());
	ui->tab_2->setWindowIcon(QIcon(":/toolbar/filter.png"));
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
		tmpItem[counter] = new QStandardItem(tmp[counter][0]);
		tmpItem[counter]->setIcon(QIcon(":/main/person.png"));

		QList<QString> tmpBooks = _library->getBooksFromAuthorKey(tmp[counter][1]);

		QStandardItem *tmpItemBooks[tmpBooks.length()];

		for(int counterB=0; counterB<tmpBooks.length(); counterB++) {
			tmpItemBooks[counterB] = new QStandardItem(tmpBooks[counterB]);
			tmpItemBooks[counterB]->setIcon(QIcon(":/main/book.png"));
			tmpItem[counter]->appendRow(tmpItemBooks[counterB]);
		}

		this->listview->appendRow(tmpItem[counter]);
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
