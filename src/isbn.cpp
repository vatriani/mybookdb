/**
 * @file isbn.cpp
 * @brief ISBN object code for handling with isbn10 or 13 numbers.
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



#include "isbn.h"

#include <string.h>

isbn::isbn()
{
	this->isbnNumber=NULL;
}

isbn::isbn(char *isbn)
{
	this->setIsbn(isbn);
}

bool isbn::isValid()
{
	if(this->isbnNumber==NULL) return false;

	int checksum = 0;
	char *isbn = this->isbnNumber;

	if(strlen(isbn)==13) // isbn13
	{
		for(unsigned short int counter=0;counter<13;counter++)
		{
			int factor=1;
			if(counter%2 != 0 && counter!=0)
				factor=3;
			checksum+=factor*(isbn[counter]-48);
		}

		if (checksum%10 == 0)
			return true;
	}
	return false;
}

bool isbn::setIsbn(char *isbn)
{
	char *p;
	while( p=strchr(isbn,'-') ) {
		memmove(p,p+1,strlen(p));
	}

	if(strlen(isbn)==13)
	{
		this->isbnNumber=isbn;
		return this->isValid();
	}
	else if(strlen(isbn)==10)
	{
		this->isbnNumber=isbn;
		return makeIsbn13();
	}

	return false;
}

bool isbn::makeIsbn13()
{
	int checksum=0;
	for(unsigned short int counter = 1; counter<11;counter++)
		checksum+= counter*(this->isbnNumber[counter-1]-48);

	if (checksum%11 != 0) {
		this->isbnNumber=NULL;
		return false;
	}

	char isbn[14]={'9','7','8','\0'};
	strcat(isbn,this->isbnNumber);

	isbn[12]=0;
	for(unsigned short int counter=0;counter<12;counter++)
	{
		int factor=1;
		if(counter%2 != 0 && counter!=0) factor=3;
		isbn[12]+=(factor*(isbn[counter]-48));
	}

	isbn[12]=((10-(isbn[12]%10))%10)+48;
	isbn[13]='\0';

	strcpy(this->isbnNumber,isbn);
	return true;
}

char* isbn::getIsbn()
{
	return this->isbnNumber;
}
