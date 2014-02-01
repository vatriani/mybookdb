/**
 * @file config.h
 * @brief Contains definitions of the struct tuple and classdefinition of Config.
 * @see tuple
 * @see Config
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

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <pthread.h>		// mutex
#include <vector>			// std::vector
#include <string>			// std::string

#include <version.h>



/**
 * @brief contains field name and value
 */
typedef struct {
	std::string descriptor;	///< field name
	std::string value;		///< field value
} tuple;



/**
 * @brief Handler for load, store and config values of the game
 *
 * Config file must have the format like:
 * valuename:value
 * @todo implement subsection in configfiles and comments
 * @todo implement Config::SetValue(std::string desc, std::string value)
 **/
class Config {
private:
	/// protects the TupleList
	pthread_mutex_t mutex;
	/// config tuples stored in a vector
	static std::vector<tuple> TupleList;

	/**
	 * convert a line from the configfile to an tuple struct
	 * @param	line the parsing line
	 * @return	tuple struct of the parameter line
	 */
	tuple* ParsingLine(std::string line);

	/**
	 * Find configs in different directorys.
	 * @return	string last found dest.
	 */
	std::string GetLocation();


public:
	Config();
	~Config();


	/**
	 * @brief loads the configfile in TupleList.
	 * @return	true if configfile was succsessful loaded
	 */
	bool LoadConfig(std::string filename);

	/**
	 * @brief stored the configuration TupleList in a configfile.
	 * @return	true if configfile was stored succsessful.
	 */
	bool SaveConfig();

	/**
	 * @brief search in the TupleList a valuename and returns the value
	 * @param	desc valuename as String
	 * @return	value of the valuename
	 */
	std::string GetFromDesc(std::string desc);

	/**
	 * @brief search in the TupleList a valuename and returns the value
	 *
	 * Same as std::string GetFromDesc(std::string) but only wraps as char*
	 * for easier use in some context.
	 * @see GetFromDesc(std::string desc)
	 */
	const char* GetFromDesc(char* desc);

	/**
	 * @brief set a value to an existing valuename in TupleList
	 * @param	desc valuename as String
	 * @param	value value to set as String
	 * @return	returns true if setting value was succsessful.
	 * @todo	needs implementation
	 */
	bool SetValue(std::string desc, std::string value);
};

#endif
