#ifndef HAMCREST_UNITTEST_H
#define HAMCREST_UNITTEST_H

#include "hamcrest/hc_description.h"

/// Integration with gtest
#define ASSERT_THAT(actual, matcher)                                                                \
    do                                                                                              \
    {                                                                                               \
        if (!matcher(actual))                                                                       \
        {                                                                                           \
            hamcrest::description_t _description;                                                   \
            _description.append_text("Expected: ")                                                  \
                        .append_description_of(matcher)                                             \
                        .append_text(", got: ")                                                     \
                        .append_value(actual);                                                      \
            FAIL() << _description.description_m;                                                   \
        }                                                                                           \
    } while (0)

#define ASSERT_THAT_NOT(actual, matcher)                                                                \
    do                                                                                              \
    {                                                                                               \
        if (matcher(actual))                                                                       \
        {                                                                                           \
            description_t _description;                                                             \
            _description.append_text("Not Expected: ")                                                  \
                        .append_description_of(matcher)                                             \
                        .append_text(", got: ")                                                     \
                        .append_value(actual);                                                      \
            FAIL() << _description.description_m;                                                   \
        }                                                                                           \
    } while (0)


#define ASSERT_DESCRIPTION(expected, matcher)                                                       \
    do                                                                                              \
    {                                                                                               \
        description_t _description;                                                                 \
        matcher.describe_to(_description);                                                          \
        ASSERT_EQ(expected, _description.description_m);                           \
    } while (0)

#endif  // HAMCREST_UNITTEST_H
