/*
 * supergemometric - config.cpp
 * Copyright © 2014 - Niels Neumann  <vatriani.nn@googlemail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <fstream>
#include <version.h>


std::vector<tuple> Config::TupleList;

Config::Config() {
	this->mutex = PTHREAD_MUTEX_INITIALIZER;
	this->TupleList.clear();
}

Config::~Config() {
}

bool Config::LoadConfig(std::string filename) {
	if(pthread_mutex_lock(&this->mutex) == 0) {
		std::ifstream file(filename.c_str());

		if(file.is_open()) {
			std::string line;

			for(std::getline(file,line);
					!file.fail() && !file.eof();
					std::getline(file,line)) {

				tuple* t=ParsingLine(line);
				if(t != NULL) {
					this->TupleList.push_back(*t);
				}
			}
		}
		else {
			// file read error
		}
		pthread_mutex_unlock(&this->mutex);
	}
}

bool Config::SaveConfig() {
	if(pthread_mutex_lock(&this->mutex) == 0) {
		this->TupleList.clear();
		pthread_mutex_unlock(&this->mutex);
	}
}

std::string Config::GetFromDesc(std::string desc) {
	std::string ret;
	if(pthread_mutex_lock(&this->mutex) == 0) {
		for(std::vector<tuple>::iterator it = this->TupleList.begin() ;
			it != this->TupleList.end();
			++it) {

			if(desc.compare(((tuple) *it).descriptor)==0) {
				ret=((tuple) *it).value;
				break;
			}
			else {
				ret="BAD";
			}
		}
		pthread_mutex_unlock(&this->mutex);
	}
	return ret;
}

const char* Config::GetFromDesc(char* desc) {
	return GetFromDesc(std::string(desc)).c_str() ;
}

bool Config::SetValue(std::string desc, std::string value) {
}

tuple* Config::ParsingLine(std::string line) {
	if(line.length() > 1) {
		tuple* newTuple = new tuple;
		size_t posOfSeparator = 0;
#ifdef WIN

#else
		if(!line.empty() && line[line.length()-1] == '\n') {
			line.erase(line.length()-1);
		}
		if(!line.empty() && line[line.length()-1] == '\r') {
			line.erase(line.length()-1);
		}
#endif
		posOfSeparator=line.find_first_of(":");
		newTuple->descriptor = std::string(line,0,posOfSeparator);
		newTuple->value = std::string(line,posOfSeparator+1);

		return newTuple;
	}
	return NULL;
}

std::string Config::GetLocation() {

}
