#include <stdio.h>

/*
 * C++ Design Patterns: COMMAND
 * http://www.plantuml.com/plantuml/uml/PP7DIiD058NtynGNN5IhCRWj8THM5ovQGTpBP79AH-Sdp4-mg0_aS_XYfkaaQhra4SxzxZadPEu3To5gnV89BUzNg-lr3KrorezGt7kwCwrzWQCtHjrar3ZPye0dORNcfkxLS_88ouDmUfOal4B4W1_vOx1yW81ia-SUvI98Qmw8D05kmmKeNIRgP33yxRIqHZYC8VzAkfIKSluuR6KDWcx2ZZHq1USPOyFNJhDio6TZtIoR7YUoumRPUpaUCcC3Y7jQN_K5YgeiX5NMpPpTSRLG4MLYYxnVb4LUbGFxk6imsmkqm9QtqZgk-jsj4RpnKO6Y0QKV0QgvyPr2jdf6kEZ9-kjJsDXqPFS89M42rP4sDZeZlKTqbmnTwtrHDk_UebRV
 *
 */
#include <iostream>

class Receiver {
public:
    void action() {
        std::cout << "Receiver: execute action" << std::endl;
    }
    Receiver() { std::cout << "Constructor Receiver" << std::endl; }
};

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
};

class ConcreteCommand : public Command {
public:
    ConcreteCommand(Receiver *r) : private_receiver(r) {std::cout << "Constructor ConcretCommand" << std::endl; };
    ~ConcreteCommand() {
        if (!private_receiver) {
            delete private_receiver;
        }
    }
    void execute() {
        std::cout << "ConcreteCommand execute" << std::endl;
        private_receiver->action();
    }
private:
    Receiver* private_receiver;
};

class Invoker {
public:
    void setCommand(Command* c) {
        private_command = c;
    }
    
    void executeCommand() {
        std::cout << "Invoker: executeCommand" << std::endl;
        if (private_command) private_command->execute();
    }

private:
    Command* private_command;
};

int main() {
    Receiver* receiver = new Receiver();
    Command *command = new ConcreteCommand(receiver);
    
    Invoker invoker;
    invoker.setCommand(command);
    invoker.executeCommand();
}