/**
 * @file fieldmanager.h
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



#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H

#include <QList>
#include <QString>
#include <QPushButton>
#include <QListView>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardItemModel>

#include "groupboxcollapse.h"



/**
 * @brief Gui widget to display a QListView with editing options.
 *
 * Editing is provided by choosing an value or enter a new one over QComboBox
 * and clicking on the add Button. To remove an entry, select the value in
 * ListView and clicking the remove Button.
 */
class fieldManager : public groupBoxCollapse
{
	Q_OBJECT
public:
	explicit fieldManager(QWidget *parent = 0);
	~fieldManager();

	void addToChooser(QList<QString>);
	void addToView(QList<QString>);

signals:
	void valueAdded(QString);
	void valueRemoved(QString);

private slots:
	void addButtonClicked();
	void removeButtonClicked();

private:
	void expand();
	void collapse();

	QListView *ListView;
	QComboBox *ComboBoxChooser;
	QPushButton *ButtonAdd;
	QPushButton *ButtonRemove;
	QSpacerItem *HorizontalSpacer;
	QVBoxLayout *LayoutVertical;
	QHBoxLayout *LayoutHorizontal;
	QStandardItemModel *itemModel;
};

#endif // FIELDMANAGER_H
