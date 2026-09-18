#include <iostream>
#include <string>
#include <map>
#include <set>

int main(){

  // --- set ---
  std::set<int> my_set {4,1,7,2}; // inserted element will be sorted
  
  my_set.insert(0); // inserted before 1
  auto value_ite = my_set.find(1); // returns an iterator
  
  if (value_ite != my_set.end()) {
    std::cout << *value_ite;
    //*value_ite += 1; // KO cannot modify set value
  }
 
  // Check if insertion already occurs

  {
    auto [iterator,is_inserted] = my_set.insert(7);
    if (! is_inserted) std::cout << "Insertion didn't occur for 7" << std::endl;
    else std::cout << (*iterator) << std::endl;
  }
  {
    auto [iterator,is_inserted] = my_set.insert(8);
    if (! is_inserted) std::cout << "Insertion didn't occur for 9" << std::endl;
    else std::cout << (*iterator) << std::endl;
  }
  my_set.clear();

  // --- map ---
  std::map<std::string,double> my_map { {"val1",1.0},{"val2",2.0} };

  my_map.insert({"val3",3.0});
  my_map.insert(std::make_pair("val4",4.0));

  auto val_ite = my_map.find("val2");
  if (val_ite != my_map.end()) {
    std::cout << (*val_ite).second << std::endl;
    (*val_ite).second +=1;
    std::cout << (*val_ite).second << std::endl;
  }

  // Check if insertion already occurs

{
  auto [iterator,is_inserted] = my_map.insert({"val2",2.0});
  if (! is_inserted) std::cout << "Insertion didn't occur for key \"val2\"" << std::endl;
  else std::cout << (*iterator).second;
}
{
  auto [iterator,is_inserted] = my_map.insert({"val5",5.0});
  if (! is_inserted) std::cout << "Insertion didn't occur";
  else std::cout << (*iterator).second;
}

  return 0;
}