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
  using std::runtime_error::runtime_error;
};

class ErrorInResponseException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class NoSuchElementException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class NoSuchFrameException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class TimeoutException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class StaleElementReferenceException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class ElementNotVisibleException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class NoAlertPresentException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class InvalidElementStateException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class MoveTargetOutOfBoundsException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class UnknownErrorException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class ElementIsNotSelectableException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class JavaScriptErrorException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class InvalidSelectorException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class UnexpectedAlertException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};

class NoSuchWindowException : public WebDriverException
{
public:
  using WebDriverException::WebDriverException;
};
} /* namespace selenium */



#endif /* EXCEPTIONS_HPP_ */
