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
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "json_object.h"
#include "json_number.h"
#include "json_string.h"
#include "json_array.h"
#include <iostream>

namespace json_kit
{
  class json_parser
  {
  public:
    inline const json_object & parse(const std::string & p_string)const;
    
  private:
    inline const json_object & parse_json_object(size_t & l_pos,const std::string & p_string)const;
    inline std::string parse_string(size_t & l_pos,const std::string & p_string)const;
    inline const json_value & parse_value(size_t & l_pos,const std::string & p_string)const;
    inline const json_number & parse_number(size_t & l_pos,const std::string & p_string)const;
    inline const json_array & parse_json_array(size_t & l_pos,const std::string & p_string)const;

    inline void throw_exception(const std::string & p_message,
				const size_t & p_pos,
				const std::string & p_string,
				const unsigned int & p_line,
				const std::string & p_file_name)const;
  };

  //----------------------------------------------------------------------------
  const json_object & json_parser::parse(const std::string & p_string)const
  {
    size_t l_pos = p_string.find_first_not_of(" \t");
    if(std::string::npos == l_pos) throw quicky_exception::quicky_logic_exception("Empty line",__LINE__,__FILE__);
    return parse_json_object(l_pos,p_string);
  }

  //----------------------------------------------------------------------------
  const json_object & json_parser::parse_json_object(size_t & l_pos,const std::string & p_string)const
  {
#ifdef DEBUG_JSON_PARSER
    std::cout << "--> Parsing Object : \"" << p_string.substr(l_pos,p_string.size() > 20 ? 20 : p_string.size()) << std::endl;
#endif // DEBUG_JSON_PARSER
    if(p_string[l_pos] != '{') throw_exception("Waiting for '{' character",l_pos,p_string,__LINE__,__FILE__);
    ++l_pos;
    if(p_string.size() == l_pos) throw_exception("Prematured end of object after '{' character",l_pos,p_string,__LINE__,__FILE__);
    l_pos = p_string.find_first_not_of(" \t",l_pos);
    if(p_string.size() == l_pos) throw_exception("Prematured end of object blank characters following '{' character",l_pos,p_string,__LINE__,__FILE__);
    json_object * l_object = new json_object();
    try
      {
	while('}' != p_string[l_pos])
	  {
	    std::string l_element_name = parse_string(l_pos,p_string);
#ifdef DEBUG_JSON_PARSER
	    std::cout << "Element name \"" << l_element_name << "\"" << std::endl ;
#endif // DEBUG_JSON_PARSER
	    l_pos = p_string.find_first_not_of(" \t",l_pos);
	    if(std::string::npos == l_pos || ':' != p_string[l_pos]) throw_exception("Expecting ':' character to separate object element name from value",l_pos,p_string,__LINE__,__FILE__);
	    if(p_string.size() - 1 == l_pos) throw_exception("Prematured end of string : Member value is missing",l_pos,p_string,__LINE__,__FILE__);
	    ++l_pos;
	    l_object->add(l_element_name,parse_value(l_pos,p_string));
	    l_pos = p_string.find_first_not_of(" \t",l_pos);
	    if(std::string::npos == l_pos) throw_exception("Prematured end of json_object, waiting for ',' character",l_pos,p_string,__LINE__,__FILE__);
	    if(',' == p_string[l_pos])
	      {
		++ l_pos;
		l_pos = p_string.find_first_not_of(" \t",l_pos);
		if(std::string::npos == l_pos) throw_exception("Prematured end of json_object, waiting for '}' to terminate the object or '\"' to start a new element name",l_pos,p_string,__LINE__,__FILE__);
	      } 
	  }
	++l_pos;
      }
    catch(quicky_exception::quicky_logic_exception & e)
      {
	delete l_object;
	throw e;
      }
     catch(std::exception & e)
      {
	delete l_object;
	throw e;
      }
#ifdef DEBUG_JSON_PARSER
    std::cout << "<-- Object parsed : \"" << p_string.substr(l_pos,p_string.size() > 20 ? 20 : p_string.size()) << std::endl;
#endif // DEBUG_JSON_PARSER
    return * l_object;
  }

  //----------------------------------------------------------------------------
  std::string json_parser::parse_string(size_t & l_pos,const std::string & p_string)const
  {
#ifdef DEBUG_JSON_PARSER
    std::cout << "--> Parsing String : \"" << p_string.substr(l_pos,p_string.size() > 20 ? 20 : p_string.size()) << std::endl;
#endif // DEBUG_JSON_PARSER
    if(p_string[l_pos] != '"') throw quicky_exception::quicky_logic_exception("Waiting for '\"' character in string \"" + p_string.substr(l_pos) +"\"",__LINE__,__FILE__);
    size_t l_pos_begin = l_pos + 1;
    bool l_continu = false;
    do
      {
	l_pos = p_string.find('"',l_pos + 1);
	if(std::string::npos == l_pos) throw quicky_exception::quicky_logic_exception("Excepting closing '\"' for string in " + p_string.substr(l_pos),__LINE__,__FILE__);
	l_continu = l_pos && p_string[l_pos -1] == '\\';
      } while(l_continu);
    ++l_pos;
#ifdef DEBUG_JSON_PARSER
    std::cout << "<-- String parsed : \"" << p_string.substr(l_pos,p_string.size() > 20 ? 20 : p_string.size()) << std::endl;
#endif // DEBUG_JSON_PARSER
    return p_string.substr(l_pos_begin, l_pos - l_pos_begin - 1);
    
  }
 
