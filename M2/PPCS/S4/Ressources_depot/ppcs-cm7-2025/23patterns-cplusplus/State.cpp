#include <stdio.h>

/*
 * C++ Design Patterns: STATE
 * http://www.plantuml.com/plantuml/uml/ZP3FIiD04CRlynHpgo8rjCSIGcqfUF9W-mBRpMWZ-oVEpXQB-YwUVGrVpCr8fOA2GqZ2z_s-cPsT9p4isJkeHhZUN6rMEAgWb7Kc9Lp68FGaMA_525rUcz0wEZjly1cmr0NUqcEc98DTT7W5w4g2xumbLF6RrAmo9yqjav1oa_-2qr_1NTSIak_bW9xybZW170yVnsFKAEWRwvSY_1p-fpC52B4u9k7DHEVMswQsqKMUSJmOjt2P6aNhIkMchhRDaTmSUfeD0YveP_PTPEFKMmLh-fGTONbiz7ra8Kz1yECDXSsUE64EkDCTMJDBShb3ss5FkN3lmeI-IqFY8MOUligTn6t9tt_rRGdrDWaej3Wi1VFobxtx1000
 *
 */

#include <iostream>

class State {
public:
    virtual ~State() {}
    
    virtual void Handle() = 0;
};

class ConcreteStateA : public State {
    ~ConcreteStateA() {}
    
    void Handle() {
        std::cout << "State A handled." << std::endl;
    }
};

class ConcreteStateB : public State {
    ~ConcreteStateB() {}

    void Handle() {
        std::cout << "State B handled." << std::endl;
    }
};

class Context {
public:
    Context() : state() {}
    ~Context() {
        if (state) {
            delete state;
        }
    }
    
    void setState(State* const s) {
        if (state) {
            delete state;
        }
        state = s;
    }
    
    void Request() {
        std::cout << "call handler()" << std::endl;
        state->Handle();
    }
    
private:
    State* state;
};

int main() {
    Context* context = new Context();
    
    context->setState(new ConcreteStateA());
    context->Request();
    
    context->setState(new ConcreteStateB());
    context->Request();
}