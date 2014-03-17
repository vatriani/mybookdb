/**
 * @file imagestore.cpp
 * @brief Handling class for extern images.
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



#include "imagestore.h"
#include "version.h"


#include <QSettings>
#include <QDebug>



imagestore *_imagestore = NULL;



imagestore::imagestore(QObject *parent) :
	QObject(parent)
{
	QSettings settings(APP_NAME,APP_CONFIG);
	QString tmpPath = settings.fileName();
	tmpPath.chop(strlen(APP_CONFIG)+5);
	tmpPath.append("image/");

	this->imagePath = new QDir(tmpPath);
	if(!this->imagePath->exists())
		this->imagePath->mkdir(tmpPath);
}

imagestore::~imagestore()
{
	delete this->imagePath;
}

QPixmap *imagestore::getImageFromKey(QString title, QString isbn)
{
	QPixmap *returnPixmap = new QPixmap();
	QString imageFilePath = this->imagePath->absolutePath();
	QByteArray hash;

	hash.append(isbn);
	hash.append(title);
	hash = QCryptographicHash::hash(hash,QCryptographicHash::Md5).toHex();

	imageFilePath.append("/").append(hash).append(".png");
	returnPixmap->load(imageFilePath);
	if(returnPixmap->width()<=0)
	{
		return NULL;
	}
	QPixmap *ret = new QPixmap(returnPixmap->scaled(QSize(100,200),Qt::KeepAspectRatio,Qt::SmoothTransformation));
	delete returnPixmap;
	return ret;
}

bool imagestore::storeImage(QPixmap pixmap, QString title, QString isbn)
{
	QString imageFilePath = this->imagePath->absolutePath();
	QByteArray hash;

	hash.append(isbn);
	hash.append(title);
	hash = QCryptographicHash::hash(hash,QCryptographicHash::Md5).toHex();

	imageFilePath.append("/").append(hash).append(".png");

	pixmap = pixmap.scaled(QSize(280,445),Qt::KeepAspectRatio);
	return pixmap.save(imageFilePath);
}
