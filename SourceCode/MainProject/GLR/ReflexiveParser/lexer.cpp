#include "lexer.h"

Lexer::Lexer()
{

}

Lexer::~Lexer()
{
    if(_metaV != NULL)
    {
        delete _metaV;
    }
}

void Lexer::AddRegExp(QString s,QString n)
{
    QRegularExpression re(QRegularExpression::anchoredPattern(s));
    _regExps.push_back({re,n});
}

void Lexer::SetInput(QString s)
{
    _input = s;
}

void Lexer::LexInput()
{
    _resTokens.clear();
    QString act = "";

    bool MetaNameMode = false;

    QVector<QVector<MatchElement>> MatchHistory;
    for(int i = 0 ; i < _input.size() ; i++)
    {
        act.append(_input[i]);
        QVector<MatchElement> RegExpMaching;

        if(MetaNameMode)
        {
            QRegularExpressionMatch match = _metaVNameRegExp.match(act, 0, QRegularExpression::PartialPreferCompleteMatch);
            RegExpMaching.push_back({match.hasMatch(),match.hasPartialMatch()});
        }
        else
        {
            for(int j = 0 ; j < _regExps.size() ; j++)
            {
                QRegularExpressionMatch match = _regExps[j]._regExp.match(act, 0, QRegularExpression::PartialPreferCompleteMatch);

                RegExpMaching.push_back({match.hasMatch(),match.hasPartialMatch()});
            }
        }

        if(i == _input.size()-1)
        {
            if(RegExpMaching.contains({true,true}))
            {
                if(MetaNameMode)
                {
                    _resTokens.push_back(Token(act));
                    MetaNameMode = false;
                }else
                {
                    _resTokens.push_back(Token(_regExps[RegExpMaching.indexOf({true,true})]._name));
                }

                break;
            }else if(RegExpMaching.contains({true,false}))
            {
                if(MetaNameMode)
                {
                    _resTokens.push_back(Token(act));
                    MetaNameMode = false;
                }else
                {
                    _resTokens.push_back(Token(_regExps[RegExpMaching.indexOf({true,false})]._name));
                }

                break;
            }
        }
        if(RegExpMaching.contains({false,true}) || RegExpMaching.contains({true,true}) || RegExpMaching.contains({true,false}))
        {
            MatchHistory.push_back(RegExpMaching);
        }else if(MatchHistory.size() == 0 )
        {
            act = "";
        }
        else
        {
            bool b = true;
            while(b)
            {
                act.chop(1);
                if(MatchHistory.last().contains({true,true}) || MatchHistory.last().contains({true,false}))
                {
                    if(MatchHistory.last().contains({true,true}))
                    {
                        if(MetaNameMode)
                        {
                            _resTokens.push_back(Token(act));
                            MetaNameMode = false;
                        }else
                        {
                            _resTokens.push_back(Token(_regExps[MatchHistory.last().indexOf({true,true})]._name));
                        }

                    }else if(MatchHistory.last().contains({true,false}))
                    {
                        if(MetaNameMode)
                        {
                            _resTokens.push_back(Token(act));
                            MetaNameMode = false;
                        }else
                        {
                            _resTokens.push_back(Token(_regExps[MatchHistory.last().indexOf({true,false})]._name));
                        }

                    }
                    act = "";
                    MatchHistory.clear();
                    b = false;
                    i--;
                }else
                {
                    i--;
                    MatchHistory.pop_back();
                    if(MatchHistory.size() == 0)
                    {
                        //Err
                        b = false;
                        i--;
                    }
                }
            }
            if(!_resTokens.isEmpty() && _metaV != NULL)
            {
                if(_resTokens.last() == *_metaV)
                {
                    MetaNameMode = true;
                }
            }

        }
    }
}

QVector<Token> Lexer::GetResTokens()
{
    return _resTokens;
}

void Lexer::SetMetaVariable(Token t)
{
    if(_metaV == NULL)
    {
        delete _metaV;
    }
    _metaV = new Token(t);
}
