/*
 * switch_to.cpp
 *
 *  Created on: Sep 17, 2014
 *      Author: speedpat
 */

#include "selenium/switch_to.hpp"
#include "selenium/alert.hpp"
#include "selenium/command_executor.hpp"




namespace selenium
{

SwitchTo::SwitchTo(CommandExecutor& driver)
 : m_driver(driver)
{

}

Alert SwitchTo::alert()
{
  return Alert(m_driver);
}

void SwitchTo::defaultContent()
{
  CommandParameters params;
  params.add("id", ::boost::optional<std::string>(::boost::none));

  m_driver.execute(Command::SWITCH_TO_FRAME, params);
}

SwitchTo& SwitchTo::frame(const std::string& frameReference)
{
  CommandParameters params;
  params.add("id", frameReference);

  m_driver.execute(Command::SWITCH_TO_FRAME, params);
  return *this;
}

SwitchTo& SwitchTo::frame(const WebElement& frameReference)
{
  CommandParameters params;
  params.add("id", frameReference);

  m_driver.execute(Command::SWITCH_TO_FRAME, params);
  return *this;
}

SwitchTo& SwitchTo::parentFrame()
{
  m_driver.execute(Command::SWITCH_TO_PARENT_FRAME);
  return *this;
}

SwitchTo& SwitchTo::window(const std::string& windowName)
{
  CommandParameters params;
  params.add("name", windowName);

  m_driver.execute(Command::SWITCH_TO_WINDOW, params);
  return *this;
}

WebElement SwitchTo::activeElement()
{
  return m_driver.execute<WebElement>(Command::GET_ACTIVE_ELEMENT);
}


} /* namespace selenium */



/*  Specialize translator_between so that it uses our custom translator for
    bool value types. Specialization must be in boost::property_tree
    namespace. */
namespace boost {
namespace property_tree {

template <typename Ch, typename Traits>
struct customize_stream<Ch, Traits, ::boost::optional<std::string>, void>
{
    static void insert(std::basic_ostream<Ch, Traits>& s, ::boost::optional<std::string> e) {
      if (e.is_initialized())
      {
        s << e.get();
      }
      else
      {
        s << "null";
      }
    }
    static void extract(std::basic_istream<Ch,Traits>& s, boost::optional<std::string>& e){
        std::string str;
        s >> str;
        if (str == "null")
        {
          e = ::boost::none;
        }
        else
        {
          e = str;
        }
        if(!s.eof()) {
            s >> std::ws;
        }
    }
};


} // namespace property_tree
} // namespace boost

