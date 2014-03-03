/**
 * @file mainwindow.h
 * @brief Class represents the main window.
 * @copyright
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author	Niels Neumann <vatriani.nn@googlemail.com>
 * @version 1.0
 */

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
#include "../networkscanner.h"
#include "version.h"

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

public slots:
	void showVersion();
	void showQt();

	void newBook();
	void toggleScanner(bool isEnabled);


private:
	Ui::MainWindow *ui;

	overview *OverView;
	bookdescription *BookDescription;
	toolbargroups *ToolBarGroups;

	void createUi();
	void readConfig();
	void saveConfig();

	QAction *ActionNew;
	QAction *ActionSave;
	QAction *ActionPrint;
	QAction *ActionSearch;
	QAction *ActionShowAll;
	QAction *ActionBarcodeScanner;

	QToolBar *ToolBar;

	networkscanner *NetworkScanner;
};

#endif // MAINWINDOW_H
