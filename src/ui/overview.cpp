#include "overview.h"
#include "ui_overview.h"

overview::overview(QWidget *parent) :
	QDockWidget(parent),
	ui(new Ui::overview)
{
	ui->setupUi(this);

	ui->tab->setWindowIcon(QIcon());
	ui->tab_2->setWindowIcon(QIcon(":/toolbar/filter.png"));
	this->ui->dockWidgetContents->setWindowFlags(Qt::SubWindow);
}

overview::~overview()
{
	delete ui;
}
