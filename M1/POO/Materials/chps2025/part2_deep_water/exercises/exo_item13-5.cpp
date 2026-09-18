#include <iostream>
#include <vector>

struct MyContainer {
  std::vector<int> m_values;

  auto begin() {return m_values.begin();}
  auto end() {return m_values.end();}
};

int main(){

  MyContainer c { {1,2,3} };
  for (auto val : c) {
    std::cout << val << " " ;
  }
  return 0;
}