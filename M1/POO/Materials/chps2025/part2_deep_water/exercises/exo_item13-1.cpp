#include <iostream>
#include <array>
#include <vector>

template <typename Container>
void _print(Container const& container) {
  for (size_t i = 0; i < container.size();++i) {
    std::cout << container[i] << " " ;
    std::cout << std::endl;
  }
}

int main(){

  // array
  std::array<int,4> array {1,2,2,3};

  std::cout << "array size " << array.size() << std::endl;
    
  std::cout << "array values " ;
  _print(array);
  // increment values
  for (size_t i = 0; i < array.size();++i) {
    array[i] += 1;
  }
  std::cout << std::endl << "array incremented values " ;
  _print(array);

  // vector
  std::vector<int> vector {1,2,2,3};
  _print(vector);
  std::cout << "vector size " << vector.size()   << std::endl;
  std::cout << "vector capacity " << vector.capacity() << std::endl;
  
  vector.clear();
  vector.resize(5,0);
  std::cout << "vector size " << vector.size()   << std::endl;
  std::cout << "vector capacity " << vector.capacity() << std::endl;
  _print(vector);
  for (size_t i = 0; i < vector.size(); ++i) {
    vector[i] = i;
  }
  _print(vector);

  vector.clear();
  vector.reserve(5);
  std::cout << "vector size " << vector.size()   << std::endl;
  std::cout << "vector capacity " << vector.capacity() << std::endl;
  std::cout << "vector has values ?" << std::endl;
  _print(vector);
  for (size_t i = 0; i < vector.size(); ++i) {
    vector[i] = i;
  }
  std::cout << "vector has values ?" << std::endl;
  _print(vector);
  for (size_t i = 0; i < vector.capacity(); ++i) {
    vector.push_back(i);
  }
  std::cout << "vector has values ?" << std::endl;
  _print(vector);
  
  // The joke
  std::vector<int> vec{5,6};
  std::cout << "vec{5,6}" << std::endl;
  _print(vec);
  std::vector<int> vec2(5,6);
  std::cout << "vec(5,6)" << std::endl;
  _print(vec2);

  return 0;
}