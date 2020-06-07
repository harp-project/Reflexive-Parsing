#ifndef RULE_H
#define RULE_H

#include <QString>
#include "token.h"
#include <QVector>

class Rule
{
public:
    Rule();
    Rule(Token _l , QVector<Token> _r);
    Token Left();
    QVector<Token> Right();
    bool operator==(const Rule) const;

private:
    Token _left;
    QVector<Token> _right;

};

#endif // RULE_H
