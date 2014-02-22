#ifndef BOOKDESCRIPTION_H
#define BOOKDESCRIPTION_H

#include <QWidget>
#include <QString>
#include "ratingbar.h"

namespace Ui {
class bookdescription;
}

class bookdescription : public QWidget
{
	Q_OBJECT

public:
	explicit bookdescription(QWidget *parent = 0);
	~bookdescription();

public slots:
	void inputIsbn(QString);
	void resetIsbn();

	void openBook(QString key);

private:
	Ui::bookdescription *ui;
	QString bookKey;

	ratingbar *Ratingbar;
};

#endif // BOOKDESCRIPTION_H
