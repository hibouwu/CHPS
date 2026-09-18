#include <iostream>

void print_while(){
  int i = 0;
  std::cout << "Print while" << std::endl;
  while (i < 10) {
    std::cout << "i = "<< i++ << std::endl;
  }
}

void print_do(){
  int i = 0;
    std::cout << "Print Do" << std::endl;
  do {
    std::cout << "i = "<< i++ << std::endl;
  } while (i < 10);

}

void print_if(int i=0)
{
  if (i==0) print_do();
  else print_while();
}

enum class Print {
  While, Do
};

void print_switch(Print print_type){
  switch (print_type)
  {
  case Print::While:
    print_while();
    break;
  case Print::Do:
    print_do();
  }
}

int main(){
  print_if(0);
  print_switch(Print::While);
  
}
  



