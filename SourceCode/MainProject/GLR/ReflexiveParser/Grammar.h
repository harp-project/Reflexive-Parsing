#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <QVector>
#include "rule.h"
class Grammar
{
public:
    Grammar();
    void AddRule(Rule R);
    void SetMetaToken(Token S);
    Token GetStarter();
    Rule GetRule(int i);
    int GetRuleIndex(Rule r);
    int Size();
    QVector<Token> GetTerminals();
    QVector<Token> GetNonTerminals();
    void SetTerminals( QVector<Token>);
    void SetNonTerminals( QVector<Token>);

    bool IsTerminal(Token);
    bool IsNonTerminal(Token);

    void InsertUniqueStartRule(); // assume that the first given rule has the original starter symbol
    void UniqueStart_End();
    Token StartToken = Token("Q");
    Token EndOfText = Token("#");
    Token MetaToken = Token("@");

    QString RandomString();

private:
    QVector<Rule> _rules;
    QVector<Token> _terminals;
    QVector<Token> _nonterminals;
};

#endif // GRAMMAR_H
