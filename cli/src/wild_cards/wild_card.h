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

#ifndef TOCCCLI_WILD_CARD_H_INCLUDED
#define TOCCCLI_WILD_CARD_H_INCLUDED

#include <string>
#include <vector>
#include "engine/singletons.h"

namespace tocccli
{
  class WildCard
  {
    public:
      WildCard(const char* wild_card_expr);
      virtual ~WildCard();

      virtual std::vector<std::string> match(std::string dir_path, std::string file_expression) = 0;
      virtual std::vector<std::string> match(std::string dir_path) = 0;
    
      const char* get_expr() { return expr; }
    protected:
      const char* expr;
  };
}

#endif
