#include "bookdescription.h"
#include "ui_bookdescription.h"

bookdescription::bookdescription(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::bookdescription)
{
	ui->setupUi(this);
}

bookdescription::~bookdescription()
{
	delete ui;
}
