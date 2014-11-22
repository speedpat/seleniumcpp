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

#ifndef BY_H_
#define BY_H_

#include <ostream>
#include <json/json.h>

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

	operator Json::Value() const;

protected:
	By(const std::string& selector);
	//virtual ~By() = default;

private:
	std::string m_selector;

};


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
