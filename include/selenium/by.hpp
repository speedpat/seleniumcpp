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

protected:
	By(const std::string& selector);
	//virtual ~By() = default;

private:
	std::string m_selector;

	friend std::ostream& operator<<(std::ostream& os, const By& by);
};

std::ostream& operator<< (std::ostream& stream, const By& by);


} /* namespace selenium */

#endif /* BY_H_ */
