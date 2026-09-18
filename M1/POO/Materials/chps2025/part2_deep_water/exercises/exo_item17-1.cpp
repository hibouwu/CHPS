#include <iostream>
#include <memory>

void print_str(std::unique_ptr<std::string>& string_ptr) {
  std::cout << "string " << *string_ptr << std::endl;
  std::cout << "string * " << string_ptr.get() << std::endl;
}

int main() {
  auto string_uptr = std::make_unique<std::string>("Hello smart pointer world");
  print_str(string_uptr);
  auto string_uptr2 = std::move(string_uptr);
  print_str(string_uptr2);
  return 0;
}