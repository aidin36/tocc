/*
 * This file is part of Tocc. (see <http://t-o-c-c.com>)
 * Copyright (C) 2013, 2014, Aidin Gharibnavaz <aidin@t-o-c-c.com>
 *
 * Tocc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tocc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with Tocc.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBTOCC_FILE_INFO_CONVERTER_H_INCLUDED
#include"libtocc/utilities/file_utils.h"
#endif //LIBTOCC_FILE_INFO_CONVERTER_H_INCLUDED

#include<string.h> //for strtok

namespace libtocc
{
	std::string getFilenameFromPath(std::string pPath)
	{
		char*		_charPath = new char[pPath.size()+1];
		char* 		_token;
		std::string	_filename;
		const char 	_sep[2] = "/"; //separator

		//get the file from path
		strcpy(_charPath, pPath.c_str());
		_token = strtok(_charPath, _sep);

		while(_token != 0)
		{
			if(_token != 0)
				_filename = std::string(_token);
			_token = strtok(0, _sep);
		}
		delete[] _charPath;

		//get the filename (without extension)
		size_t _extPos = _filename.rfind(".");
		if(_extPos != std::string::npos && _extPos != 0)
			return _filename.substr(0, _extPos);

		return _filename;
	}
}	
