#include "parsertable.h"

ParserTable::ParserTable()
{

}

void ParserTable::AddToken(Token t)
{
    _tokens.push_back(t);
}

Token ParserTable::GetToken(int i)
{
    return _tokens[i];
}

QVector<Token> ParserTable::GetAllToken()
{
    return _tokens;
}

void ParserTable::SetState(int aktState, int newState, Token t, Action a)
{
    if(_states.isEmpty())
    {
        _states.resize(1);
        if(_states[0].size() != _tokens.size())
        {
            _states[0].resize(_tokens.size());
        }
    }

    if(newState >= _states.size()-1)
    {
        while(_states.size()-1 < newState)
        {
            QVector<QVector<Action>> a;
            a.resize(_tokens.size());
            _states.push_back(a);
        }

    }
    if(aktState >= _states.size()-1)
    {
        while(_states.size()-1 < aktState)
        {
            QVector<QVector<Action>> a;
            a.resize(_tokens.size());
            _states.push_back(a);
        }

    }
    int aktToken = _tokens.indexOf(t);
    _states[aktState][aktToken].push_back(a);
}

QVector<Action> ParserTable::GetState(int i, Token t)
{
    int j = _tokens.indexOf(t);
    if(j == -1)
    {
        return {Error};
    }
    return _states[i][j];
}

void ParserTable::SetStateSize()
{
    _states.resize(1);
    _states[0].resize(_tokens.size());

}

int ParserTable::GetNoStates()
{
    return _states.size();
}

