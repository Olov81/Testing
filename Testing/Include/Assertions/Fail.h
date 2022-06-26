#pragma once

#include <functional>
#include <sstream>

inline void fail(long line, const char* file,  const std::function<void(std::stringstream&)>& appendMessage)
{
    std::stringstream s;
    s << file << "(" << line << "):" << std::endl;
    appendMessage(s);
    throw std::exception(s.str().c_str());
}
