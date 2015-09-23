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
#ifndef JSON_STRING_H
#define JSON_STRING_H

#include "json_value.h"
#include <string>
#include <locale>
#if __GNUC__ >= 5
#define QUICKY_HANDLE_UNICODE
#include <codecvt>
#endif // QUICKY_HANDLE_UNICODE

namespace json_kit
{
  class json_string: public json_value
  {
  public:
    inline json_string(const std::string & p_string);
    inline const std::string & get_string(void)const;
    inline size_t get_size(void)const;
   private:
    std::string m_string;
    size_t m_size;
  };

  //----------------------------------------------------------------------------
  json_string::json_string(const std::string & p_string):
  json_value(json_value::t_value::STRING),
  m_string(p_string),
  m_size(p_string.size())
  {
#ifdef QUICKY_HANDLE_UNICODE
    bool l_continu = true;
    do
      {
	size_t l_pos = m_string.find("\\u");
	if(std::string::npos != l_pos)
	  {
	    char16_t l_char16 = strtoul(m_string.substr(l_pos + 2,4).c_str(),NULL,16);
	    std::u16string l_source(1,l_char16);
	    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> l_convert;
	    std::string l_dest = l_convert.to_bytes(l_source); 
	    m_string.replace(l_pos,6,l_dest);
	    m_size -= 5;
	  }
	else
	  {
	    l_continu = false;
	  }
      } while(l_continu);
#endif // QUICKY_HANDLE_UNICODE
  }
 
  //----------------------------------------------------------------------------
  const std::string & json_string::get_string(void)const
  {
    return m_string;
  }
 
  //----------------------------------------------------------------------------
  size_t json_string::get_size(void)const
  {
    return m_size;
  }
}

#ifdef QUICKY_HANDLE_UNICODE
#undef QUICKY_HANDLE_UNICODE
#endif // QUICKY_HANDLE_UNICODE

#endif // JSON_STRING_H
//EOF
