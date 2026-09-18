#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main() {
  std::vector vec{1,2,3,4,5,6};
  std::vector<int> even_elements;
  std::copy_if(vec.begin(),vec.end(),std::back_inserter(even_elements),
  [](auto i){
    if (i%2==0) return true; 
    else return false;
    });
  
  std::copy(even_elements.begin(),even_elements.end(),
            std::ostream_iterator<int>(std::cout," "));
  return 0;
}