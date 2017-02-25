#pragma once

#include <algorithm>
#include <string>
#include <initializer_list>
#include <sstream>
#include <iterator>

namespace qd { namespace string_alg {
    std::string to_lower(std::string source)
    {
        std::transform(
            source.cbegin(),
            source.cend(),
            source.begin(),
            ::tolower);
        return source;
    }
} }