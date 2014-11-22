/*
 * Copyright (C) 2014 Patrick Heeb
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
