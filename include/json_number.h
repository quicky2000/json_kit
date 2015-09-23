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
#ifndef JSON_NUMBER_H
#define JSON_NUMBER_H

#include "json_value.h"
#include <string>
#include <cstdlib>

namespace json_kit
{
  class json_number: public json_value
  {
  public:
    inline json_number(const std::string & p_number);
    inline uint64_t get_uint64_t(void)const;
    inline int64_t get_int64_t(void)const;
    inline double get_double(void)const;
  private:
    std::string m_number;
  };

  //----------------------------------------------------------------------------
  json_number::json_number(const std::string & p_number):
  json_value(json_value::t_value::NUMBER),
  m_number(p_number)
  {
  }

  //----------------------------------------------------------------------------
  uint64_t json_number::get_uint64_t(void)const
  {
    return strtoull(m_number.c_str(),NULL,0);
  }

  //----------------------------------------------------------------------------
  int64_t json_number::get_int64_t(void)const
  {
    return strtoll(m_number.c_str(),NULL,0);
  }

  //----------------------------------------------------------------------------
  double json_number::get_double(void)const
  {
    return strtod(m_number.c_str(),NULL);
  }
}

#endif // JSON_NUMBER_H
//EOF
