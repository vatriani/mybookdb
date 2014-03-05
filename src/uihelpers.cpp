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
