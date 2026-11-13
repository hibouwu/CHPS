#include <stdio.h>

/*
 * C++ Design Patterns: BUILDER
 * http://www.plantuml.com/plantuml/uml/hL9HJiCm3FtFAIpniS5KAdwdgXhjG492Q1fmWBJre2XjAiT1JC21UevUZ2pB1c9eN-GdplFpUqxYcM59R1ibuX5aZpUtywibZ6BXLgcaCJ2l2KlM1Ey2t8gWiBMgaFnf0gLk3PCjUNmQ48ESRIdZiEyo2zALOy8JSWXTqQSGTSj8AraYX8BWTRBrMaZYIyVy1MM7KExrGkEvRaj2ng1vNPFX83mv4Fu9POTGleTSxqiqLl4HgtjqhrBzkvVOVyLP1C5AX1sIZoZwyyh76A5J8LhD2DB0tOMtJeeqARNID2MzbYfJ5jDGaSG-aIPnaUwu3-iEfni0SaB9jMwbyha5KeCCIe8P-awIpq651fgXvsVj8i-hy7kEDem8R0kwU45sUDCfV4FFwz0oo5TT4rJrQZNqX2qxDSAEXjwuWtSmvmBT-syk9MOkSjFz1G00
 *
 */

#include <iostream>
#include <string>

class Product {
public:
  void partA(const std::string &part) {
    part_a = part;
  }
  void partB(const std::string &part) {
    part_b = part;
  }
  void partC(const std::string &part) {
    part_c = part;
  }

  void checkProduct() {
    std::cout << part_a + " " + part_b + " " + part_c + " have been created" << std::endl;
  }

private:
  std::string part_a;
  std::string part_b;
  std::string part_c;
};

class Builder {
public:
  Builder() { std::cout << "Constructor Builder" << std::endl; }
  virtual ~Builder() {}
  Product getProduct() { return product; }

  virtual void buildPartA() =0;
  virtual void buildPartB() =0;
  virtual void buildPartC() =0;

protected:
  Product product;
};

class ConcreateBuilder1 : public Builder {
public:
  ConcreateBuilder1() { std::cout << "Constructor ConcreateBuilder-1" << std::endl; }
  ~ConcreateBuilder1() {}

  void buildPartA() {
    product.partA("1-A");
  }
  void buildPartB() {
    product.partB("1-B");
  }
  void buildPartC() {
    product.partC("1-C");
  }

};

class ConcreateBuilder2 : public Builder {
public:
  ConcreateBuilder2() { std::cout << "Constructor ConcreateBuilder-2" << std::endl; }
  ~ConcreateBuilder2() {}

  void buildPartA() {
    product.partA("2-A");
  }
  void buildPartB() {
    product.partB("2-B");
  }
  void buildPartC() {
    product.partC("2-C");
  }

};

class Director {
public:
  Director() { std::cout << "Constructor Director" << std::endl; }
  ~Director() {
    if (builder) {
      delete builder;
    }
  }

  void setBuilder(Builder *b) {
    if (builder) {
      delete builder;
    }
    builder = b;
  }

  Product getProduct() { 
      Builder *builder_ok = dynamic_cast<Builder*>(builder);
      if (builder_ok) {
      return builder->getProduct();
        } else { 
            std::cout << "Director does construct : empty_product !" << std::endl;
            Product empty_product;
            return empty_product;} 
      }

  void construct() {
    Builder* builder_ok = dynamic_cast<Builder*>(builder);
    std::cout << "Director does construct" << std::endl;
    if (builder_ok) {
    builder_ok->buildPartA();
    builder_ok->buildPartB();
    builder_ok->buildPartC();
    } else {
        std::cout << "Director does construct : no method available !" << std::endl;
    }
  }

private:
  Builder *builder = nullptr;
};

int main(int argc, char* argv[]) {
  Director director;
  director.setBuilder(new ConcreateBuilder1);
  director.construct();

  Product product1 = director.getProduct();
  product1.checkProduct();

  director.setBuilder(new ConcreateBuilder2);
  director.construct();
  Product product2 = director.getProduct();
  product2.checkProduct();

  director.setBuilder(0);
  director.construct();
  Product product3 = director.getProduct();
  product3.checkProduct();
}