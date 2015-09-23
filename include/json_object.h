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
#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include "json_value.h"
#include "quicky_exception.h"
#include <map>

namespace json_kit
{
  class json_object: public json_value
  {
  public:
    inline json_object(void);
    inline ~json_object(void);
    inline void add(const std::string & p_name,
		    const json_value & p_value);
    inline bool contains(const std::string & p_name)const;
    inline size_t get_size(void)const;
    inline const json_value & get(const std::string & p_name)const;
  private:
    typedef std::map<std::string,const json_value*> t_elements;
    t_elements m_elements;
  };

  //----------------------------------------------------------------------------
  json_object::json_object(void):
    json_value(json_value::t_value::OBJECT)
  {
    
  }

  //----------------------------------------------------------------------------
  json_object::~json_object(void)
  {
    for(auto l_iter: m_elements)
    {
      delete l_iter.second;
    }
  }

  //----------------------------------------------------------------------------
  void json_object::add(const std::string & p_name,
			const json_value & p_value)
  {
    m_elements.insert(t_elements::value_type(p_name,&p_value));
  }

  //----------------------------------------------------------------------------
  bool json_object::contains(const std::string & p_name)const
  {
    return m_elements.end() != m_elements.find(p_name);
  }

  //----------------------------------------------------------------------------
  const json_value & json_object::get(const std::string & p_name)const
  {
    t_elements::const_iterator l_iter = m_elements.find(p_name);
    if(m_elements.end() != l_iter)
      {
	return *(l_iter->second);
      }
    throw quicky_exception::quicky_logic_exception("Unable to find member name \""+p_name+"\"",__LINE__,__FILE__);
  }
    
  //----------------------------------------------------------------------------
  size_t json_object::get_size(void)const
  {
    return m_elements.size();
  }

}
#endif // JSON_OBJECT_H
//EOF
