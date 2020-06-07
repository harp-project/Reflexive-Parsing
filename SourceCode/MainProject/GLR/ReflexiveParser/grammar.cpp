#include "Grammar.h"

Grammar::Grammar()
{

}

void Grammar::AddRule(Rule R)
{
    _rules.push_back(R);
}

void Grammar::SetMetaToken(Token S)
{
    MetaToken = S;
}

Token Grammar::GetStarter()
{
    return StartToken;
}

Rule Grammar::GetRule(int i)
{
    return  _rules[i];
}

int Grammar::GetRuleIndex(Rule r)
{
    return _rules.indexOf(r);
}

int Grammar::Size()
{
    return _rules.size();
}

QVector<Token> Grammar::GetTerminals()
{
    return _terminals;
}

QVector<Token> Grammar::GetNonTerminals()
{
    return _nonterminals;
}

void Grammar::SetTerminals(QVector<Token>t)
{
    _terminals = t;
}

void Grammar::SetNonTerminals(QVector<Token>n)
{
    _nonterminals = n;
}

bool Grammar::IsTerminal(Token t)
{
    return _terminals.contains(t);
}

bool Grammar::IsNonTerminal(Token t)
{
    return _nonterminals.contains(t);
}

void Grammar::InsertUniqueStartRule() // assume that the first given rule has the original starter symbol
{
    Rule a(StartToken,{_rules[0].Left()});
    _rules.push_front(a);
}

void Grammar::UniqueStart_End()
{
    StartToken = Token("Q");
    QString start = "Q";
    while(IsTerminal(StartToken) || IsNonTerminal(StartToken))
    {
        start.append(RandomString());
        StartToken = Token(start);
    }
    _nonterminals.push_back(StartToken);

    EndOfText = Token("#");
    QString end = "#";
    while(IsTerminal(end) || IsNonTerminal(end))
    {
        end.append(RandomString());
        EndOfText = Token(end);
    }
}

QString Grammar::RandomString()
{

    QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#@");
    int rsl = 10;

    QString rs;
    for(int i=0; i<rsl; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        rs.append(nextChar);
    }
    int index = qrand() % rs.length();
    rs = rs[index];
    return rs;
}
