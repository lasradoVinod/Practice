// Exception class


#ifndef Exception_class
#define Exception_class

#include <string>

class Exception
{

 public:
  Exception (std::string s, int level ) : m_s ( s ) {lvl = level;}
  ~Exception (){};

  std::string description() { return m_s; }
  int level() { return lvl; }

 private:

  std::string m_s;
  int lvl;

};

#endif
