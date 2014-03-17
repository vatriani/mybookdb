/**
 * @file bookdescription.cpp
 * @brief Gui widget for displaying and editing book details.
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
#include "../imagestore.h"

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
	ui->comboBoxFormat->addItems(_book_kind);
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

	QPixmap *cover = _imagestore->getImageFromKey(book[DB_BOOK_TITLE],book[DB_BOOK_ISBN]);
	if(cover != NULL)
		ui->Cover->setPixmap(*cover);
}

void bookdescription::addAuthor(QString)
{
	/** @todo Needs implementation */
}

void bookdescription::removeAuthor(QString)
{
	/** @todo Needs implementation */
}

void bookdescription::addGenre(QString)
{
	/** @todo Needs implementation */
}

void bookdescription::removeGenre(QString)
{
	/** @todo Needs implementation */
}

void bookdescription::addKeyword(QString)
{
	/** @todo Needs implementation */
}

void bookdescription::removeKeyword(QString)
{
	/** @todo Needs implementation */
}
