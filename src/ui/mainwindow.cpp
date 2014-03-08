#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "../imagestore.h"
#include <QMessageBox>
#include <QApplication>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->BookDescription = NULL;
	this->NetworkScanner = NULL;

	_library = new library(this);
	_imagestore = new imagestore(this);
	createUi();
	readConfig();
}

MainWindow::~MainWindow()
{
	delete this->ActionNew;
	delete this->ActionSave;
	delete this->ActionPrint;
	delete this->ActionSearch;
	delete this->ActionShowAll;
	delete this->ToolBarGroups;
	delete this->ToolBar;
	delete this->OverView;
	if(this->BookDescription)
		delete this->BookDescription;

	delete _library;
	delete _imagestore;
	delete ui;

	if(this->NetworkScanner)
		delete this->NetworkScanner;
}

void MainWindow::createUi()
{
	this->setWindowIcon(QIcon(":/main/app.png"));

	this->ui->actionQuit->setIcon(QIcon(":/toolbar/application_exit.png"));

	this->ActionNew = new QAction(QIcon(":/toolbar/filenew.png"), tr("New"), this);
	this->ActionSave = new QAction(QIcon(":/toolbar/document_save.png"), tr("New"), this);
	this->ActionPrint = new QAction(QIcon(":/toolbar/printer.png"), tr("Print"), this);
	this->ActionSearch = new QAction(QIcon(":/toolbar/edit_find.png"), tr("Search"), this);
	this->ActionShowAll = new QAction(QIcon(":/toolbar/edit_clear_list.png"), tr("Search"), this);
	this->ActionBarcodeScanner = new QAction(QIcon(":/toolbar/barcode.png"), tr("Scan from Barcode"), this);
	this->ActionBarcodeScanner->setCheckable(true);

	this->ToolBarGroups = new toolbargroups(this);

	this->ToolBar = new QToolBar(this);
	this->ToolBar->addAction(this->ActionNew);
	this->ToolBar->addAction(this->ActionSave);
	this->ToolBar->addAction(this->ActionPrint);
	this->ToolBar->addSeparator();
	this->ToolBar->addAction(this->ActionSearch);
	this->ToolBar->addAction(this->ActionShowAll);
	this->ToolBar->addAction(this->ActionBarcodeScanner);
	this->ToolBar->addSeparator();
	this->ToolBar->addWidget(this->ToolBarGroups);
	this->ToolBar->setWindowTitle(tr("Main ToolBar"));
	this->addToolBar(ToolBar);

	this->OverView = new overview(this);
	newBook();

	this->setDockNestingEnabled(true);
	this->addDockWidget(Qt::LeftDockWidgetArea,(QDockWidget*)this->OverView);

	this->ui->scrollArea->setWidgetResizable(true);

	connect(this->ui->actionAbout_2,SIGNAL(triggered()),
			this,SLOT(showVersion()));
	connect(this->ui->actionAbout_Qt_2,SIGNAL(triggered()),
			this,SLOT(showQt()));
	connect(this->ActionNew,SIGNAL(triggered()),
			this,SLOT(newBook()));
	connect(this->ActionBarcodeScanner,SIGNAL(triggered(bool)),
			this,SLOT(toggleScanner(bool)));
}

void MainWindow::readConfig()
{
	QSettings settings(APP_NAME,APP_CONFIG);

	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(400, 400)).toSize();
	bool barcodeScannerIsActive = settings.value("barcode_scanner",false).toBool();

	this->resize(size);
	this->move(pos);
	this->ActionBarcodeScanner->setChecked(barcodeScannerIsActive);
	if(barcodeScannerIsActive)
		this->toggleScanner(barcodeScannerIsActive);
}

void MainWindow::saveConfig()
{
	QSettings settings(APP_NAME,APP_CONFIG);
	settings.setValue("pos", this->pos());
	settings.setValue("size", this->size());
	settings.setValue("barcode_scanner",this->ActionBarcodeScanner->isChecked());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	saveConfig();
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

void MainWindow::newBook()
{
	if(this->BookDescription)
	{
		delete this->BookDescription;
		this->BookDescription = NULL;
	}

	this->BookDescription = new bookdescription(this);
	this->ui->scrollArea->setWidget(this->BookDescription);

	connect(this->OverView,SIGNAL(openBook(QString)),
			this->BookDescription,SLOT(openBook(QString)));
}

void MainWindow::toggleScanner(bool isEnabled)
{
	if(!isEnabled && this->NetworkScanner)
	{
		delete this->NetworkScanner;
		this->NetworkScanner = NULL;
	}
	else
	{
		this->NetworkScanner = new networkscanner;
		connect(this->NetworkScanner,SIGNAL(newBarcode(QString)),
				this->BookDescription,SLOT(isbnScanner(QString)));
	}

}
