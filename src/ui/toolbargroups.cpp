#include "toolbargroups.h"
#include "ui_toolbargroups.h"

toolbargroups::toolbargroups(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::toolbargroups)
{
	ui->setupUi(this);
}

toolbargroups::~toolbargroups()
{
	delete ui;
}
