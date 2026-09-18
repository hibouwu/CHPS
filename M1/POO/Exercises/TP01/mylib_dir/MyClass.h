#ifndef MYCLASS_H
#define MYCLASS_H

#include <string>

#if defined _WIN32 || defined __CYGWIN__
  #ifdef MYLIB_BUILD
    #define MYLIB_API __declspec(dllexport)
  #else
    #define MYLIB_API __declspec(dllimport)
  #endif
#elif defined(__GNUC__) && __GNUC__ >= 4
  #define MYLIB_API __attribute__((visibility("default")))
#else
  #define MYLIB_API
#endif

namespace MyLib {
    class MYLIB_API MyClass {
    public:
        MyClass();
        void print(std::string message);
        int value() const;
    };
}

#endif // MYCLASS_H
