#include <stdio.h>

/*
 * C++ Design Patterns: STRATEGY
 * http://www.plantuml.com/plantuml/uml/bP3FIiD04CRlynHpgw8rU2qXj57nvi7cud6ocIOB-oTiPgL1VQ0-Hr_CRJ15K12_q_9zluKVinw4WaHh85lWjdhUL0-FBxZ884KP6WQyyqvuBm3Q2OSTASQj119kHtm3JBb2thEAmXUNyF7jcmeiFBER_y3bxt2d6qQslOnesTOS1e0lFVJBvTaBpeBvUwf_gFonbm3E2oCD-7GxUUHraIjlV5W5Fv8fJUHYflDiMeeyguiPhiQULwS2I-xeLVj0PjhkZuUTTbemEYJJ-g2bitoDXZ6mQoPckhFgoBLCTHfOKjKS3tq2o0as4PNHxEG6KeCdLLYdLxJc4m00
 *
 */


#include <iostream>

class Strategy {
public:
    virtual ~Strategy() {}
    virtual void execute() = 0;
};

class ConcreteStrategyA : public Strategy {
    ~ConcreteStrategyA() {}

    void execute() {
        std::cout << "Concrete Strategy A" << std::endl;
    }
};

class ConcreteStrategyB : public Strategy {
    ~ConcreteStrategyB() {}

    void execute() {
        std::cout << "Concrete Strategy B" << std::endl;
    }
};

class ConcreteStrategyC : public Strategy {
    ~ConcreteStrategyC() {}

    void execute() {
        std::cout << "Concrete Strategy C" << std::endl;
    }
};

class Context {
public:
    Context(Strategy* s) : strategy(s) {
        std::cout << "Assign Concrete Strategy : " << typeid(*s).name() << std::endl;
    }
    ~Context() {
        delete strategy;
    }

    void execute() {
        strategy->execute();
    }
private:
    Strategy* strategy;
};

int main() {
    Context context(new ConcreteStrategyB());
    context.execute();
}