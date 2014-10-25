/*
 * script_result.hpp
 *
 *  Created on: Sep 24, 2014
 *      Author: speedpat
 */

#ifndef SCRIPT_RESULT_HPP_
#define SCRIPT_RESULT_HPP_

#include <selenium/types.hpp>

namespace selenium
{
class CommandExecutor;

class ScriptResult : public Json::Value
{
public:
    template <bool is_const_iterator = true>
    class const_noconst_iterator : public std::iterator<std::bidirectional_iterator_tag, ScriptResult> {
    private:

      typedef typename std::conditional<is_const_iterator, const ScriptResult&, ScriptResult&>::type ValueReferenceType;

      typedef typename std::conditional<is_const_iterator, Response::const_iterator, Response::iterator>::type InnerIteratorType;

      const_noconst_iterator(ValueReferenceType result, InnerIteratorType pos) : _result(result), _pos(pos) {
      }


    public:
      const_noconst_iterator(const const_noconst_iterator<false>& other) : _result(other._result), _pos(other._pos) {
      }

      bool operator== (const const_noconst_iterator& other) const {
        return _pos == other._pos;
      }

      bool operator!= (const const_noconst_iterator& other) const {
        return !(*this == other);
      }

      ScriptResult operator*() {
        std::cerr << ((*_pos)) << std::endl;
        return ScriptResult::create(_result.m_driver, *_pos);
      }

      const_noconst_iterator& operator--(){
        _pos--;
        return (*this);
      }

      const_noconst_iterator operator--(int){
        const const_noconst_iterator old(*this);
        --(*this);
        return old;
      }

      const_noconst_iterator& operator++(){
        _pos++;
        return (*this);
      }

      const_noconst_iterator operator++(int){
        const const_noconst_iterator old(*this);
        ++(*this);
        return old;
      }

      friend class const_noconst_iterator<true>;
      friend class ScriptResult;

    private:
      ValueReferenceType _result;
      InnerIteratorType _pos;

    }; // end of nested class const_noconst_iterator

    /**
     * Shorthand for a regular iterator (non-const) type for ScriptResult.
     */
    typedef const_noconst_iterator<false> iterator;

    /**
     * Shorthand for a constant iterator (const_iterator) type for a ScriptResult.
     */
    typedef const_noconst_iterator<true> const_iterator;


private:
  static ScriptResult create(CommandExecutor& driver, const Response& value);
  ScriptResult(CommandExecutor& driver, const Response& array);

  friend class WebDriver;

public:
  ScriptResult(const ScriptResult& other);

  operator int() const throw (std::runtime_error);
  operator long() const throw (std::runtime_error);
  operator long long int() const throw (std::runtime_error);
  operator float() const throw (std::runtime_error);
  operator double() const throw (std::runtime_error);
  operator bool() const throw (std::runtime_error);
  operator WebElement() const throw (std::runtime_error);
  operator WebElements() const;
  operator std::string() const throw (std::runtime_error);
  explicit operator const char*() const throw (std::runtime_error);

  ScriptResult& operator =(const ScriptResult& other);

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;


  bool operator==(const int&) const;
  bool operator==(const long&) const;
  bool operator==(const long long int&) const;
  bool operator==(const float&) const;
  bool operator==(const double&) const;
  bool operator==(const bool&) const;
  bool operator==(const WebElement&) const;
  bool operator==(const std::string&) const;
  bool operator==(const char*) const;

private:
  CommandExecutor& m_driver;
};

bool operator==(const int&, const ScriptResult&);
bool operator==(const long&, const ScriptResult&);
bool operator==(const long long int&, const ScriptResult&);
bool operator==(const float&, const ScriptResult&);
bool operator==(const double&, const ScriptResult&);
bool operator==(const bool&, const ScriptResult&);
bool operator==(const WebElement&, const ScriptResult&);
bool operator==(const std::string&, const ScriptResult&);
bool operator==(const char*, const ScriptResult&);

} /* namespace selenium */

#endif /* SCRIPT_RESULT_HPP_ */
