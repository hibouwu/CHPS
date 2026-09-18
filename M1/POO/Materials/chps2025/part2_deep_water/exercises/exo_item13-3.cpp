#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <map>


std::ostream& operator<< (std::ostream & os, std::pair<std::string,int> const& pair)
{
  os << " first = "<< pair.first;
  os << " second = "<< pair.second; 
  return os;
}

template <typename Container>
void _print(Container const& container) {
  for (auto iterator = container.begin(); iterator != container.end(); ++iterator) {
    std::cout << *iterator << " " ;
  }
  std::cout << std::endl;
}

int main(){
  std::array<int,4> array {1,2,3,4};
  std::vector<int> vector {5,6,7,8};
  std::set<int> set {9,10,11,12};
  std::map<std::string,int> map { {"13",13}, {"14",14}, {"15",15}};

  _print(array);
  _print(vector);
  _print(set);
  _print(map);

  

  return 0;
}