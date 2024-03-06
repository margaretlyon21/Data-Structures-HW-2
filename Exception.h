#ifndef EXCEP_H
#define EXCEP_H

#include <stdexcept>

class stackOverflow : public std::exception{
  public:
    const char* message() {
      return "Stack Overflow";
    }

};
class stackUnderflow : public std::exception{
  public:
    const char* message() {
      return "Stack Underflow";
    }
};

class queueOverflow : public std::exception{
  public:
    const char* message() {
      return "Queue Overflow";
    }

};
class queueUnderflow : public std::exception{
  public:
    const char* message() {
      return "Queue Underflow";
    }
};

#endif