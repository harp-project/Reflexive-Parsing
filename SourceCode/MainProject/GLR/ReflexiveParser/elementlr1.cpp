#include "elementLR1.h"

ElementLR1::ElementLR1()
{
    _dot = 0;
}

ElementLR1::ElementLR1(Rule r, QVector<Token> l)
{
    _rule = r;
    _dot = 0;
    _lookahedToken = l;
}

int ElementLR1::GetDot()
{
    return _dot;
}

void ElementLR1::SetDot(int d)
{
    _dot = d;
}

Token ElementLR1::Left()
{
    return  _rule.Left();
}

QVector<Token> ElementLR1::Right()
{
    return _rule.Right();
}

bool ElementLR1::operator==(const ElementLR1 r) const
{
    return (this->_rule == r._rule && this->_dot == r._dot && this->_lookahedToken == r._lookahedToken);
}

QVector<Token> ElementLR1::LookahedToken()
{
    return _lookahedToken;
}

Rule ElementLR1::GetRule()
{
    return _rule;
}
