#include "bookdescription.h"
#include "ui_bookdescription.h"

#include <QDebug>
#include <QComboBox>
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>

#include "../isbn.h"
#include "../library.h"
#include "../uihelpers.h"

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
	ui->groupBoxGenre->addToChooser(_library->getAllGenres());
	ui->groupBoxAuthors->addToChooser(_library->getAllAuthors());
	ui->comboBoxPublisher->addItems(_library->getAllPublishers());
	ui->comboBoxCollection->addItems(_library->getAllCollections());
}

bookdescription::bookdescription(QString bookkey, QWidget *parent) :
	QWidget(parent)
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

	this->Ratingbar->setRating(book[DB_BOOK_RATING].toInt());
	ui->lineEditPages->setText(book[DB_BOOK_PAGES]);
	ui->lineEditTitle->setText(book[DB_BOOK_TITLE]);
	ui->lineEditISBN->setText(book[DB_BOOK_ISBN]);

	ui->groupBoxAuthors->addToView(_library->getAuthorsOfBook(this->bookKey));
	ui->groupBoxGenre->addToView(_library->getGenresOfBook(this->bookKey));

	setComboBoxIndex(ui->comboBoxCollection,_library->getSerieNameFromKey(book[DB_BOOK_SERIE]));
	setComboBoxIndex(ui->comboBoxLanguage,_library->getLanguageFromKey(book[DB_BOOK_LANGUAGE]));
	setComboBoxIndex(ui->comboBoxPublisher,_library->getPublisherFromKey(book[DB_BOOK_PUBLISHER]));
}
