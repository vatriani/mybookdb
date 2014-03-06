#ifndef GROUPBOXCOLLAPSE_H
#define GROUPBOXCOLLAPSE_H

#include <QWidget>
#include <QGroupBox>
#include <QMouseEvent>

class groupBoxCollapse : public QGroupBox
{
	Q_OBJECT
public:
	explicit groupBoxCollapse(QWidget *parent = 0);

	void mouseReleaseEvent(QMouseEvent*);
	void change();
	virtual void expand();
	virtual void collapse();

private:
	bool isCollapse;
};

#endif // GROUPBOXCOLLAPSE_H
