#include <stdio.h>

/*
 * C++ Design Patterns: INTERPRETER
 * http://www.plantuml.com/plantuml/uml/XL7Dpjem4BpxALRg0IXre_OOHH6bui058SIzseHjiEgVQEqWKCi3zJdwOdK2-OBqWU93ifuPxux72n-GGsEqI2QmtknNk-rk5RymIKHSfKRluRjMPCFRpjb0vm2_1SGb8RXVPEzrpUg4WNuOh3ja3fx2LDcRw1F4gd1Ep-vazK3E8EquSHL2nGdy4qk2RuKFZ6LOdMicxvMpzxaVe1D5D4ndujgRsnCRPL6_qm_U1h_pnnwGzZSRkcqYCDxmmUENrzJNiP57TI0WKuSB6385iHUYppgJ_IFSVY1b_YGRyIIkx8-KGooZqlxEusefFxuG2-i20SRyRdbaHPwLJZjEsLrGBtL3-RgFWJXBEZBFaYBlzVjBJMaBm9AEU5AEKNVSDewZ036gmx-_9IicQ2n1nMWCjhlQDHoXJgpHLbWHj0Scolg0jbJ4u9qTte4Q_Yp87g1rBHQnQep-3m00
 *
 */
#include <iostream>
#include <unordered_map>

/*
 * Simple Interpreter example:
 * (digit+digit) => digit
 * (|+|digit|) = terminal
 * exemple : (9 = non-terminal
 * context : 9 -> true, )->true, (->false, (digit->false, digit)->true, digit+->false, +digit->false
 *
 */

class Context {
public:
    typedef char token;
    enum class std_token:token{digit='9',open_bracket='(', close_bracket=')', plus_symbol='+'};

    void set(std_token var, bool value) {
        maps.insert(std::make_pair(var, value));
    }

    char get(std_token var) {
        return maps[var];
    }
private:
    std::unordered_map<std_token, bool> maps;
};

class AbstractExpression {
public:
    virtual ~AbstractExpression() {}
    virtual bool interpret(Context* const context) = 0;
};

class TerminalExpression : public AbstractExpression {
public:
    TerminalExpression(Context::std_token token) : private_token(token) {}
    ~TerminalExpression() {}

    bool interpret(Context* const context) {
        return context->get(private_token);
    }
private:
    Context::std_token private_token;
};

class NonTerminalExpression : public AbstractExpression {
public:
    NonTerminalExpression(AbstractExpression* f, AbstractExpression* s)
    : first(f), second(s) {}

    ~NonTerminalExpression() {
        if (first) delete first;
        if (second) delete second;
    }

    bool interpret(Context* const context) {
        return first->interpret(context) && second->interpret(context);
    }
private:
    AbstractExpression* first;
    AbstractExpression* second;
};

int main() {
    Context context;
    //define way "basic" token property
    context.set(Context::std_token::close_bracket, true);
    context.set(Context::std_token::digit, true);
    context.set(Context::std_token::open_bracket, false);
    context.set(Context::std_token::plus_symbol, false);

    AbstractExpression* expressionCloseBracket = new TerminalExpression(Context::std_token::close_bracket); // )
    AbstractExpression* expressionOpenBracket = new TerminalExpression(Context::std_token::open_bracket); // (
    AbstractExpression* expressionDigit = new TerminalExpression(Context::std_token::digit); // 9
    AbstractExpression* expressionPlus = new TerminalExpression(Context::std_token::plus_symbol); // +
    AbstractExpression* expressionOpenBracketDigit = new NonTerminalExpression(expressionOpenBracket, expressionDigit); // (9
    AbstractExpression* expressionDigitCloseBracket = new NonTerminalExpression(expressionDigit, expressionCloseBracket); // 9)
    AbstractExpression* expressionDigitPlus = new NonTerminalExpression(expressionDigit, expressionPlus); // 9+
    AbstractExpression* expressionPlusDigit = new NonTerminalExpression(expressionPlus, expressionDigit); // +9

    std::cout << "( -> " << expressionOpenBracket->interpret(&context) << std::endl;
    std::cout << "9 -> " << expressionDigit->interpret(&context) << std::endl;
    std::cout << "+ -> " << expressionPlus->interpret(&context) << std::endl;

    std::cout << "(9 -> " << expressionOpenBracketDigit->interpret(&context) << std::endl;
    std::cout << "9+ -> " << expressionDigitPlus->interpret(&context) << std::endl;
    std::cout << "+9 -> " << expressionPlusDigit->interpret(&context) << std::endl;
    std::cout << "9) -> " << expressionDigitCloseBracket->interpret(&context) << std::endl;
}