/**
 * @file ratingbar.h
 * @brief Own widget with 10 stars to represent rating of a book.
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
 * @addtogroup GUIW Custom GUI widgets
 * @{
 */
#ifndef RATINGBAR_H
#define RATINGBAR_H



#include <QWidget>
#include <QLabel>


/**
 * @brief The ratingbar class is an own widget for represent rating of a book
 * with 10 stars.
 *
 * Rating is shown and could be changed with mousewheel.
 */
class ratingbar : public QWidget
{
	Q_OBJECT
public:
	/**
	 * @brief Default constructor.
	 */
	explicit ratingbar(QWidget *parent = 0);
	/**
	 * @brief Default destructor.
	 */
	~ratingbar();

	/**
	 * @brief Default getter method, returns the rating.
	 * @return Rating as int.
	 */
	int getRating();
	/**
	 * @brief Default setter method for rating.
	 * @param rating Rating representing by an integer.
	 */
	void setRating(int);

signals:

public slots:
	/**
	 * @brief Slot for rating is changed.
	 */
	void changeRating();

protected:
	/**
	 * @brief Implements mousewheel events.
	 *
	 * Interprets mousewheel events as change the rating.
	 * @param event Delivered from eventhandler, represents QWheelEvent.
	 */
	void wheelEvent(QWheelEvent *event);

private:
	/**
	 * @brief Helperfunction to create ui.
	 */
	void createUi();

	/**
	 * @brief 10 QLabel for visual the stars.
	 */
	QLabel *stars[10];
	/**
	 * @brief Contains the actual rating.
	 */
	unsigned int rating;
};

#endif // RATINGBAR_H
/**
 * @}
 */
