/**
 * @file isbn.h
 * @brief ISBN object code for handling with isbn10 or 13 numbers.
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
 * @defgroup non GUI classes
 * @{
 */

#ifndef ISBN_H
#define ISBN_H


/**
 * @brief Class for store isbn numbers.
 *
 * Additionaly the class checks if the isbn number is valid and converted isbn10
 * to isbn13 and store it.
 *
 * ISBN numbers can contain '-' for better readability on enter but only numbers
 * are stored by this class.
 *
 */
class isbn
{
public:
	/**
	 * @brief Default constructor.
	 */
	isbn();
	/**
	 * @brief Constructor sets initialy a isbn number.
	 * @param isbn Number to check.
	 *
	 * @see isValid()
	 * @see makeIsbn13()
	 */
	isbn(char* /**isbn*/);

	/**
	 * @brief Seter method for ISBN number.
	 *
	 * Also checks if isbn number is valid and need to translate to isbn13.
	 * @return False if isbn number couldn't set.
	 */
	bool setIsbn(char* /**isbn*/);
	/**
	 * @brief geter method for ISBN number.
	 *
	 * @return ISBN number as char* or NULL if ISBN number is not set.
	 */
	char* getIsbn();
	/**
	 * @brief Checks if the isbn number is valid.
	 * @return False for invalid isbn number.
	 */
	bool isValid();

private:
	/**
	 * @brief Convert an ISBN 10 number to an ISBN 13.
	 *
	 * Done by adding 978 at front of the old number and calculate the new
	 * ISBN 13 checksum.
	 */
	bool makeIsbn13();

	/**
	 * @brief Holds the ISBN number
	 */
	char *isbnNumber;
};

#endif // ISBN_H
/** @} */
