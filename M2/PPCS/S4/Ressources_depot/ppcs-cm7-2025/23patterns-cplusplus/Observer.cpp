/*
 * C++ Design Patterns: OBSERVER
 * 
 * http://www.plantuml.com/plantuml/uml/XL51Rjim4Bpp5OFqaBY1xVOg24RWDeTS6Y0ESgUaTSo08bLoQTH8yvTUzGvzh9GYkguCj3nnPuOxiyiRpz9ngBLONk9-lRbzUBfzmELInACCazlAah09nGkLZ5U1UEROtnUUt9uSCZn5mhg1k8PabkNkIXdOI2NLR6Gh-XThBAljuUgz_81duWrBfYFW_m1lGfHQUeylrfIEcAO1_NizwAFLdU7HPDBr-gGhnDlfpCSHNqV_q5IzpYDB-vWXwnCm_U2pqCarmNTLmixJJwpci2DmbZ-5cFr_dDvcfoe2rGqVK5DTaFD2f5NDLnUV5ekF5pZvo-4B5FcZAFyvdq-NBDA3lzc4YeaS-Ra6MHen1egc1EdnxVCmGrwiyj9gwp9d3rAlTQ1LUfSl1sQLBujL4ZyU6ifw06lQoRsoJkg1-zgrMsKK8nY28orPMHCBTB_GwE0L1US7PME3W-jQgLNqWPQeuwNNlVICjgEkkeolovqqprIJuLXtBKjUuD463qqUDexCexXh6pALDEpXhU5nkLth8GFREiRv7eO-2n5rFKtY9jv2hNy3
 *
 * 2021 / JMB
 *
 */


#include <iostream>
#include <vector>

class Subject;

class Observer {
public:
    Observer(const int id) : p_id(id) {}
    virtual ~Observer() {}

    virtual int getState() = 0;
    virtual void update(Subject* subject) = 0;
    virtual int getId() = 0;
protected:
    int p_id;
};

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(const int state, const int id)
    : observerState(state), Observer(id) {}
    ~ConcreteObserver() {}

    int getState() {
        return observerState;
    }

    int getId() {
        return p_id; //protected
    }

    void update(Subject* subject);
private:
    int observerState;
};

class Subject {
public:
    virtual ~Subject() {}

    void attach(Observer* observer) {
        vObserver.emplace_back(observer);
    }

    void detach(const int id) {
        for (auto it = vObserver.begin(); it != vObserver.end(); ++it) {
            if ((*it)->getId() == id) {
                vObserver.erase(it);
            }
        }
    }

    void notify() {
        for (auto observer : vObserver) {
            observer->update(this);
        }
    }

    virtual int getState() = 0;
    virtual void setState(const int state) = 0;
private:
    std::vector<Observer*> vObserver;
};

class ConcreteSubject : public Subject {
public:
    ~ConcreteSubject() {}

    int getState() {
        return subjectState;
    }

    void setState(const int state) {
        subjectState = state;
    }
private:
    int subjectState;
};

void ConcreteObserver::update(Subject *subject) {
    observerState = subject->getState();
    std::cout << "Observer(id=" << p_id << ") update state to: " << observerState << std::endl;
}

int main() {
    ConcreteObserver observer1(1000, 1);
    ConcreteObserver observer2(2000, 2);

    std::cout << "Observer1 state: " << observer1.getState() << std::endl;
    std::cout << "Observer2 state: " << observer2.getState() << std::endl;

    Subject* subject = new ConcreteSubject();
    subject->attach(&observer1);
    subject->attach(&observer2);

    subject->setState(10);
    subject->notify();

    std::cout << "Observer1 state: " << observer1.getState() << std::endl;
    std::cout << "Observer2 state: " << observer2.getState() << std::endl;

    subject->detach(1);
    subject->setState(100);
    subject->notify();

    std::cout << "Observer1 state: " << observer1.getState() << std::endl;
    std::cout << "Observer2 state: " << observer2.getState() << std::endl;
}
