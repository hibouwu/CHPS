#include <stdio.h>

/*
 * C++ Design Patterns: PROXY
 * http://www.plantuml.com/plantuml/uml/RO_FIiD06CJl-nGVUAWYCNWj8HJ5gvRMWvvainbnPV-attuh1lM1z3NwOgPf2otqEoqpls5cPqaqI_PEbHEQBnwUdcbIgk6CqodHhRC8efGD0dxL1hJCpJkCq9UYuSw8iSf8SdwXVlQX1RGxnYvFONEEd_qEAAXZ-w45BsaRF1Lxioq8lfEUF7m3JahjUwhleZWiFZR6AdMugzg9D2L6n-lVX21QR0pKGcs_JKLHxw8gH07fHFVNuxAggIiJNUGfnrwx6vTHZsHLZd9TbKsz9n_x3jEDG4lXR2IpTgDt5upkKdQW72WEmuGAGY0VMv2tpD4oGKQMaJeO0GsqN_zva8b1M0kjCiZ0PLiOUwKGMjgCLRFXbRtx1m00
 *
 */
#include <iostream>
// A subject exposes a contract
class Subject {
public:
  virtual ~Subject() {}
  virtual void request() = 0;
};

// Implementation of the contract
class RealSubject : public Subject {
public:
  void request() {
    std::cout << "RealSubject Request" << std::endl;
  }
};

// A proxy encapsulates an already known class - with the same contract as Subject
class Proxy : public Subject
{
public:
  Proxy()
  {
    private_subject = new RealSubject();
  }

  ~Proxy()
  {
    delete private_subject;
  }

  void request()
  {
    std::cout << "Do Proxy Request" << std::endl;
    private_subject->request();
  }

private:
  RealSubject *private_subject;
};


int main()
{
  Proxy *proxy = new Proxy();
  proxy->request();
  delete proxy;
}