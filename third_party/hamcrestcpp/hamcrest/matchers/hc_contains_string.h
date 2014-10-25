#ifndef HAMCREST_CONTAINS_H
#define HAMCREST_CONTAINS_H

#ifndef HAMCREST_DESCRIPTION_H
#include "hc_description.h"
#endif

#ifndef HAMCREST_MATCHER_H
#include "hc_matcher.h"
#endif

namespace hamcrest {


/**
    Is the value equal to another value
*/
struct contains_t : public matcher<std::string>
{
    explicit contains_t(const std::string& expected) : expected_m(expected) { }
    
    bool operator()(const std::string& actual) const
    {
      return actual.find(expected_m) != std::string::npos;
    }
    
    void describe_to(description_t& description) const { description.append_value(expected_m); }

    matcher<std::string>* copy() const { return new contains_t(*this); }

    std::string expected_m;
};

//HAMCREST_TAG_MATCHER(contains_t);


/// Helper function, deducing the type
contains_t contains(const std::string& expected) { return contains_t(expected); }

contains_t contains(const char* expected) { return contains_t(expected); }



}   // namespace hamcrest

#endif  // HAMCREST_CONTAINS_H
