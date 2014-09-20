/*
 * By.h
 *
 *  Created on: Sep 7, 2014
 *      Author: speedpat
 */

#ifndef BY_H_
#define BY_H_

#include <ostream>

namespace selenium {

class Locator;

class By {
public:
	static const By& ID;
	static const By& NAME;
	static const By& LINK_TEXT;
	static const By& PARTIAL_LINK_TEXT;
	static const By& TAG_NAME;
	static const By& XPATH;
	static const By& CLASS_NAME;
	static const By& CSS_SELECTOR;

	static Locator id(const std::string& id);
	static Locator name(const std::string& name);
	static Locator linkText(const std::string& linkText);
	static Locator partialLinkText(const std::string& linkText);
	static Locator tagName(const std::string& tagName);
	static Locator xpath(const std::string& xpath);
	static Locator className(const std::string& className);
	static Locator cssSelector(const std::string& selector);

protected:
	By(const std::string& selector);
	//virtual ~By() = default;

private:
	std::string m_selector;

	friend std::ostream& operator<<(std::ostream& os, const By& by);
};

std::ostream& operator<< (std::ostream& stream, const By& by);

class Locator
{
public:
  Locator(const By& by, const std::string& value);
  ~Locator() = default;

  const By& getClause() const;
  const std::string& getValue() const;

private:
  const By& m_by;
  const std::string m_value;
};


} /* namespace selenium */

#endif /* BY_H_ */
