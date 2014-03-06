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
