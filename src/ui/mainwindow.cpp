#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QApplication>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	_library = new library(this);
	CreateUi();
	ReadConfig();

}

MainWindow::~MainWindow()
{
	delete this->New;
	delete this->Save;
	delete this->Print;
	delete this->Search;
	delete this->ShowAll;
	delete this->ToolBarGroups;
	delete this->ToolBar;
	delete this->OverView;
	delete this->BookDescription;
	delete _library;
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

	connect(this->ui->actionAbout_2,SIGNAL(triggered()),this,SLOT(showVersion()));
	connect(this->ui->actionAbout_Qt_2,SIGNAL(triggered()),this,SLOT(showQt()));

	connect(this->OverView,SIGNAL(openBook(QString)),this->BookDescription,SLOT(openBook(QString)));
}

void MainWindow::ReadConfig()
{
	QSettings settings(APP_NAME,APP_CONFIG);
	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(400, 400)).toSize();
	this->resize(size);
	this->move(pos);
}

void MainWindow::SaveConfig()
{
	QSettings settings(APP_NAME,APP_CONFIG);
	settings.setValue("pos", this->pos());
	settings.setValue("size", this->size());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	SaveConfig();
	event->accept();
}

void MainWindow::showVersion()
{
	QMessageBox(QMessageBox::Information,"About MyBookDB","MyBookDB Version ",QMessageBox::Ok);
}

void MainWindow::showQt()
{
	qApp->aboutQt();
}
