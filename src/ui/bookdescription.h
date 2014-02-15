#ifndef BOOKDESCRIPTION_H
#define BOOKDESCRIPTION_H

#include <QWidget>

namespace Ui {
class bookdescription;
}

class bookdescription : public QWidget
{
	Q_OBJECT

public:
	explicit bookdescription(QWidget *parent = 0);
	~bookdescription();

private:
	Ui::bookdescription *ui;
};

#endif // BOOKDESCRIPTION_H
