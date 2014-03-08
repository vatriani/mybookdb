/**
 * @file overview.h
 * @brief Represents the collection overview.
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



#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <QDockWidget>
#include <QStandardItemModel>
#include <QItemSelection>

namespace Ui {
class overview;
}

class overview : public QDockWidget
{
	Q_OBJECT

public:
	explicit overview(QWidget *parent = 0);
	~overview();

	void buildTree();

signals:
	void openBook(QString key);

public slots:
	void initialModel(QList<QList<QString> > tmp);
	void selectionChanged(const QModelIndex &, const QModelIndex &);

private:
	Ui::overview *ui;

	QStandardItemModel *listview;
};

#endif // OVERVIEW_H
