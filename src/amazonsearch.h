/**
 * @file amazonsearch.h
 * @brief Searching book informations from amazon.
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

/**
 * @addtogroup NGUI Non GUI classes
 * @{
 */

#ifndef AMAZONSEARCH_H
#define AMAZONSEARCH_H

#include <QObject>

class amazonsearch : public QObject
{
	Q_OBJECT
public:
	explicit amazonsearch(QObject *parent = 0);

signals:

public slots:

};

#endif // AMAZONSEARCH_H
/**
 * @}
 */
