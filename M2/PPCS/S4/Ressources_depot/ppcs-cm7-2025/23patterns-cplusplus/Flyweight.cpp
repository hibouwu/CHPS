#include <stdio.h>

/*
 * C++ Design Patterns: FLYWEIGHT
 * https://www.plantuml.com/plantuml/uml/bL3DZjCm4BxxAKRYq1O85TTLLAr0Mq12N7OHueGSPzeQEUDePWn4m0F1Q-oBuLgXgOWgiLOEyNm_y_cx5hMigGjclO3jsuyVRjwyUdq7YxN9nmKh0jimV4M_F-ZMEeqym7S3-LIGA7ABZEsdplPbzWJsg2V-SZKEWvTfAiiLc9_6U5BadNKuBHYT7q7iaQtwI4jFWD-KFObtjseLLrax1diPF9AURf4Se-A_RXLuEZSOC_tVYlSa1ylONZQt8Jp4zk1R1Enw7Q33ha4MOsO5FwwcJYOKwXzLDNlcZ70nydnFdUbZYJFsENZHyfnaA2g25NZtl7HHDvlQnH3vYkDWmukGS7CIrki2RUfri_dBlXjwl3eEu5OvEKriGy5kY77lHHaXe41iFgCAj9O44Y78o4PeynU9xd-XF2rAPtlRX098wll8YfmrWBiTElKx-695Cxmedj0cwEv_TrYqckCyCqWj71zchlDVwi8V
 *
 */

#include <iostream>
#include <string>
#include <unordered_map>

class Flyweight {
public:
  virtual ~Flyweight() {}

  virtual void operation(const std::string& extrinsicState) = 0;
};

class ConcreteFlyweight : public Flyweight {
public:
  ConcreteFlyweight(const std::string& intrinsicState) :
    intrinsicState(intrinsicState) {
    std::cout << "ConcreteFlyweight intrinsicState: " << intrinsicState << std::endl;
  }
  ~ConcreteFlyweight() {}

  void operation(const std::string& extrinsicState) {
    std::cout << "ConcreteFlyweight operation extrinsicState: " << extrinsicState << std::endl;
  }

private:
  std::string intrinsicState;
};

class UnsharedConcreteFlyweight : public Flyweight {
public:
  UnsharedConcreteFlyweight(const std::string& allState) : private_allState(allState) {
    std::cout << "UnsharedConcreteFlyweight  allState: " << private_allState << std::endl;
  }
  void operation(const std::string& extrinsicState) {
    std::cout << "UnsharedConcreteFlyweight operation extrinsicState: " << extrinsicState << std::endl;
  }
private:
  std::string private_allState;
};

class FlyweightFactory {
public:
  ~FlyweightFactory() {
    for (auto it = mapflys.begin(); it != mapflys.end(); ++it) {
      delete it->second;
    }
    mapflys.clear();
  }

  Flyweight *getFlyweight(const std::string& key) {
    if (mapflys.find(key) != mapflys.end()) {
      std::cout << "Key : " << key << ", already exist" << std::endl;
      return mapflys[key];
    }

    Flyweight *fly = new ConcreteFlyweight(key);
    mapflys.insert(std::make_pair(key, fly));
    std::cout << "New entry for key: " << key<< std::endl;
    return  fly;
  }

  void listFlyweights() const
    {
        size_t count = this->mapflys.size();
        std::cout << "\nFlyweightFactory: I have " << count << " flyweights:\n";
        for (auto& it: mapflys) {
                            // Do stuff
                            std::cout << it.first << ";";
                            }
        std::cout << std::endl;
    }

private:
  std::unordered_map<std::string, Flyweight*> mapflys;
};

int main() {
  FlyweightFactory *factory = new FlyweightFactory();
  factory->getFlyweight("Hello Greeting")->operation("Greeting the world");
  factory->getFlyweight("Hello")->operation("Greeting group");
  factory->getFlyweight("Hello")->operation("Greeting classroom");
  factory->listFlyweights();
  Flyweight* unsharedfly = new UnsharedConcreteFlyweight("Unshared");
  unsharedfly->operation("Greeting");
}