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


#include "engine/wild_card_manager.h"
#include "wild_cards/asterisk_wild_card.h"
#include "utilities/file_system.h"

namespace tocccli
{
   WildCardManager::WildCardManager()
   {
     wild_cards.push_back(new AsteriskWildCard());
   }

   std::vector<std::string> WildCardManager::detect_wild_cards(std::string expression)
   {
      std::vector<std::string> files;
      std::string dir = get_dir(expression);
      std::string file_expression = get_file(expression);
      
      for(int i = 0; i < wild_cards.size(); i++)
      {
        if(file_expression.find(wild_cards[i]->get_expr()) >= 0)
        {
          files = wild_cards[i]->match(dir, file_expression);
        }
      }
     
      return files;
   }
}
