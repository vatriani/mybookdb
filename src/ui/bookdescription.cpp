#include "bookdescription.h"
#include "ui_bookdescription.h"

#include <QDebug>
#include <QComboBox>
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>

#include "../isbn.h"
#include "../library.h"

bookdescription::bookdescription(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::bookdescription)
{
	ui->setupUi(this);
	connect(this->ui->lineEditISBN,SIGNAL(textChanged(QString)),this,SLOT(inputIsbn(QString)));
	connect(this->ui->lineEditISBN,SIGNAL(editingFinished()),this,SLOT(resetIsbn()));

	this->Ratingbar = new ratingbar(this);
	ui->gridLayout_2->addWidget(this->Ratingbar,2,1);

	ui->comboBoxLanguage->addItems(_library->getAllLanguages());
	ui->comboBoxGenre->addItems(_library->getAllGenres());
	ui->comboBoxAuthors->addItems(_library->getAllAuthors());
	ui->comboBoxPublisher->addItems(_library->getAllPublishers());
	ui->comboBoxCollection->addItems(_library->getAllCollections());
}

bookdescription::bookdescription(QString bookkey, QWidget *parent) :
	bookdescription(parent)
{
	openBook(bookkey);
}

bookdescription::~bookdescription()
{
	delete ui;
}

void bookdescription::inputIsbn(QString tmp)
{
	if(tmp.length()!=0)
	{
		isbn Validator((char*)tmp.toStdString().c_str());
		if(!Validator.isValid())
			this->ui->lineEditISBN->setStyleSheet("color:#FF0000");
		else
			this->ui->lineEditISBN->setStyleSheet("");
	}
	else
		ui->lineEditISBN->setStyleSheet("");
}

void bookdescription::resetIsbn()
{
	if(ui->lineEditISBN->text().length()!=0)
	{
		isbn Validator((char*)this->ui->lineEditISBN->text().toStdString().c_str());
		if(Validator.isValid())
			this->ui->lineEditISBN->setText(Validator.getIsbn());
	}
}

void bookdescription::isbnScanner(QString tmp)
{
	this->ui->lineEditISBN->setText(tmp);
}

/**
 * @brief bookdescription::openBook
 * language, description, serie, publisher, title, isbn, key
 * @param key Bookkey
 */
void bookdescription::openBook(QString key)
{
	this->bookKey=key;
	QList<QString> book = _library->getFullBookByKey(this->bookKey);

	this->Ratingbar->setRating(book[0].toInt());
	ui->lineEditPages->setText(book[1]);
	ui->lineEditTitle->setText(book[6]);
	ui->lineEditISBN->setText(book[7]);

	ui->listViewAuthors->setModel(this->getItemModelFromList(_library->getAuthorsOfBook(this->bookKey)));
	ui->listViewGenre->setModel(this->getItemModelFromList(_library->getGenresOfBook(this->bookKey)));


	//ui->comboBoxCollection->findData(_library->getSerieNameFromKey(book[4]));
	setComboBoxIndex(ui->comboBoxCollection,_library->getSerieNameFromKey(book[4]));
	setComboBoxIndex(ui->comboBoxLanguage,_library->getLanguageFromKey(book[2]));
	setComboBoxIndex(ui->comboBoxPublisher,_library->getPublisherFromKey(book[5]));
}

QStandardItemModel *bookdescription::getItemModelFromList(QList<QString> list)
{
	QStandardItemModel *model = new QStandardItemModel();
	QStandardItem *tmpItem[list.length()];

	for(int counter = 0; counter < list.length(); counter++)
	{
		tmpItem[counter] = new QStandardItem(list[counter]);
		model->appendRow(tmpItem[counter]);
	}

	return model;
}

void bookdescription::setComboBoxIndex(QComboBox *box, QString string)
{
	box->setCurrentIndex(box->findText(string));
}
