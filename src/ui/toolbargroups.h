#ifndef TOOLBARGROUPS_H
#define TOOLBARGROUPS_H

#include <QWidget>

namespace Ui {
class toolbargroups;
}

class toolbargroups : public QWidget
{
	Q_OBJECT

public:
	explicit toolbargroups(QWidget *parent = 0);
	~toolbargroups();

private:
	Ui::toolbargroups *ui;
};

#endif // TOOLBARGROUPS_H
