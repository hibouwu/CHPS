#include <stdio.h>

/*
 * C++ Design Patterns: VISITOR
 * http://www.plantuml.com/plantuml/uml/jLB1RjGm4BtxAqRYiAsgTDKULr5KKZZq0gXKlQBPPBerSkmm7aUgW7_Xck_8Zv6uTaNLPIK4-93OyzwyDthsXHTa2PrHwnNSNdsykdb_3QkrcbTZq7kuD9giAAMj4DzXGt2hlHR7y5N1l5x1i9pV6kh8okiZRG5XS-bimoIKoyTxkFN2tRxWriVgUpRFKB8yIvudV-1vyfUUv__LyzTSK_qfLsmQwcLf7c2JKzypQFPEZGNqh0SK-jIYO9fdlrO2ToHlKF3ezzhrlz5E69H5VbPFbMz5yUAs3wBdwb42YgBAqQdqVzwGypc8rafP9mJeuTrPdBtSLcNZZECDkmSqjGbK9Uzo7O6gN6-hpBrvw6cp5A2cUnoqOpGHkwQUfz6J5O9W2Lm_ZOoYdONf1ymG6ks98P9xPD127RG41i4BXqO2KpoltFOpoUaZymDnHxBKsscyqrPpLBSk36JCCvl8zsWzDFTeTyHBLxpdkNarZMOQOowz2saCWrz2L8cV-4Hnf-LKaMrXoKbTpBlGcPy0
 *
 */

#include <iostream>

class Element;
class ConcreteElementA;
class ConcreteElementB;

class Visitor {
public:
    virtual ~Visitor() {}

    virtual void visitorElementA(ConcreteElementA* const element) = 0;
    virtual void visitorElementB(ConcreteElementB* const element) = 0;
};

class ConcreteVisitor1 : public Visitor {
public:
    ~ConcreteVisitor1() {}

    void visitorElementA(ConcreteElementA* const element);
    void visitorElementB(ConcreteElementB* const element);
};

class ConcreteVisitor2 : public Visitor {
public:
    ~ConcreteVisitor2() {}

    void visitorElementA(ConcreteElementA* const element);
    void visitorElementB(ConcreteElementB* const element);
};

class Element {
public:
    Element() {std::cout << "Constructor Element "<< std::endl;}
    virtual ~Element() {std::cout << "Destructor Element "<< std::endl;}

    virtual  void accept(Visitor& v) = 0;
};

class ConcreteElementA : public Element {
public:
    ConcreteElementA(const std::string& data)
    : private_data(data) {}
    ~ConcreteElementA() {}

    void accept(Visitor& v) {
        v.visitorElementA(this);
    }

    std::string getData() {
        return private_data;
    }
private:
    std::string private_data;
};

class ConcreteElementB : public Element {
public:
    ConcreteElementB(const std::string& data)
    : private_data(data) {}
    ~ConcreteElementB() {}

    void accept(Visitor& v) {
        v.visitorElementB(this);
    }

    std::string getData() {
        return private_data;
    }
private:
    std::string private_data;
};

void ConcreteVisitor1::visitorElementA(ConcreteElementA *const element) {
    std::cout << "Concrete Visitor 1 : Element A visited, " << element->getData() << std::endl;
}
void ConcreteVisitor1::visitorElementB(ConcreteElementB *const element) {
    std::cout << "Concrete Visitor 1 : Element B visited, " << element->getData() << std::endl;
}
void ConcreteVisitor2::visitorElementA(ConcreteElementA *const element) {
    std::cout << "Concrete Visitor 2 : Element A visited, " << element->getData() << std::endl;
}
void ConcreteVisitor2::visitorElementB(ConcreteElementB *const element) {
    std::cout << "Concrete Visitor 2 : Element B visited, " << element->getData() << std::endl;
    
}

int main() {
    ConcreteVisitor1 visitor1;
    ConcreteVisitor2 visitor2;
    ConcreteElementA elementA("String ElementA ConcreteElementA");
    elementA.accept(visitor1);
    elementA.accept(visitor2);
    ConcreteElementB elementB("String ElementB ConcreteElementB");
    elementB.accept(visitor1);
    elementB.accept(visitor2);
}