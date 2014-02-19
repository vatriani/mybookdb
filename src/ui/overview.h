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
