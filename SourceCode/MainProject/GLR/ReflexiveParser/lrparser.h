#ifndef LRELEMZO_H
#define LRELEMZO_H

#include "Grammar.h"
#include "parsertable.h"
#include "elementlr1.h"
#include "node.h"
#include "lexer.h"

struct BoolToken{
    bool _bool;
    Token _token;
};

struct RuleNo{
    int _ruleNo;
    bool _isMeta;
    QVector<int> _metaind;
    QVector<Token> _metaVar;
    bool operator==(const RuleNo r) const{
        return _ruleNo == r._ruleNo && _isMeta == r._isMeta && _metaind == r._metaind && _metaVar == r._metaVar;
    }
};

struct StackElement{
    Token _token;
    int _state;
    StackElement(){};
    StackElement(Token t , int s)
    {
        _token = t;
        _state = s;
    }
    bool operator==(const StackElement s) const{
        return  _token == s._token && _state == s._state;
    }
};

struct ForkElement{
    Token _nextToken;
    int _textIndex;
    QVector<StackElement> _stack;
    int _state;
    QVector<RuleNo> _rulesUsed;
    int _ruleToContinue; // if -1 there were no decision jet
    QVector<BoolToken> _ismetanonterminal;
    StackElement _actStarter;
    Token _reducedToken;
    bool _reduced;
    ForkElement(){};
    ForkElement(Token t ,int i, QVector<StackElement> s ,int e ,QVector<RuleNo> r , int c,QVector<BoolToken> m, StackElement a, bool reduced, Token ret)
    {
        _nextToken = t;
        _textIndex = i;
        _stack = s;
        _state = e;
        _rulesUsed = r;
        _ruleToContinue = c;
        _ismetanonterminal = m;
        _actStarter = a;
        _reduced = reduced;
        _reducedToken = ret;
    }
};

class LRParser
{
public:
    LRParser(Grammar g, QVector<Token> t);
    void Generate();
    void Parse();
    bool GetResult();
    QVector<ElementLR1> Read(QVector<ElementLR1> , Token);
    QVector<ElementLR1> Closure(ElementLR1);
    ParserTable GetTable();
    QVector<Token> PossibleTokens(int state);
    QVector<Token> First(QVector<Token>);
    QVector<RuleNo> GetRulesUsed();
    void SetProgText(QVector<Token>);

    void SetProgramAST(Node*);
    QVector<Node *> GetValidASTs();

    Node* BuildCST();
    Node* GetMostRightenNodewNonTerm(Node*,Token);
    QVector<Node*> GetPatternForest();
    void printCST(Node*);

    void CalValidMatches();
    bool ProcessCSTs(Node*,Node*);

    QVector<Token> GetText();
    QVector<Token> GetProgText();

    void ResetProgCST(Node*);

private:

    Grammar _grammar;
    QVector<Token> _text;
    QVector<StackElement> _stack;
    bool _result;
    QVector<bool> _allResult;
    ParserTable _table;
    QVector<RuleNo> _rulesUsed;
    QVector<QVector<int>> _parsedRules;

    QVector<ForkElement> _brancesToProcess;
    QVector<Node*> _patternForest;
    QVector<Node*> _programAST;
    QVector<Node*> _validASTs;

    QVector<Token> _progText;
};

#endif // LRELEMZO_H
