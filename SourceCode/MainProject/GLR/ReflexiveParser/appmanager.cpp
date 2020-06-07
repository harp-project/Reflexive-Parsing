#include "appmanager.h"
#include <QtDebug>
AppManager::AppManager(QObject *parent) : QObject(parent)
{
    _resWindow = NULL;
    _mainWindow = new MainWindow(this);
    _mainWindow->show();
    connect(this,SIGNAL(Error(QString)),_mainWindow,SLOT(Error(QString)));
}

AppManager::~AppManager()
{
    if(_resWindow != NULL)
    {
        delete _resWindow;
    }

    delete _mainWindow;
}

void AppManager::Start()
{
    Lexer L;
    L.SetMetaVariable(Token(_metaV));
    L.AddRegExp(_metaV, _metaV);
    QStringList s = _inpRegExp.split("\n", QString::SkipEmptyParts);

    for(int i = 0 ; i < s.size() ; i++)
    {
        QStringList ss = s[i].split(" ", QString::SkipEmptyParts);
        if(ss.size() != 2)
        {
            emit Error("Reg");
            return;
        }
        L.AddRegExp(ss[0],ss[1]);
    }
    L.SetInput(_inpText);
    L.LexInput();
    _inpTextToken = L.GetResTokens();
    if(_inpTextToken.isEmpty())
    {
        emit Error("Lex");
        return;
    }

    L.SetInput(_inpPatt);
    L.LexInput();
    _inpPattToken = L.GetResTokens();
    if(_inpPattToken.isEmpty())
    {
        emit Error("Lex");
        return;
    }

    _terminalsToken.clear();
    QStringList t = _terminals.split("\n", QString::SkipEmptyParts);
    for(int i = 0; i < t.size() ; i++)
    {
        QStringList tt = t[i].split(" ", QString::SkipEmptyParts);
        for(int j = 0 ; j < tt.size() ; j++)
        {
            _terminalsToken.push_back(Token(tt[j]));
        }
    }

    _nonTerminalsToken.clear();
    t.clear();
    t = _nonTerminals.split("\n", QString::SkipEmptyParts);
    for(int i = 0; i < t.size() ; i++)
    {
        QStringList tt = t[i].split(" ", QString::SkipEmptyParts);
        for(int j = 0 ; j < tt.size() ; j++)
        {
            _nonTerminalsToken.push_back(Token(tt[j]));
        }

    }

    s.clear();
    Grammar G;
    s = _inpGramm.split("\n", QString::SkipEmptyParts);
    for(int i = 0 ; i < s.size() ; i++)
    {
        QStringList ss = s[i].split("->");
        if(ss.size() != 2)
        {
            emit Error("Gram");
            return;
        }
        QVector<Token> Right;

        if(ss[1] == "") //epsilon rule
        {
            Right = {};
        }else if(ss[1].contains(" "))
        {
            QStringList Rss = ss[1].split(" ", QString::SkipEmptyParts);

            for(int j = 0 ; j < Rss.size() ; j++)
            {
                Right.push_back(Token(Rss[j]));
            }
        }else
        {
            Right.push_back(Token(ss[1]));
        }
        G.AddRule(Rule(Token(ss[0]),Right));

    }
    G.SetTerminals(_terminalsToken);
    G.SetNonTerminals(_nonTerminalsToken);
    G.UniqueStart_End();
    G.InsertUniqueStartRule();
    G.SetMetaToken(Token(_metaV));

    for(int i = 0 ; i < _inpTextToken.size() ; i++)
    {
        if(!G.GetTerminals().contains(_inpTextToken[i]))
        {
            emit Error("Lex");
            return;
        }
    }

    for(int i = 0 ; i < _inpPattToken.size() ; i++)
    {
        if(_inpPattToken[i] == G.MetaToken)
        {
            i++;
            continue;
        }
        if(!G.GetTerminals().contains(_inpPattToken[i]))
        {
            emit Error("Lex");
            return;
        }
    }

    LRParser Parser(G,_inpPattToken);
    Parser.SetProgText(_inpTextToken);

    Parser.Generate();
    Parser.Parse();
    Parser.CalValidMatches();



    _resWindow = new ResWindow(this,0);

    _resWindow->SetResTrees(Parser.GetValidASTs());
    _resWindow->show();
    _mainWindow->setEnabled(false);

}
void AppManager::TextChanged(QString s)
{
    _inpText = s;
}

void AppManager::GrammChanged(QString s)
{
    _inpGramm = s;
}

void AppManager::PattChanged(QString s)
{
    _inpPatt = s;
}

void AppManager::RegExpChanged(QString s)
{
    _inpRegExp = s;
}

void AppManager::TerminalsChanged(QString s)
{
    _terminals = s;
}

void AppManager::NonTerminalsChanged(QString s)
{
    _nonTerminals = s;
}

void AppManager::MetaVChanged(QString s)
{
    _metaV = s;
}

void AppManager::ResClosed()
{
    _mainWindow->setEnabled(true);
}
