/*
 * wait.cpp
 *
 *  Created on: Sep 15, 2014
 *      Author: speedpat
 */

#include <chrono>
#include <selenium/wait.hpp>

namespace selenium
{

Wait::Wait(WebDriver& driver, unsigned int timeout, unsigned int sleeper)
 : m_timeout(timeout), m_sleeper(sleeper), m_driver(driver)
{

}


} /* namespace selenium */
