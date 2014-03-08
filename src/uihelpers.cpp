/**
 * @file uihelpers.cpp
 * @brief Some useful functions for better gui handling.
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



#include "uihelpers.h"

QStandardItemModel *getItemModelFromList(QList<QString> list)
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

void setComboBoxIndex(QComboBox *box, QString string)
{
	box->setCurrentIndex(box->findText(string));
}
