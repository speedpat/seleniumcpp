/*
 * selenium_testcase.cpp
 *
 *  Created on: Sep 18, 2014
 *      Author: speedpat
 */

#include "selenium/selenium.hpp"
#include "selenium_testcase.hpp"
#include "test_environment.hpp"

namespace selenium
{

WebDriver* SeleniumTestCase::s_driver = nullptr;

SeleniumTestCase::SeleniumTestCase()
 : m_wait(nullptr)
{

}

SeleniumTestCase::~SeleniumTestCase()
{
}

void SeleniumTestCase::SetUpTestCase()
{
  s_driver = new WebDriver(testEnvironment().driverUrl(), DesiredCapabilities::FIREFOX);
}

void SeleniumTestCase::TearDownTestCase()
{
  if (s_driver)
  {
    s_driver->quit();
    delete s_driver;
    s_driver = nullptr;
  }
}

void SeleniumTestCase::SetUp()
{
  m_wait = new Wait(*s_driver, 5);
}

void SeleniumTestCase::TearDown()
{
  delete m_wait;
  m_wait = nullptr;
}

TestEnvironment& SeleniumTestCase::testEnvironment()
{
  return *selenium::TestEnvironment::s_testEnvironment;
}

Pages& SeleniumTestCase::pages()
{
  return testEnvironment().pages();
}

std::string SeleniumTestCase::whereIs(const std::string& relativePath)
{
  return testEnvironment().whereIs(relativePath);
}

WebDriver& SeleniumTestCase::webDriver()
{
  if (SeleniumTestCase::s_driver == nullptr)
  {
    throw WebDriverException("illegal state, not properly intialized");
  }
  return *SeleniumTestCase::s_driver;
}

Wait& SeleniumTestCase::wait()
{
  return *m_wait;
}

void SeleniumTestCase::assertThat(::testing::AssertionResult result)
{
  ASSERT_TRUE(result);
}

::testing::AssertionResult SeleniumTestCase::equalsIgnoreCase(Attribute attribute, const char* value)
{
  if (attribute.isConvertibleTo(Json::stringValue))
  {
    std::string attributeValue = attribute.asString();
    std::transform(attributeValue.begin(), attributeValue.end(), attributeValue.begin(), ::tolower);
    if (attributeValue == value)
    {
      return ::testing::AssertionSuccess();
    }
  }
  return ::testing::AssertionFailure();
}

::testing::AssertionResult SeleniumTestCase::equalsIgnoreCase(const char* value, const std::string& val2)
{
    std::string val2str = val2;
    std::transform(val2str.begin(), val2str.end(), val2str.begin(), ::tolower);
    if (val2str  == value)
    {
      return ::testing::AssertionSuccess();
    }
  return ::testing::AssertionFailure();
}


 ::testing::AssertionResult SeleniumTestCase::equals(Attribute attribute, const char* value)
{
  if (attribute.isConvertibleTo(Json::stringValue))
  {
    std::string attributeValue = attribute.asString();
    if (attributeValue == value)
    {
      return ::testing::AssertionSuccess();
    }
  }
  return ::testing::AssertionFailure();
}

 ::testing::AssertionResult SeleniumTestCase::equals(Attribute attribute, const std::string& value)
 {
   if (attribute.isConvertibleTo(Json::stringValue))
   {
     std::string attributeValue = attribute.asString();
     if (attributeValue == value)
     {
       return ::testing::AssertionSuccess();
     }
   }
   return ::testing::AssertionFailure();
}


 ::testing::AssertionResult SeleniumTestCase::equals(const char* value, Attribute attribute)
{
  return equals(attribute, value);
}

 ::testing::AssertionResult SeleniumTestCase::equals(Response& resp, Response& result)
 {
   if (resp.type() == result.type())
   {
     if (resp == result)
     {
       return ::testing::AssertionSuccess();
     }
   }
   return ::testing::AssertionFailure();
 }

 ::testing::AssertionResult SeleniumTestCase::equals(Response& resp, selenium::ScriptResult result)
 {
   if (resp.type() == result.type())
   {
     if (resp == result)
     {
       return ::testing::AssertionSuccess();
     }
   }
   return ::testing::AssertionFailure();
 }

 ::testing::AssertionResult SeleniumTestCase::equals(const char* val1, const char* val2)
{
    std::string val1str = val1;
    std::string val2str = val2;
    if (val1str == val2str)
    {
      return ::testing::AssertionSuccess();
    }
  return ::testing::AssertionFailure();
}

 ::testing::AssertionResult SeleniumTestCase::equals(const char* val1, const std::string val2)
{
  return equals(val1, val2.data());
}

 ::testing::AssertionResult SeleniumTestCase::equals(const std::string val1, const std::string val2)
{
  return equals(val1.data(), val2.data());
}

 ::testing::AssertionResult SeleniumTestCase::equals(const std::string val1, const char* val2)
{
  return equals(val1.data(), val2);
}

 ::testing::AssertionResult SeleniumTestCase::null(Response attribute)
 {
   return attribute.isNull() ? testing::AssertionSuccess() : testing::AssertionFailure();
 }

 ::testing::AssertionResult SeleniumTestCase::contains(const Response& attribute, const char* value)
 {
   std::string val = value;
   return contains(attribute, val);
 }

 ::testing::AssertionResult SeleniumTestCase::contains(const Response& attribute, const std::string& value)
 {
   if (attribute.isConvertibleTo(Json::stringValue))
   {
     std::string attributeValue = attribute.asString();
     if (attributeValue.find(value) != std::string::npos)
     {
       return ::testing::AssertionSuccess();
     }
   }
   return ::testing::AssertionFailure();
 }

 ::testing::AssertionResult SeleniumTestCase::equals(const Response& attribute, bool value)
 {
   if (attribute.isConvertibleTo(Json::booleanValue))
   {
     bool attributeValue = attribute.asBool();
     if (value == attributeValue)
     {
       return ::testing::AssertionSuccess();
     }
   }
   return ::testing::AssertionFailure();
 }

 ::testing::AssertionResult SeleniumTestCase::equals(const Response& attribute, int value)
 {
   if (attribute.isConvertibleTo(Json::intValue))
   {
     int attributeValue = attribute.asInt();
     if (value == attributeValue)
     {
       return ::testing::AssertionSuccess();
     }
   }
   return ::testing::AssertionFailure();
 }

} /* namespace selenium */
