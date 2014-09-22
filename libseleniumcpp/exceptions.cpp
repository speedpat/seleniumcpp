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


ErrorInResponseException::ErrorInResponseException(const std::string& what)
 : WebDriverException(what), m_cause("")
{

}

ErrorInResponseException::ErrorInResponseException(const std::string& what, const std::runtime_error& cause)
 : WebDriverException(what), m_cause(cause)
{

}

NoSuchElementException::NoSuchElementException(const std::string& what)
 : WebDriverException(what)
{

}

NoSuchFrameException::NoSuchFrameException(const std::string& what)
 : WebDriverException(what)
{

}

TimeoutException::TimeoutException(const std::string& what)
 : WebDriverException(what)
{

}

StaleElementReferenceException::StaleElementReferenceException(const std::string& what)
 : WebDriverException(what)
{

}

ElementNotVisibleException::ElementNotVisibleException(const std::string& what)
 : WebDriverException(what)
{

}

NoAlertPresentException::NoAlertPresentException(const std::string& what)
 : WebDriverException(what)
{

}

InvalidElementStateException::InvalidElementStateException(const std::string& what)
 : WebDriverException(what)
{

}

MoveTargetOutOfBoundsException::MoveTargetOutOfBoundsException(const std::string& what)
 : WebDriverException(what)
{

}

UnknownErrorException::UnknownErrorException(const std::string& what)
 : WebDriverException(what)
{

}

ElementIsNotSelectableException::ElementIsNotSelectableException(const std::string& what)
 : WebDriverException(what)
{

}

JavaScriptErrorException::JavaScriptErrorException(const std::string& what)
 : WebDriverException(what)
{

}

} /* namespace selenium */

