#pragma once

#include <numeric>
#include <string>
#include <initializer_list>

namespace qd { namespace string_alg {
    std::string join(
        const std::initializer_list<std::string>& source, 
        const char delim)
    {
        if (source.size() == 0) {
            return "";
        }

        std::string buf = *source.begin();
        for (auto it = std::next(source.begin());it != source.end(); ++it) {
            buf.append(delim + *it);
        }

        return buf;
    }
} }