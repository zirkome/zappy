#ifndef _EXCEPTION_H_
# define _EXCEPTION_H_

# include <string>
# include <stdexcept>

class Exception : public std::runtime_error
{
public:
  explicit Exception(const std::string &str) throw();
  virtual ~Exception() throw();
  virtual const char* what() const throw();

private:
  std::string	_what;
};

#endif /* _EXCEPTION_H_ */
