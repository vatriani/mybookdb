/**
 * @file bookdescription.h
 * @brief
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

#ifndef BOOKDESCRIPTION_H
#define BOOKDESCRIPTION_H

#include <QWidget>
#include <QString>
#include <QStandardItemModel>
#include <QList>
#include <QComboBox>


#include "ratingbar.h"

namespace Ui {
class bookdescription;
}

class bookdescription : public QWidget
{
	Q_OBJECT

public:
	explicit bookdescription(QWidget *parent = 0);
	bookdescription(QString, QWidget *parent = 0);
	~bookdescription();

public slots:
	void inputIsbn(QString);
	void resetIsbn();
	void isbnScanner(QString);

	void openBook(QString);

private:
	Ui::bookdescription *ui;
	QString bookKey;

	ratingbar *Ratingbar;
	QStandardItemModel *getItemModelFromList(QList<QString>);
	void setComboBoxIndex(QComboBox*,QString);
};

#endif // BOOKDESCRIPTION_H
