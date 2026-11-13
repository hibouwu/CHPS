/*
 * C++ Design Patterns: ITERATOR
 * 
 * http://www.plantuml.com/plantuml/uml/VP71RjD048Rl-nGZzP1MKOYuHfRL1ZZa0gY41vXuf-wYzMoPdQqQeE_2aJo7NuoDWqrIHzsJv_-_yJ-ZkOwAegdnPZw1rVh3xStwqorCvYQ_ocECyCuxOZN6iPBSOKLmKzT2DIh1JmFvNK0bbCjL1b23N5wPvw4xS3QLNlPCHpsmsCDAJ_eFg4cpstJEYe_KB-u7NLujuAiRLBIsPuU_F1_FtESC8tD6Jl0Bk7CIJxK3wkBxmDGPon1yltCI8TPHx6Zr5z7JSVH1FXy_FHi_VIt-tba2QXvq2mqr6v9epE6AC9kL_yztBFP3ci65ujTiDhwVwSbJV-Wt79G08tnysqrQRCgY2Zx8Gi8M_T8dAdkuc7TEMSmtPG-ljm-qs0kmf7jyT47miF9daeOKx0IhgjrP4i3q13OmjpkAMKyCM4kxgr6x1alG8BlsZn34TlSz4QiZxtE5704VWnFeoFOtL84PdMRK8qILL6dAXQMZXEnDmkORwHj3R66_gBdENwdnVm40http://www.plantuml.com/plantuml/uml/VP71RjD048Rl-nGZzP1MKOYuHfRL1ZZa0gY41vXuf-wYzMoPdQqQeE_2aJo7NuoDWqrIHzsJv_-_yJ-ZkOwAegdnPZw1rVh3xStwqorCvYQ_ocECyCuxOZN6iPBSOKLmKzT2DIh1JmFvNK0bbCjL1b23N5wPvw4xS3QLNlPCHpsmsCDAJ_eFg4cpstJEYe_KB-u7NLujuAiRLBIsPuU_F1_FtESC8tD6Jl0Bk7CIJxK3wkBxmDGPon1yltCI8TPHx6Zr5z7JSVH1FXy_FHi_VIt-tba2QXvq2mqr6v9epE6AC9kL_yztBFP3ci65ujTiDhwVwSbJV-Wt79G08tnysqrQRCgY2Zx8Gi8M_T8dAdkuc7TEMSmtPG-ljm-qs0kmf7jyT47miF9daeOKx0IhgjrP4i3q13OmjpkAMKyCM4kxgr6x1alG8BlsZn34TlSz4QiZxtE5704VWnFeoFOtL84PdMRK8qILL6dAXQMZXEnDmkORwHj3R66_gBdENwdnVm40
 * 2021 / JMB
 *
 */

#include <iostream>
#include <vector>

class Iterator;
class ConcreteIterator;

class Aggregate {
public:
  virtual ~Aggregate() {}
  virtual Iterator* createIterator() = 0;
};

class ConcreteAggregate : public Aggregate {
public:
  ConcreteAggregate(int N) {
    //do a memory allocation  
    v.reserve(N);
    for (int i = 0; i < N; ++i) {
      //direct move in memory of i value 
      v.emplace_back(i);
    }
  }
  ~ConcreteAggregate() {}

  Iterator* createIterator();

  int getItem(int idx) { return v.at(idx); }

  unsigned int getSize() { return v.size(); }
  //emplace_back ==> move in memory
  void addItem(int obj) { v.emplace_back(obj); }

private:
  std::vector<int> v;
};

class Iterator {
public:
  virtual ~Iterator() {}

  virtual void first() = 0;
  virtual void next() = 0;
  virtual bool isDone() = 0;
  virtual int currentItem() = 0;
};

class ConcreteIterator : public Iterator {
public:
  ConcreteIterator(ConcreteAggregate *ag)
  : p_cag(ag), p_index(0) {}

  void first() {
    p_index = 0;
  }

  void next() {
    ++p_index;
  }

  bool isDone() {
    return p_index >= p_cag->getSize();
  }

  int currentItem() {
    return p_cag->getItem(p_index);
  }
private:
  ConcreteAggregate *p_cag;
  int p_index;
};

Iterator *ConcreteAggregate::createIterator() {
  std::cout << "createIterator" << std::endl;
  return new ConcreteIterator(this);
}

int main() {
  ConcreteAggregate *concreteAggregate = new ConcreteAggregate(10);
  concreteAggregate->addItem(123);

  Iterator* it = concreteAggregate->createIterator();
  for ( ; !it->isDone(); it->next()) {
    std::cout << "Item value: " << it->currentItem() << std::endl;
  }

}


