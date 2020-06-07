#ifndef PARSERTABLE_H
#define PARSERTABLE_H

#include <QVector>
#include "elementlr1.h"


enum Indicator{Ok, Step, Reduce, Error};

struct Action{
    Action(){};
    Indicator _indicator;
    ElementLR1 _rule;
    int _stepState;

    Action(Indicator i, ElementLR1 r){
        _indicator = i;
        _rule = r;
    }
    Action(Indicator i){
        _indicator = i;
    }
    Action(Indicator i,int s){
        _indicator = i;
        _stepState = s;
    }
};

class ParserTable
{
public:
    ParserTable();
    void AddToken(Token);
    Token GetToken(int i);
    QVector<Token> GetAllToken();
    void SetState(int aktState, int newState, Token t, Action a);
    QVector<Action> GetState(int i,Token t);
    void SetStateSize();
    int GetNoStates();
private:
    QVector<Token> _tokens;
    QVector<QVector<QVector<Action>>> _states;
};

#endif // PARSERTABLE_H
