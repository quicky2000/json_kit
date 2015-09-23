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
#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include "quicky_exception.h"
#include <string>

namespace json_kit
{
  class json_value
  {
  public:
    typedef enum class value_type {STRING=0,NUMBER,OBJECT,ARRAY,TRUE,FALSE,NULLV} t_value;
    inline const t_value & get_type(void)const;
    inline static const std::string & type2string(const t_value & p_type); 
    inline json_value(const t_value & p_type);
    inline virtual ~json_value(void){}
    inline bool is_bool(void)const;
    inline bool get_bool(void)const;
    inline bool is_null(void)const;

    // Virtual methods
    inline virtual const json_value & get(const std::string & p_name)const;
    inline virtual bool contains(const std::string & p_name)const;
    inline virtual size_t get_size(void)const;
    inline virtual const json_value & get(const unsigned int & p_index)const;
    inline virtual const std::string & get_string(void)const;
    inline virtual uint64_t get_uint64_t(void)const;
    inline virtual int64_t get_int64_t(void)const;
    inline virtual double get_double(void)const;
 protected:
  private:
    t_value m_type;
    static const std::string m_type2string[(unsigned int)t_value::NULLV + 1];
  };

  //----------------------------------------------------------------------------
  json_value::json_value(const t_value & p_type):
  m_type(p_type)
  {
  }

  //----------------------------------------------------------------------------
  const json_value::t_value & json_value::get_type(void)const
  {
    return m_type;
  }

  //----------------------------------------------------------------------------
  const std::string & json_value::type2string(const json_value::t_value & p_type)
  {
    return m_type2string[(unsigned int)p_type];
  }

  //----------------------------------------------------------------------------
  const json_value & json_value::get(const std::string & p_name)const
  {
    throw quicky_exception::quicky_logic_exception("Invalid call to method get(<name>) for JSON value type \""+type2string(m_type),__LINE__,__FILE__);
  }

  //----------------------------------------------------------------------------
  const json_value & json_value::get(const unsigned int & p_index)const
  {
    throw quicky_exception::quicky_logic_exception("Invalid call to method get(<index>) for JSON value type \""+type2string(m_type),__LINE__,__FILE__);
  }

  //----------------------------------------------------------------------------
  bool json_value::contains(const std::string & p_name)const
  {
    throw quicky_exception::quicky_logic_exception("Invalid call to method contains(<name>) for JSON value type \""+type2string(m_type),__LINE__,__FILE__);
  }

  //----------------------------------------------------------------------------
  size_t json_value::get_size(void)const
  {
    throw quicky_exception::quicky_logic_exception("Invalid call to method get_size() for JSON value type \""+type2string(m_type),__LINE__,__FILE__);
  }

  //----------------------------------------------------------------------------
  const std::string & json_value::get_string(void)const
  {
    throw quicky_exception::quicky_logic_exception("Invalid call to method get_string() for JSON value type \""+type2string(m_type),__LINE__,__FILE__);
  }

  //----------------------------------------------------------------------------
  bool json_value::is_bool(void)const
  {
    return m_type == t_value::TRUE || m_type == t_value::FALSE;
  }

  //----------------------------------------------------------------------------
  bool json_value::get_bool(void)const
  {
    if(t_value::TRUE == m_type) return true;
    if(t_value::FALSE == m_type) return false;
    throw quicky_exception::quicky_logic_exception("Invalid call to method get_bool() for JSON value type \""+type2string(m_type),__LINE__,__FILE__);
  }

  //----------------------------------------------------------------------------
  bool json_value::is_null(void)const
  {
    return m_type == t_value::NULLV;
  }


  //----------------------------------------------------------------------------
  uint64_t json_value::get_uint64_t(void)const
  {
    throw quicky_exception::quicky_logic_exception("Invalid call to method get_uint64_t() for JSON value type \""+type2string(m_type),__LINE__,__FILE__);
  }

  //----------------------------------------------------------------------------
  int64_t json_value::get_int64_t(void)const
  {
    throw quicky_exception::quicky_logic_exception("Invalid call to method get_int64_t() for JSON value type \""+type2string(m_type),__LINE__,__FILE__);
  }

  //----------------------------------------------------------------------------
  double json_value::get_double(void)const
  {
    throw quicky_exception::quicky_logic_exception("Invalid call to method get_double() for JSON value type \""+type2string(m_type),__LINE__,__FILE__);
  }

}

#endif // JSON_VALUE_H
//EOF
