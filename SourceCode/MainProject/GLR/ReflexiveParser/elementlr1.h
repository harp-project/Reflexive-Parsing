#ifndef ELEMENTLR1_H
#define ELEMENTLR1_H

#include "rule.h"

class ElementLR1
{
public:
    ElementLR1();
    ElementLR1(Rule,QVector<Token>);
    int GetDot();
    void SetDot(int);
    Token Left();
    QVector<Token> Right();
    QVector<Token> LookahedToken();
    Rule GetRule();
    bool operator==(const ElementLR1) const;

private:
    int _dot;
    Rule _rule;
    QVector<Token> _lookahedToken;
};

#endif // ELEMENTLR1_H
