#include <stdio.h>

/*
 * C++ Design Patterns: CHAIN OF RESPONSABILITY
 * http://www.plantuml.com/plantuml/uml/ZP11Qnin48Nl-XKFUaXBwvhaQ9ObjMc9eJZ1oQMdejM-T5Mqqdea6KpR7vGU-YVynwgku-HGC9cBXddpFkRfCYOjAVTEJS-mkFgmNE7w4zOVRs-kLxVB-VBpykuBpgQgb74wHYoSfKzAMPyezzeGLzgtZe8V2gKc6CHkTUBNc8rXZ476-IjquzwQcyoONhzHlvwGmHjXuYFe_97qziMEYrEEphO4-o7jqBDlA56fGmXCwkFnwXYY-ZcP_7VGIVNYINt6OORdzCg7HEY8rVbuPTNKbGako4p2JhkvowmNdROUuHvhnY7uQ1lhRDfLqt6nhgPDVVJUxGRE_WqmPwUtDeXsetP3wPdG4gOGacGhHFQ4wVJ-JtcB8WUy7l7x1un6lQL1ktym8GzEV-CxE2A9jeaz_KXq6i9DtlzEnC2SK3hXmLwS4h8hj44B1fUZPPQ8q7ndYjXaYwwis3Ioyl6FtYlw5ZuagilIvTxz1G00
 *
 */

#include <iostream>
#include <string>




class Handler {
public:
    virtual ~Handler() {};
  
    void setSuccessor(Handler *s) {
        private_successor = s;
    }

    Handler* getSuccessor() {
        return private_successor;
    }

    virtual void handleRequest() = 0;
private:
    Handler *private_successor;
};

class ConcreteHandler1 : public Handler {
public:
    ~ConcreteHandler1() {}
    ConcreteHandler1(){std::cout << "Constructor ConcreteHandler1" << std::endl;}
    void handleRequest() {
        if (!this->getSuccessor()) {
            std::cout << "Request handled by Concrete Handler 1 // no successor" << std::endl;
        }
        else {
            std::cout << "Request handled by the Successor (=chain of responsability) : ";
            this->getSuccessor()->handleRequest();
        }
    }
};

class ConcreteHandler2 : public Handler {
public:
    ~ConcreteHandler2() {}
    ConcreteHandler2(){std::cout << "Constructor ConcreteHandler2" << std::endl;}
    void handleRequest() {
        if (!this->getSuccessor()) {
            std::cout << "Request handled by Concrete Handler 2 // no successor" << std::endl;
        }
        else {
            std::cout << "Request handled by the Successor (=chain of responsability) : " << std::endl;
            this->getSuccessor()->handleRequest();
        }
    }
};

class Client {
public:
    Handler *h;
};

int main() {
    Client* client = new Client();
    client->h = new ConcreteHandler1();
    Handler* h2 = new ConcreteHandler2();
    client->h->handleRequest();
    client->h->setSuccessor(h2);
    client->h->handleRequest();
    //h2->setSuccessor(client->h);
    client->h->handleRequest();
}