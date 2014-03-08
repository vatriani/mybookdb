/**
 * @file imagestore.h
 * @brief Handling class for extern images.
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
#ifndef IMAGESTORE_H
#define IMAGESTORE_H



#include <QObject>
#include <QString>
#include <QDir>
#include <QPixmap>



/**
 * @brief Image file handling from local user directory.
 *
 * Class to save and load images by key from config path of user.
 * The key is without fileextension and will be automatic added (*.png).
 */
class imagestore : public QObject
{
	Q_OBJECT
public:
	/**
	 * @brief Standard constructor.
	 *
	 * Checks if the imagepath exists or create it if it doesn't.
	 */
	explicit imagestore(QObject *parent = 0);
	/**
	 * @brief Standard destructor.
	 */
	~imagestore();

	/**
	 * @brief Load image by key.
	 * @param key Keyvalue or filename without fileextension.
	 * @return Returning QPixmap pointer of the loaded image. If image doesn't
	 * exists the NULL pointer is returned.
	 */
	QPixmap *getImageFromKey(QString);
	/**
	 * @brief Store the image under keyvalue with automaic added fileextension.
	 * @param pixmap The QPixmap object containing the image.
	 * @param key The image file name without fileextension.
	 * @return True if image could be saved.
	 */
	bool storeImage(QPixmap,QString);

private:
	/**
	 * @brief Holds the image directory from users .config directory.
	 */
	QDir *imagePath;
};



/**
 * @brief Global library instance for getting everywhere infos.
 */
extern imagestore *_imagestore;

#endif // IMAGESTORE_H
/**
 * @}
 */
