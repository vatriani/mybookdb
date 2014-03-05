#ifndef GROUPBOXCOLLAPSE_H
#define GROUPBOXCOLLAPSE_H

#include <QWidget>
#include <QGroupBox>
#include <QListView>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QMouseEvent>

class groupBoxCollapse : public QGroupBox
{
	Q_OBJECT
public:
	explicit groupBoxCollapse(QWidget *parent = 0);

	void addToChooser(QList<QString>);
	void addToView(QList<QString>);

	void mouseReleaseEvent(QMouseEvent*);

signals:

public slots:
	void collapse();

private:


	QListView *ListView;
	QComboBox *ComboBoxChooser;
	QPushButton *ButtonAdd;
	QPushButton *ButtonRemove;
	QPushButton *ButtonNew;
	QSpacerItem *HorizontalSpacer;
	QVBoxLayout *LayoutVertical;
	QHBoxLayout *LayoutHorizontal;
	bool isCollapse;
};

#endif // GROUPBOXCOLLAPSE_H
