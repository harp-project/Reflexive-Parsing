#include "rule.h"

Rule::Rule()
{

}

Rule::Rule(Token _l, QVector<Token> _r)
{
    _left = _l;
    _right = _r;
}

Token Rule::Left()
{
    return _left;
}

QVector<Token> Rule::Right()
{
    return _right;
}

bool Rule::operator==(const Rule r) const
{
    return (this->_left == r._left && this->_right == r._right);
}
