/*
 * exceptions.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: speedpat
 */

#include <selenium/exceptions.hpp>

namespace selenium {

WebDriverException::WebDriverException(const std::string& what)
 : std::runtime_error(what)
{

}

WebDriverException::WebDriverException(const WebDriverException& e)
 : std::runtime_error(e)
{

}

ErrorInResponseException::ErrorInResponseException(const std::string& what)
 : WebDriverException(what), m_cause("")
{

}

ErrorInResponseException::ErrorInResponseException(const std::string& what, const std::runtime_error& cause)
 : WebDriverException(what), m_cause(cause)
{

}

ErrorInResponseException::ErrorInResponseException(const ErrorInResponseException& e)
 : WebDriverException(e), m_cause(e.m_cause)
{

}

NoSuchElementException::NoSuchElementException(const std::string& what)
 : WebDriverException(what)
{

}

NoSuchElementException::NoSuchElementException(const NoSuchElementException& e)
 : WebDriverException(e)
{

}

NoSuchFrameException::NoSuchFrameException(const std::string& what)
 : WebDriverException(what)
{

}

NoSuchFrameException::NoSuchFrameException(const NoSuchFrameException& e)
 : WebDriverException(e)
{

}

TimeoutException::TimeoutException(const std::string& what)
 : WebDriverException(what)
{

}

TimeoutException::TimeoutException(const NoSuchFrameException& e)
 : WebDriverException(e)
{

}

StaleElementReferenceException::StaleElementReferenceException(const std::string& what)
 : WebDriverException(what)
{

}

StaleElementReferenceException::StaleElementReferenceException(const NoSuchFrameException& e)
 : WebDriverException(e)
{

}


} /* namespace selenium */


