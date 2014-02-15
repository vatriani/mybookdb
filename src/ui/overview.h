#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <QDockWidget>

namespace Ui {
class overview;
}

class overview : public QDockWidget
{
	Q_OBJECT

public:
	explicit overview(QWidget *parent = 0);
	~overview();

private:
	Ui::overview *ui;
};

#endif // OVERVIEW_H
