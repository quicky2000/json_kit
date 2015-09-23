/*    This file is part of json_kit
      Copyright (C) 2015  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include "json_value.h"
#include "quicky_exception.h"
#include <vector>

namespace json_kit
{
  class json_array: public json_value
  {
  public:
    inline json_array(void);
    inline ~json_array(void);
    inline void add(const json_value & p_value);
    inline size_t get_size(void)const;
    inline const json_value & get(const unsigned int & p_index)const;

  private:
    typedef std::vector<const json_value *> t_elements;
    t_elements m_elements;
  };

  //----------------------------------------------------------------------------
  json_array::json_array(void):
    json_value(json_value::t_value::ARRAY)
  {
    
  }

  //----------------------------------------------------------------------------
  json_array::~json_array(void)
  {
    for(auto l_iter:m_elements)
    {
      delete l_iter;
    }
  }
  //----------------------------------------------------------------------------
  void json_array::add(const json_value & p_value)
  {
    m_elements.push_back(&p_value);
  }

  //----------------------------------------------------------------------------
  size_t json_array::get_size(void)const
  {
    return m_elements.size();
  }

  //----------------------------------------------------------------------------
  const json_value & json_array::get(const unsigned int & p_index)const
  {
    return *(m_elements.at(p_index));
  }

}
#endif // JSON_ARRAY_H
//EOF
