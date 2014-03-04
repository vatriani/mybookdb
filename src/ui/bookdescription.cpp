#include "bookdescription.h"
#include "ui_bookdescription.h"

#include <QDebug>

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

	ui->lineEditPages->setText(book[0]);
	ui->lineEditTitle->setText(book[7]);
	ui->lineEditISBN->setText(book[8]);


	QList<QString> author = _library->getAuthorsOfBook(this->bookKey);
	/*while(bookQuery.length())
	{

	}
*/
	qDebug() << book;
	qDebug() << author;
}
