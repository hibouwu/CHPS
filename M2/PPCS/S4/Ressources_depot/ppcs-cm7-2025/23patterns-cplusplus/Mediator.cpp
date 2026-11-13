#include <stdio.h>

/*
 * C++ Design Patterns: MEDIATOR
 * http://www.plantuml.com/plantuml/uml/TL31RXCn4BtxAqRg8Q1e6t6DLgjIoe53G4AzLxFs8pNoseizNX417zJlw8_XEDqIPOLFC-_DUsyyDqauIXwSsgnez_7kq_lxBrzfjL77fnsdH3iOon8Y_L9KtXMnCM_UljJ69ecspu82_Pab7uBN4O8BAJKqGPV-GGVdmFkCT2BMisbj_kSwY_xPZT5EB7WONe8kSMjEo1KbUBDB-vfHWGWDEw5YoyqNMUjBX_N2uT4Q48PH3ZHWw16JKgyNQ9kp_RTa_RSG1vpnlvjcSJUrE6JJBLTKhzN9PJcWV10G9_hyhYxVzbshWmjn6yE1tQtBwEQ8TbEPhjtqtJnyVnYnFG9qYqUUR8ZiAdVt_AIZ5SgUGlyTGZ-o9NZDOyeEv938Ua5aBJRuL3LcLQRXKpcHG-cgy9fsa88IJ-o52b5dTSYZupt8FJ_j4MdaMB9GJAUW-UX9-3awgwtWMi4RElvKtPGg3-ul
 *
 */

#include <iostream>
#include <string>
#include <vector>

class Mediator;

class Colleague {
public:
    Colleague(Mediator* const m, unsigned int i)
    : private_mediator(m), private_id(i) {}

    virtual ~Colleague() = default;

    unsigned int getId() {
        return private_id;
    }

    virtual void sendMsg(std::string) = 0;
    virtual void receiveMsg(std::string) = 0;

protected:
    Mediator* private_mediator;
    unsigned int private_id;
};

class ConcreteColleague : public Colleague {
public:
    ConcreteColleague(Mediator* const m, unsigned int i)
    : Colleague(m, i) {}

    ~ConcreteColleague() = default;

    void sendMsg(std::string msg) override;

    void receiveMsg(std::string msg) override {
        std::cout << "Message: " << msg << " is received by Colleague(id=" << this->getId() << ")" << std::endl;
    }
};

class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void add(Colleague* const c) = 0;
    virtual void distribute(Colleague* const sender, const std::string& msg) = 0;
};

class ConcreteMediator : public Mediator {
public:
    ~ConcreteMediator() {
        for (unsigned int i = 0; i < colleagues_.size(); ++i) {
            delete colleagues_[i];
        }
        vector_colleagues.clear();
    }

    void add(Colleague* const c) {
        vector_colleagues.push_back(c);
    }

    void distribute(Colleague* const sender, const std::string& msg) {
        for (auto colleague : colleagues_) {
            if (colleague->getId() != sender->getId()) {
                colleague->receiveMsg(msg);
            }
        }
    }
private:
    std::vector<Colleague*> vector_colleagues;
};

void ConcreteColleague::sendMsg(std::string msg) {
    std::cout << "Message: " << msg << " is sent by Colleague(id=" << this->getId() << ")" << std::endl;
    private_mediator->distribute(this, msg);
}

int main() {
    Mediator *mediator = new ConcreteMediator();

    Colleague *colleague1 = new ConcreteColleague(mediator, 1);
    Colleague *colleague2 = new ConcreteColleague(mediator, 2);
    Colleague *colleague3 = new ConcreteColleague(mediator, 3);

    mediator->add(colleague1);
    mediator->add(colleague2);
    mediator->add(colleague3);

    colleague1->sendMsg("Hello");
    colleague2->sendMsg("World");
    colleague3->sendMsg("Mediator Pattern");
}
