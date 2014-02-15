#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QToolBar>
#include <QSettings>
#include <QCloseEvent>

#include "overview.h"
#include "bookdescription.h"
#include "toolbargroups.h"

#include "../library.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void closeEvent(QCloseEvent *event);

private:
	Ui::MainWindow *ui;

	library *Library;
	overview *OverView;
	bookdescription *BookDescription;
	toolbargroups *ToolBarGroups;

	void CreateUi();
	void ReadConfig();
	void SaveConfig();

	QAction *New;
	QAction *Save;
	QAction *Print;
	QAction *Search;
	QAction *ShowAll;


	QToolBar *ToolBar;
};

#endif // MAINWINDOW_H
