#include <stdio.h>

/*
 * C++ Design Patterns: MEMENTO
 * http://www.plantuml.com/plantuml/uml/NO_Dxjem4CJlVegzqN_RDEeLHH6YuWXKXPxH9fc2Mtz4wmqIglf0VOw-M9Ce0OGljdupE-DT9MNHpZkJBsYxsMvsnpqjSjEVsd5Az8K5ohyWzDjGVpBwAlRAYjDUxDa6rYWqAGU-eZbjuH4qJknxQE8B-eOdz6Skci2z9Yah7lAZxSKnl3zGWau1xsmWJyivxsqor09Mp9wt8VXY6n1ygpVoy1Ka6VDOztqsHvZffYBBdlvXJ8WAuaIxpsD9KPL57LsKfSGRkxNhK4wZHJuAPP5NvUmztbei1q1hNFXgex0RjGE7H3uszeU5a5iWrDocph7Q6AX1ZsBr4_fnT2C8pZQf3FpVNsKTB3LSPxFQKXixeHRYeIeO9noJ82btSazC_JNEVZ883GsBcLN_whpx3m00
 *
 */

#include <iostream>


class Memento {
private:
    friend class Originator;

    Memento(int s) : private_state(s) {}

    void setState(int s) {
        private_state = s;
    }

    int getState() {
        return private_state;
    }
private:
    int private_state;
};

class Originator {
public:
    void setState(int s) {
        private_state = s;
    }

    int getState() {
        return private_state;
    }

    void setMemento(Memento* const m) {
        private_state = m->getState();
    }

    Memento* createMemento() {
        return new Memento(private_state);
    }

    int getMementoState(Memento* const m) {
        return m->getState();
    }

private:
    int private_state;
};

class CareTaker {
public:
    CareTaker(Originator* const o) : private_originator(o) {}

    ~CareTaker() {}

    void save() {
        std::cout << "Save state: " << private_originator->getState() << std::endl;
        Undo_Memento=Saved_Memento;
        Redo_Memento=Saved_Memento;
        Saved_Memento=(private_originator->createMemento());
    }

    void printSavedStates() {
        std::cout << "Saved states: " ;
        if (Saved_Memento==0) {
            std::cout << "it's empty" << std::endl;
        } else {
            std::cout << "saved state " << private_originator->getMementoState(Saved_Memento) ;
            std::cout << " undo state " << private_originator->getMementoState(Undo_Memento) ;
            std::cout << " redo state " << private_originator->getMementoState(Redo_Memento) << std::endl;
        }
    }

    void undo() {
        if (Undo_Memento==0) {
            std::cout << "Unable to undo state." << std::endl;
            return;
        }
        if (private_originator->getMementoState(Saved_Memento)==private_originator->getMementoState(Undo_Memento)) {
            std::cout << "Unable to undo state." << std::endl;
            return;
        }
        Memento* m = Undo_Memento;
        Redo_Memento = Saved_Memento;
        Saved_Memento = Undo_Memento;
        private_originator->setMemento(m);
        std::cout << "Perform Undo : " << private_originator->getState() << std::endl;
    }

    void redo() {
        if (Redo_Memento==0) {
            std::cout << "Unable to redo state." << std::endl;
            return;
        }
        Memento* m = Redo_Memento;
        Saved_Memento=Redo_Memento;
        private_originator->setMemento(m);
        std::cout << "Perform Redo : " << private_originator->getState() << std::endl;
    }

    private:
    Originator* private_originator;
    Memento* Saved_Memento; // for saved
    Memento* Undo_Memento; // for undo
    Memento* Redo_Memento; // for redo
};

int main() {
    Originator *originator = new Originator();
    CareTaker *careTaker = new CareTaker( originator);

    originator->setState(0);
    careTaker->save();
    originator->setState(1);
    careTaker->save();
    originator->setState(2);
    careTaker->save();
    careTaker->printSavedStates();
    careTaker->undo();
    careTaker->printSavedStates();
    careTaker->redo();
    careTaker->printSavedStates();
    careTaker->undo();
    careTaker->undo();
    careTaker->undo();
    careTaker->printSavedStates();
}