  //----------------------------------------------------------------------------
  const json_number & json_parser::parse_number(size_t & l_pos,const std::string & p_string)const
  {
#ifdef DEBUG_JSON_PARSER
    std::cout << "--> Parsing Number : \"" << p_string.substr(l_pos,p_string.size() > 20 ? 20 : p_string.size()) << std::endl;
#endif // DEBUG_JSON_PARSER
    size_t l_pos_start = l_pos;
    if(p_string.size() - 1 == l_pos) throw_exception("Prematured end of JSON number",l_pos,p_string,__LINE__,__FILE__);
    l_pos = p_string.find_first_not_of("0123456789eE-.",l_pos+1);
    if(std::string::npos == l_pos) throw_exception("No characters afer JSON number",l_pos_start,p_string,__LINE__,__FILE__);
#ifdef DEBUG_JSON_PARSER
    std::cout << "<-- Number parsed : \"" << p_string.substr(l_pos,p_string.size() > 20 ? 20 : p_string.size()) << std::endl;
#endif // DEBUG_JSON_PARSER
    return * new json_number(p_string.substr(l_pos_start,l_pos - l_pos_start));
  }

  //----------------------------------------------------------------------------
  const json_array & json_parser::parse_json_array(size_t & l_pos,const std::string & p_string)const
  {
#ifdef DEBUG_JSON_PARSER
    std::cout << "--> Parsing Array : \"" << p_string.substr(l_pos,p_string.size() > 20 ? 20 : p_string.size()) << std::endl;
#endif // DEBUG_JSON_PARSER
    if('[' != p_string.at(l_pos)) throw_exception("Expecting '[' to start a JSON array",l_pos,p_string,__LINE__,__FILE__);
    ++l_pos;
    if(l_pos == p_string.size()) throw_exception("Prematured end of JSON array after '[' character",l_pos,p_string,__LINE__,__FILE__);
    l_pos = p_string.find_first_not_of(" \t",l_pos);
    if(std::string::npos == l_pos) throw_exception("Prematured end of JSON array after '[' or blank characters",l_pos,p_string,__LINE__,__FILE__);
    json_array * l_array = new json_array();
    try
      {
	while(']' != p_string[l_pos])
	{
	  l_array->add(parse_value(l_pos,p_string));
	  l_pos = p_string.find_first_not_of(" \t",l_pos);
	  if(std::string::npos == l_pos) throw_exception("Prematured end of json_array waiting for character after element",l_pos,p_string,__LINE__,__FILE__);
	  if(',' == p_string[l_pos])
	    {
	      ++ l_pos;
	      l_pos = p_string.find_first_not_of(" \t",l_pos);
	      if(std::string::npos == l_pos) throw_exception("Prematured end of json_array, waiting for ']' to terminate the array or a new value",l_pos,p_string,__LINE__,__FILE__);
	    } 
	}
	++l_pos;
      }
    catch(quicky_exception::quicky_logic_exception & e)
      {
	delete l_array;
	throw e;
      }
     catch(std::exception & e)
      {
	delete l_array;
	throw e;
      }
#ifdef DEBUG_JSON_PARSER
    std::cout << "<-- Array parsed : \"" << p_string.substr(l_pos,p_string.size() > 20 ? 20 : p_string.size()) << std::endl;
#endif // DEBUG_JSON_PARSER
    return * l_array;
  }

  //----------------------------------------------------------------------------
  const json_value & json_parser::parse_value(size_t & l_pos,const std::string & p_string)const
  {
    if(p_string.size() == l_pos) throw_exception("Premature end of JSON value",l_pos,p_string,__LINE__,__FILE__);
    l_pos = p_string.find_first_not_of(" \t",l_pos);
    if(std::string::npos == l_pos) throw_exception("Premature end of JSON value",l_pos,p_string,__LINE__,__FILE__);
    switch(p_string[l_pos])
      {
      case '-':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
	return parse_number(l_pos,p_string);
	break;
      case '"':
	return * new json_string(parse_string(l_pos,p_string));
	break;
      case '[':
	return parse_json_array(l_pos,p_string);
	break;
      case '{':
	return parse_json_object(l_pos,p_string);
	break;
      case 'f':
	if(p_string.size() - l_pos < std::string("false").size() || "false" != p_string.substr(l_pos,std::string("false").size())) throw_exception("Expecting \"false\" keyword",l_pos,p_string,__LINE__,__FILE__);
	l_pos += std::string("false").size();
	return * new json_value(json_value::t_value::FALSE);
	break;
      case 't':
	if(p_string.size() - l_pos < std::string("true").size() || "true" != p_string.substr(l_pos,std::string("true").size())) throw_exception("Expecting \"true\" keyword",l_pos,p_string,__LINE__,__FILE__);
	l_pos += std::string("true").size();
	return * new json_value(json_value::t_value::TRUE);
	break;
      case 'n':
	if(p_string.size() - l_pos < std::string("null").size() || "null" != p_string.substr(l_pos,std::string("null").size())) throw_exception("Expecting \"null\" keyword",l_pos,p_string,__LINE__,__FILE__);
	l_pos += std::string("null").size();
	return * new json_value(json_value::t_value::NULLV);
	break;
      default:
	throw_exception("Unexpected character '"+std::string(1,p_string[l_pos])+"' to begin a JSON value",l_pos,p_string,__LINE__,__FILE__);
	break;
      }
    // Should never occur
    return *new json_string("DUMMY");
  }

  //----------------------------------------------------------------------------
  void json_parser::throw_exception(const std::string & p_message,
				    const size_t & p_pos,
				    const std::string & p_string,
				    const unsigned int & p_line,
				    const std::string & p_file_name)const
  {
    throw quicky_exception::quicky_logic_exception(p_message+" in string \""+ p_string.substr(p_pos) + "\"",p_line,p_file_name);
  }

}
#endif // JSON_PARSER_H
//EOF
