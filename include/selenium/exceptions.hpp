/*
 * exceptions.hpp
 *
 *  Created on: Sep 8, 2014
 *      Author: speedpat
 */

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <stdexcept>

namespace selenium
{

class WebDriverException : public std::runtime_error
{
public:
	WebDriverException(const std::string& what);
	virtual ~WebDriverException() = default;
};

class ErrorInResponseException : public WebDriverException
{
public:
	ErrorInResponseException(const std::string& what);
	ErrorInResponseException(const std::string& what, const std::runtime_error& cause);
	virtual ~ErrorInResponseException() = default;

private:
	std::runtime_error m_cause;
};

class NoSuchElementException : public WebDriverException
{
public:
	NoSuchElementException(const std::string& what);
	virtual ~NoSuchElementException() = default;

};

class NoSuchFrameException : public WebDriverException
{
public:
	NoSuchFrameException(const std::string& what);
	virtual ~NoSuchFrameException() = default;

};

class TimeoutException : public WebDriverException
{
public:
  TimeoutException(const std::string& what);
  virtual ~TimeoutException() = default;
};

class StaleElementReferenceException : public WebDriverException
{
public:
  StaleElementReferenceException(const std::string& what);
  virtual ~StaleElementReferenceException() = default;

};

class ElementNotVisibleException : public WebDriverException
{
public:
  ElementNotVisibleException(const std::string& what);
  virtual ~ElementNotVisibleException() = default;

};

class NoAlertPresentException : public WebDriverException
{
public:
  NoAlertPresentException(const std::string& what);
  virtual ~NoAlertPresentException() = default;
};

class InvalidElementStateException : public WebDriverException
{
public:
  InvalidElementStateException(const std::string& what);
  virtual ~InvalidElementStateException() = default;
};

class MoveTargetOutOfBoundsException : public WebDriverException
{
public:
  MoveTargetOutOfBoundsException(const std::string& what);
  virtual ~MoveTargetOutOfBoundsException() = default;
};

class UnknownErrorException : public WebDriverException
{
public:
  UnknownErrorException(const std::string& what);
  virtual ~UnknownErrorException() = default;
};

class ElementIsNotSelectableException : public WebDriverException
{
public:
  ElementIsNotSelectableException(const std::string& what);
  virtual ~ElementIsNotSelectableException() = default;
};

class JavaScriptErrorException : public WebDriverException
{
public:
  JavaScriptErrorException(const std::string& what);
  virtual ~JavaScriptErrorException() = default;
};

} /* namespace selenium */



#endif /* EXCEPTIONS_HPP_ */
