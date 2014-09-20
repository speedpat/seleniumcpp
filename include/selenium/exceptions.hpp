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
	WebDriverException(const WebDriverException& e);
	virtual ~WebDriverException() = default;
};

class ErrorInResponseException : public WebDriverException
{
public:
	ErrorInResponseException(const std::string& what);
	ErrorInResponseException(const std::string& what, const std::runtime_error& cause);
	ErrorInResponseException(const ErrorInResponseException& e);
	virtual ~ErrorInResponseException() = default;

private:
	std::runtime_error m_cause;
};

class NoSuchElementException : public WebDriverException
{
public:
	NoSuchElementException(const std::string& what);
	NoSuchElementException(const NoSuchElementException& e);
	virtual ~NoSuchElementException() = default;

};

class NoSuchFrameException : public WebDriverException
{
public:
	NoSuchFrameException(const std::string& what);
	NoSuchFrameException(const NoSuchFrameException& e);
	virtual ~NoSuchFrameException() = default;

};

class TimeoutException : public WebDriverException
{
public:
  TimeoutException(const std::string& what);
  TimeoutException(const NoSuchFrameException& e);
  virtual ~TimeoutException() = default;
};

class StaleElementReferenceException : public WebDriverException
{
public:
  StaleElementReferenceException(const std::string& what);
  StaleElementReferenceException(const NoSuchFrameException& e);
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

} /* namespace selenium */



#endif /* EXCEPTIONS_HPP_ */
