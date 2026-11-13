#include <stdio.h>

/*
 * C++ Design Patterns: COMPOSITE
 * https://www.plantuml.com/plantuml/uml/VL7BRjH04BpxArhYu8J5hBYkh5LWnG49259oNxN75JDe7bPFpqeHy3_m7Vanx65Z0alIfvcgckegpKLI5itULUkQTfSVFbrUlRj-I_MwciO6XTom0UsY7sD0KFfQqJGD-NrWZt9vHd64iDeOpiwF2FVzcGraQFFxRRAAyuKL-7Z0gU183z3TP-kAWvq4DkWzXP3zl0kJr_UgCevJelVWcoNOAFR00_QsBy3g9Dpg_oPBYh-T57ipPn44Ei1ebCTid-oyUhhpwj7Eft7__4NxhMbA-N-nnVq1qJJF7-1LY0hYH1zVbIrjjsrDT54s4c_PlN4PsqNThWkrRTVTzbvzVJjYCmDqfPADPc5NkDSfmNUE1r1Vn-uBD57F8L4Ee7JKeaXPkYX81a7nWbnj-xkV82Ib7jHnO6SJf4XTpSRS_KZKJ3vMsGeevbatICpZikjbXT3JNAwwc4xPkry0
 *
 */

#include <iostream>
#include <string>
#include <vector>

class Component {
public:
  std::string  m_name;
  Component() { std::cout << "Constructor Component" << std::endl; }
  virtual ~Component() {}
  virtual void operation() = 0;

  virtual void add(Component *) {};
  virtual void remove(Component *) {};
  virtual Component* getChild(int) { return nullptr; };
  
  virtual void enumerate() = 0 ;
};

class Leaf : public Component {
public:
  Leaf(int id) : private_id(id) { std::cout << "Constructor Leaf" << std::endl; }
  ~Leaf() {}

  void operation() { std::cout << "This is operation from Leaf: " << private_id << std::endl; }
  void enumerate() { std::cout << "Enumerate from Leaf: " << private_id << std::endl;};
private:
  int private_id;
};

class Composite : public Component {
public:
  Composite() { std::cout << "Constructor Composite" << std::endl; }
  ~Composite() {
    for (unsigned int i = 0; i < private_children.size(); ++i) {
      delete private_children[i];
    }
  }

  void operation() {
    std::cout << "size of children: " << private_children.size() << std::endl;
    for (unsigned int i = 0; i < private_children.size(); ++i) {
      private_children[i]->operation();
    }
  }

  void add(Component *c) {
    private_children.push_back(c);
  }

  void remove(Component *c) {
    for (auto iter = private_children.begin(); iter != private_children.end(); ++iter) {
      if (*iter == c) {
        private_children.erase(iter);
      }
    }
  }

  Component* getChild(unsigned int idx) {
    return idx < private_children.size() ? private_children[idx] : nullptr;
  }
 
 void group(const std::string &n) {m_name=n;};
 void enumerate() {
        std::cout << "Group " << m_name.c_str() << " contains:" << std::endl;
        for (auto &&o : private_children)
            o->enumerate();
    }
private:
  std::vector<Component*> private_children;
};

int main() {
  Composite composite;
  composite.group("principal");
  for (unsigned int i = 0; i < 3; ++i) {
    composite.add(new Leaf(i));
  }

  Composite composite2;
  composite2.group("secondaire");

  composite.add(&composite2);

  composite.remove(0);
  composite.operation();

  Component *component1 = composite.getChild(0);
  component1->operation();

  Component *component2 = composite.getChild(3);
  component2->operation();
  composite.enumerate();
}