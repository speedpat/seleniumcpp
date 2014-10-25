#ifndef HAMCREST_ANYTHING_H
#define HAMCREST_ANYTHING_H

#include <hamcrest/hc_description.h>
#include "hamcrest/hc_matcher.h"

namespace hamcrest {


/**
    A matcher that always returns true
*/
template <typename T>
struct anything : public matcher<T>
{
    /**
        Create matcher that always evaluates to true

        @param description A meaningful string used when describing itself.
    */
    explicit anything(const std::string& description = "ANYTHING") : description_m(description) { }

    virtual ~anything() = default;

    virtual bool operator()(const T& /*item*/) const { return true; }
    
    virtual void describe_to(description_t& description) const { description.append_text(description_m); }

    virtual matcher<T>* copy() const { return new anything(*this); }

    std::string description_m;
};

HAMCREST_TAG_MATCHER(anything);


}   // namespace hamcrest

#endif  // HAMCREST_ANYTHING_H
