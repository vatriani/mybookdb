/**
 * @file main.cpp
 * @brief Contains int main function.
 * @copyright
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author	Niels Neumann <vatriani.nn@googlemail.com>
 * @version 1.0
 */



#include "ui/mainwindow.h"
#include "version.h"
#include <QApplication>
#include <QTranslator>
#include <QCommandLineParser>



/**
 * @brief Programm entry point.
 *
 * Create a object from QApplication and MainWindow.
 */
int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setApplicationName(APP_NAME);
	QCoreApplication::setApplicationVersion(APP_VERSION);

	QCommandLineParser parser;
	parser.setApplicationDescription("Programm to manage and view your book collection at home.");
	parser.addHelpOption();
	parser.addVersionOption();

	parser.process(app);

	QTranslator translator;
	//translator.load("hellotr_la");
	app.installTranslator(&translator);

	MainWindow w;
	w.show();

	return app.exec();
}
