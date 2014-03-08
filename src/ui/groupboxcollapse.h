/**
 * @file groupboxcollapse.h
 * @brief Define a collapseable groupbox widget.
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

/**
 * @addtogroup GUIW Custom GUI widgets
 * @{
 */

#ifndef GROUPBOXCOLLAPSE_H
#define GROUPBOXCOLLAPSE_H

#include <QWidget>
#include <QGroupBox>
#include <QMouseEvent>

/**
 * @brief Implements collapseable GroupBox.
 *
 * Simply adding collapseable to a QGroupBox with custom markers like TreeView.
 * Checkability is needed for the indicators.
 *
 * @warning The checkable is sacrifice for collapse.
 */
class groupBoxCollapse : public QGroupBox
{
	Q_OBJECT
public:
	/**
	 * @brief Default constructor.
	 *
	 * Sets variables to enable checkability and collapseability.
	 */
	explicit groupBoxCollapse(QWidget *parent = 0);

	/**
	 * @brief Is triggered by expandig GroupBox.
	 *
	 * At now its recommend to add your widgets visability here in your class.
	 * Sets to true;
	 */
	virtual void expand();
	/**
	 * @brief Is triggered by collapsing GroupBox.
	 *
	 * At now its recommend to add your widgets visability here in your class.
	 * Sets to false.
	 */
	virtual void collapse();

private:
	/**
	 * @brief Helper routine to determine if GroupBox is collapse or expanding.
	 */
	void change();
	/**
	 * @brief Reimplement the OnClick on the title for collapse.
	 */
	void mouseReleaseEvent(QMouseEvent*);

	/**
	 * @brief Holds the collapse state of the GroupBox.
	 */
	bool isCollapse;
};

#endif // GROUPBOXCOLLAPSE_H
/**
 * @}
 */
