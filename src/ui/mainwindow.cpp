#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	CreateUi();
	ReadConfig();

	//this->Library = new library(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::CreateUi()
{
	this->setWindowIcon(QIcon(":/main/app.png"));

	this->ui->actionQuit->setIcon(QIcon(":/toolbar/application_exit.png"));

	New = new QAction(QIcon(":/toolbar/book.png"), tr("New"), this);
	Save = new QAction(this);
	Print = new QAction(QIcon(":/toolbar/printer.png"), tr("Print"), this);
	Search = new QAction(QIcon(":/toolbar/search.png"), tr("Search"), this);
	this->ShowAll = new QAction(this);

	this->ToolBarGroups = new toolbargroups(this);


	ToolBar = new QToolBar(this);
	ToolBar->addAction(New);
	ToolBar->addAction(Save);
	ToolBar->addAction(Print);
	this->ToolBar->addSeparator();
	ToolBar->addAction(Search);
	this->ToolBar->addAction(this->ShowAll);
	this->ToolBar->addSeparator();
	this->ToolBar->addWidget(this->ToolBarGroups);
	ToolBar->setWindowTitle(tr("Main ToolBar"));
	this->addToolBar(ToolBar);

	this->OverView = new overview(this);


	this->BookDescription = new bookdescription(this);
	this->setDockNestingEnabled(true);
	this->addDockWidget(Qt::LeftDockWidgetArea,(QDockWidget*)this->OverView);



	this->ui->scrollArea->setWidget(this->BookDescription);
	this->ui->scrollArea->setWidgetResizable(true);
}

void MainWindow::ReadConfig()
{
	QSettings settings("mybookdb");
	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(400, 400)).toSize();
	this->resize(size);
	this->move(pos);
}

void MainWindow::SaveConfig()
{
	QSettings settings("mybookdb");
	settings.setValue("pos", this->pos());
	settings.setValue("size", this->size());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	SaveConfig();
	event->accept();
}
