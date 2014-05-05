#include "Exception.hpp"

Exception::Exception(const std::string &str) throw() : std::runtime_error(str), _what(str)
{

}

Exception::~Exception() throw()
{

}

const char* Exception::what() const throw()
{
  return (_what.c_str());
}
