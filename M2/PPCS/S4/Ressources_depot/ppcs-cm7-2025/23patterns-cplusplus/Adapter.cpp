#include <stdio.h>

/*
 * C++ Design Patterns: ADAPTER
 * http://www.plantuml.com/plantuml/uml/XP9DRi8m48NtFiL8NG2gGaIMA8g0jhkggYXxD76cgYl7Zkm94lsvIxUSWulL3I652BMpchpvdbzipSmpEgvBBU81p6_dZwkx9GnY4KeP9lUCac1UO1LwU1SGwWfiHGvPMJCSYKyXf4RluKOhCjmorr3OjMoKzMNQ6kc8wVpegAyFbMdJQJBw5qb6RVYboEwSuozsmaAzeNDqWKtwR7B6YXTL451PyHPAAdDoNeZZZTAeVP9VvIEAkj1pjNSdqVk6AEkCVymI8Onb0lJmC14GAispL5fjtTJPBUg5hYbhVMdS3B8qphCZkzfMDFqHu8bTBRbsg9lPShz3hJn1RGYaDHjoNbaJsh92Lhacm0r9Q61D7f2P38UcgE6m1sEunnDhGnO1wDRC0ta6TqZQxmZsNw07odX68nNogSdchyH-BCWKO2oJc8MkBlKt
 *
 */


#include <iostream>
#include <string>
#include <functional>

/* Legacy code -------------------------------------------------------------- */

struct Adapter {
    Adapter() { std::cout << "Constructor Adapter" << std::endl;}
    virtual void operation() = 0;
};

struct Adaptee1 : Adapter {
    void Adaptee1Bizarre() { std::cout << "perform Adaptee1Bizarre" << std::endl;}
    void operation() { Adaptee1Bizarre(); }
};

//exported interface to the client
class Client {
public:
    void do_client_operation(Adapter &do_client){
    std::cout << "do_client operation()" << std::endl;
    do_client.operation();                // Interface from Adapter
};
};

// Evolution with ConcreteAdapter & Adaptee2

struct Adaptee2 {                     // Introduced later on - don't call Adapter Constructor
    void Adaptee2Bizarre() { std::cout << "perform Adaptee2Bizarre" << std::endl; }
    //void operation() { Adaptee2Bizarre(); }
};

struct ConcreteAdapter : Adapter {              // Expanding Adapter with lambda function
    std::function<void()>    m_request;
    //lambda function, copy cm in m_request and call specific adaptee operation
    ConcreteAdapter(Adaptee1* cm1) { m_request = [cm1] ( ) {  std::cout << "lambda cm1" << std::endl; cm1->Adaptee1Bizarre(); }; }
    ConcreteAdapter(Adaptee2* cm2) { m_request = [cm2] ( ) { std::cout << "lambda cm2" << std::endl; cm2->Adaptee2Bizarre(); }; }
    void operation() { m_request(); }
};

int main() {
    Client client;
    std::cout << "new Adaptee1" << std::endl;
    ConcreteAdapter adp1(new Adaptee1());
    client.do_client_operation(adp1);
    std::cout << "new Adaptee2" << std::endl;
    ConcreteAdapter adp2(new Adaptee2());
    client.do_client_operation(adp2);
}



