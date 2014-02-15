#include "library.h"

#include <QSettings>
#include <QMessageBox>
#include <QDebug>
#include <QApplication>

library::library(QObject *parent) :
	QObject(parent)
{
	db.addDatabase("QSQLITE");
	//db.setConnectOptions("QSQLITE_OPEN_URI=1");
	//db.setHostName("localhost");
	db.setDatabaseName(":memory:");
	if(!db.open()) {
		QMessageBox::critical(0, tr("Cannot open database"),
		tr("Unable to establish a database connection.\n"
		"This program needs SQLite support. Please read "
		"the Qt SQL driver documentation for information how "
		"to build it.\n\n"
		"Click Cancel to exit."), QMessageBox::Cancel);
	}
}
