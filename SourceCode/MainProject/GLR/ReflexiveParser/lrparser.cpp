#include "lrparser.h"

LRParser::LRParser(Grammar g, QVector<Token> t)
{
    _grammar = g;
    _text = t;
}

void LRParser::Generate()
{
    for(int i = 0 ; i < _grammar.Size() ; i++)
    {
        if(!_table.GetAllToken().contains(_grammar.GetRule(i).Left()))
        {
            _table.AddToken(_grammar.GetRule(i).Left());
        }
        QVector<Token> Righten = _grammar.GetRule(i).Right();
        for(int j = 0 ; j < Righten.size(); j++)
        {
            if(!_table.GetAllToken().contains(Righten[j]))
            {
                _table.AddToken(Righten[j]);
            }
        }
    }
    _table.AddToken(_grammar.EndOfText);// or _grammar.EndOfText Token("#")
    _table.SetStateSize();

    QVector<QVector<ElementLR1>> I_Piles;

    I_Piles.push_back(Closure(ElementLR1(_grammar.GetRule(0),{_grammar.EndOfText}))); // # -> jelenti a szöveg végét/verem alját
    for(int i = 0 ; i < I_Piles.size(); i++)
    {
        for(int j = 0 ; j < _table.GetAllToken().size(); j++)
        {
            QVector<ElementLR1> I = Read(I_Piles[i],_table.GetToken(j));

            if(I.size() != 0)
            {
                if(I_Piles.contains(I))
                {
                    int prevState = I_Piles.indexOf(I);
                    _table.SetState(i,prevState,_table.GetToken(j),Action(Step,prevState));
                    continue;
                }
                I_Piles.push_back(I);
                _table.SetState(i,I_Piles.size()-1,_table.GetToken(j),Action(Step,I_Piles.size()-1));
            }
            for(int k = 0 ; k < I.size() ; k++)
            {
                if(I[k].Right().isEmpty())
                {
                    for(int g = 0 ; g < I[k].LookahedToken().size(); g++)
                    {
                        _table.SetState(i,_table.GetAllToken().indexOf(I[k].LookahedToken()[g]),I[k].LookahedToken()[g],Action(Reduce,I[k]));
                    }
                }
                if(I[k].Right().size() == I[k].GetDot())
                {
                    if(I[k].Left() == _grammar.StartToken) // Accept
                    {
                        if(I[k].LookahedToken().size() == 0)
                        {
                            _table.SetState(I_Piles.size()-1,_table.GetAllToken().indexOf(_grammar.EndOfText),_grammar.EndOfText,Action(Ok));
                        }
                        for(int l = 0 ; l <I[k].LookahedToken().size(); l++)
                        {
                            _table.SetState(I_Piles.size()-1,_table.GetAllToken().indexOf(I[k].LookahedToken()[l]),I[k].LookahedToken()[l],Action(Ok));
                        }
                    }else //reduce state
                    {
                        for(int g = 0 ; g < I[k].LookahedToken().size(); g++)
                        {
                            _table.SetState(I_Piles.size()-1,_table.GetAllToken().indexOf(I[k].LookahedToken()[g]),I[k].LookahedToken()[g],Action(Reduce,I[k]));
                        }
                    }

                }
            }
        }
    }
}

void LRParser::Parse()
{

    QVector<Token> text;
    for(int ta = 0 ; ta < 2 ; ta++)
    {
        if(_progText.isEmpty())
        {
            ta++;
        }

        if(ta == 0)
        {
            text = _progText;
        }else
        {
            text = _text;
        }

        int State = 0;
        Token NextToken = text[0];
        Token RedToken;
        bool reduced = false;
        bool parsing = true;
        QVector<BoolToken> IsMetaNonTerminal;
        int i = 0;
        _stack.clear();
        _brancesToProcess.clear();
        _rulesUsed.clear();
        _allResult.clear();
        _parsedRules.clear();

        StackElement ActStarter(_grammar.EndOfText,0);
        _stack.push_back(StackElement(_grammar.EndOfText,0));
        IsMetaNonTerminal.push_back({false,Token()});

        int RuleToContinue = -1;

        _brancesToProcess.push_back(ForkElement(NextToken,i,_stack,State,_rulesUsed,RuleToContinue,IsMetaNonTerminal,ActStarter,false,Token("")));

        //starting problem
        for(int g = 0 ; g < _table.GetNoStates() ; g++)
        {
            for(int j = 0 ; j < _table.GetAllToken().size() ; j++)
            {
                for(int k = 0 ; k < _table.GetState(g,_table.GetAllToken()[j]).size() ; k++)
                {
                    if(_table.GetState(g,_table.GetAllToken()[j])[k]._indicator == Step)
                    {
                        _stack.clear();
                        IsMetaNonTerminal.clear();
                        _stack.push_back(StackElement(_grammar.EndOfText,g));
                        IsMetaNonTerminal.push_back({false,Token()});
                        State = g;
                        _brancesToProcess.push_back(ForkElement(NextToken,i,_stack,State,_rulesUsed,k,IsMetaNonTerminal,ActStarter,false,Token("")));
                    }
                }
            }
        }

        for(int p = 0 ; p < _brancesToProcess.size() ; p++)
        {
            if(p != 0)
            {
                NextToken = _brancesToProcess[p]._nextToken;
                i = _brancesToProcess[p]._textIndex;
                _stack = _brancesToProcess[p]._stack;
                State = _brancesToProcess[p]._state;
                _rulesUsed = _brancesToProcess[p]._rulesUsed;
                RuleToContinue = _brancesToProcess[p]._ruleToContinue;
                parsing = true;
                IsMetaNonTerminal = _brancesToProcess[p]._ismetanonterminal;
                ActStarter = _brancesToProcess[p]._actStarter;
                reduced = _brancesToProcess[p]._reduced;
                RedToken = _brancesToProcess[p]._reducedToken;
            }

            while(parsing)
            {
                if(reduced)
                {
                    NextToken = RedToken;
                    reduced = false;
                }else
                {
                    if(i >= text.size())
                    {
                        NextToken =_grammar.EndOfText;
                    }else{
                        NextToken = text[i];
                    }
                }



                QVector<Action> ToDo;

                //Fork on -MetaV -------
                if(NextToken ==_grammar.MetaToken)
                {
                    for(int k = 0 ; k < PossibleTokens(State).size() ; k++)
                    {
                        QVector<Token> Pt = PossibleTokens(State);
                        ToDo = _table.GetState(State,PossibleTokens(State)[k]);
                        if(ToDo.size() >= 1)
                        {
                            for(int j = 0 ; j < ToDo.size() ;j++)
                            {
                               if(ToDo[j]._indicator == Step)
                               {
                                   int newState = ToDo[j]._stepState;

                                   _stack.push_back(StackElement(PossibleTokens(State)[k],newState));
                                   IsMetaNonTerminal.push_back({true,text[i+1]});

                                   _brancesToProcess.push_back(ForkElement(PossibleTokens(State)[k],i+2,_stack,newState,_rulesUsed,-1,IsMetaNonTerminal,ActStarter,false,Token("")));
                                   _stack.pop_back();
                                   IsMetaNonTerminal.pop_back();

                               }
                               else if(ToDo[j]._indicator == Reduce)
                               {
                                   QVector<StackElement> copy = _stack;
                                   bool IsMeta = false;
                                   QVector<int> meta_ind = {};
                                   QVector<Token> metaVar = {};
                                   ElementLR1 rule = ToDo[j]._rule;
                                   if(rule.Right().size() > _stack.size()-1) // err starter
                                   {
                                       parsing = false;
                                       _allResult.push_back(false);
                                       break;
                                   }
                                   for(int j = 0;  j < rule.Right().size(); j++ )
                                   {
                                       if(IsMetaNonTerminal.last()._bool == true)
                                       {
                                           IsMeta = true;
                                           meta_ind.push_back(rule.Right().size()-1-j);
                                           metaVar.push_back(IsMetaNonTerminal.last()._token);
                                       }
                                       _stack.pop_back();
                                       IsMetaNonTerminal.pop_back();

                                   }
                                   if(IsMeta)
                                   {
                                       _rulesUsed.push_back({_grammar.GetRuleIndex(rule.GetRule()),true,meta_ind,metaVar});
                                   }else
                                   {
                                       _rulesUsed.push_back({_grammar.GetRuleIndex(rule.GetRule()),false,meta_ind,metaVar});
                                   }

                                   RedToken = rule.Left();
                                   reduced = true;

                                   _brancesToProcess.push_back(ForkElement(PossibleTokens(State)[k],i,_stack,_stack.last()._state,_rulesUsed,-1,IsMetaNonTerminal,ActStarter,reduced,RedToken));
                                   _stack = copy;
                               }
                            }
                        }
                    }
                    break;
                }
                //------
                else
                {
                    ToDo = _table.GetState(State,NextToken);
                }

                if(ToDo.isEmpty())
                {
                    //error
                    parsing = false;
                    _allResult.push_back(false);
                }else if(ToDo.size() >= 1)
                {
                    int index = 0;
                    if(RuleToContinue == -1)
                    {
                        if(ToDo.size() > 1)
                        {
                            for(int j = 1 ; j < ToDo.size(); j++)
                            {
                                _brancesToProcess.push_back(ForkElement(NextToken,i,_stack,State,_rulesUsed,j,IsMetaNonTerminal,ActStarter,false,Token("")));
                            }
                        }
                    }
                    else
                    {
                        index = RuleToContinue;
                        RuleToContinue = -1;
                    }

                    if(_stack.size() == 1 && i >= text.size() && _grammar.IsNonTerminal(NextToken) && ToDo[index]._indicator == Step) // starter problem accept
                    {
                         parsing = false;
                         _allResult.push_back(true);
                    }
                    else if(ToDo[index]._indicator == Step)
                    {
                        QVector<Token> PossTokens = PossibleTokens(State);
                        if(!(PossTokens.isEmpty()))
                        {
                            if(PossTokens.contains(NextToken))
                            {
                                int newState = ToDo[index]._stepState;

                                State = newState;
                                _stack.push_back(StackElement(Token(NextToken),State));
                                IsMetaNonTerminal.push_back({false,Token()});

                                if(i < text.size())
                                {
                                    if(NextToken == text[i])
                                    {
                                        i++;
                                    }

                                }
                            }else //err
                            {
                                parsing = false;
                                _allResult.push_back(false);
                            }
                        }else //err
                        {
                            parsing = false;
                            _allResult.push_back(false);
                        }

                    }else if(ToDo[index]._indicator == Reduce)
                    {
                        bool IsMeta = false;
                        QVector<int> meta_ind = {};
                        QVector<Token> metaVar = {};
                        ElementLR1 rule = ToDo[index]._rule;
                        if(rule.Right().size() > _stack.size()-1) // err starter
                        {
                            parsing = false;
                            _allResult.push_back(false);
                            break;
                        }
                        for(int j = 0;  j < rule.Right().size(); j++ )
                        {
                            if(IsMetaNonTerminal.last()._bool == true)
                            {
                                IsMeta = true;
                                meta_ind.push_back(rule.Right().size()-1-j);
                                metaVar.push_back(IsMetaNonTerminal.last()._token);
                            }
                            _stack.pop_back();
                            IsMetaNonTerminal.pop_back();

                        }
                        if(IsMeta)
                        {
                            _rulesUsed.push_back({_grammar.GetRuleIndex(rule.GetRule()),true,meta_ind,metaVar});
                        }else
                        {
                            _rulesUsed.push_back({_grammar.GetRuleIndex(rule.GetRule()),false,meta_ind,metaVar});
                        }

                        State = _stack.last()._state;
                        RedToken = rule.Left();
                        reduced = true;
                    }else if(ToDo[index]._indicator == Ok)//elogadás
                    {                       
                        parsing = false;
                        if(IsMetaNonTerminal.last()._bool)
                        {
                            _rulesUsed.push_back({0,IsMetaNonTerminal.last()._bool,{0},{IsMetaNonTerminal.last()._token}});
                        }else
                        {
                            _rulesUsed.push_back({0,IsMetaNonTerminal.last()._bool,{},{IsMetaNonTerminal.last()._token}});
                        }

                        _stack.pop_back();
                        IsMetaNonTerminal.pop_back();
                        _allResult.push_back(true);

                    }else if(_stack.size() == 1 && i >= text.size()) //accept (starter problem)
                    {
                        _stack.pop_back();
                        IsMetaNonTerminal.pop_back();
                        parsing = false;
                        _allResult.push_back(true);
                    }
                    else
                    {
                        parsing = false;
                        _allResult.push_back(false);
                        break;
                    }

                }

                if(i > text.size())
                {
                    parsing = false;
                    _allResult.push_back(false);
                }
            }

            if(_stack.isEmpty() )
            {
                _allResult.push_back(false);
            }else if(!(_stack[0]._token == _grammar.EndOfText))
            {
                _allResult.push_back(false);
            }else if((_stack.size() > 0) && text.size() != i)
            {
                _allResult.push_back(false);
            }
            if(!_rulesUsed.isEmpty() && _allResult.last() == true)
            {
                if(ta == 0)
                {
                    Node* n= BuildCST();
                    if(!_programAST.contains(n))
                    {
                        _programAST.push_back(BuildCST());
                    }
                }else
                {
                    Node* n= BuildCST();
                    if(!_patternForest.contains(n))
                    {
                        _patternForest.push_back(BuildCST());
                    }
                }
            }
        }
        _result = _allResult.contains(true);
    }

}

bool LRParser::GetResult()
{
    return _result;
}

QVector<ElementLR1> LRParser::Read(QVector<ElementLR1> I, Token t)
{
    QVector<ElementLR1> result;
    for(int i = 0 ; i < I.size(); i++)
    {
        if(I[i].GetDot() != I[i].Right().size())
        {
            if(I[i].Right()[I[i].GetDot()] == t)
            {
                ElementLR1 n = I[i];
                int d = n.GetDot();
                n.SetDot(d+1);
                result.push_back(n);
            }
        }
    }
    QVector<ElementLR1> a;
    for(int i = 0 ; i < result.size(); i++)
    {
        QVector<ElementLR1> v = Closure(result[i]);
        for(int j = 0 ; j < v.size() ; j++)
        {
            if(!a.contains(v[j]))
            {
                a.append(v[j]);
            }
        }
    }
    return a;
}

QVector<ElementLR1> LRParser::Closure(ElementLR1 r)
{
    QVector<ElementLR1> result;
    result.push_back(r);

    for(int j = 0 ; j < result.size(); j++)
    {
        if(result[j].GetDot() != result[j].Right().size())
        {
            for(int i = 0 ; i < _grammar.Size(); i++)
            {
                if(result[j].Right()[result[j].GetDot()] == _grammar.GetRule(i).Left())
                {
                    if(result[j].GetDot()+1 < result[j].Right().size())
                    {
                        QVector<Token> f;

                        f.push_back(result[j].Right()[result[j].GetDot()+1]);

                        ElementLR1 n(_grammar.GetRule(i),First(f));
                        n.SetDot(0);
                        if(!result.contains(n))
                        {
                            result.push_back(n);
                        }

                    }else
                    {
                        ElementLR1 n(_grammar.GetRule(i),result[j].LookahedToken());
                        n.SetDot(0);
                        if(!result.contains(n))
                        {
                            result.push_back(n);
                        }
                    }
                }
            }
        }
    }
    return result;
}

ParserTable LRParser::GetTable()
{
    return _table;
}

QVector<Token> LRParser::PossibleTokens(int state)
{
    QVector<Token> result;

    for(int i = 0 ; i < _table.GetAllToken().size(); i++)
    {
        if(!(_table.GetState(state,_table.GetAllToken()[i]).isEmpty()))
        {
            result.push_back(_table.GetToken(i));
        }
    }
    return result;
}

QVector<Token> LRParser::First(QVector<Token> T)
{
    QVector<Token> res;
    if(_grammar.IsTerminal(T[0]))
    {
        return {T[0]};
    }else if(T[0].Get() == "")
    {
        QVector<Token> res;
        for(int i = 1 ; i < T.size();i++)
        {
            res.append(T[i]);
        }
        return res;
    }else
    {
        QVector<Token> NonTerminalsToCheck = {T[0]};
        for(int j = 0 ; j < NonTerminalsToCheck.size(); j++)
        {
            for(int i = 0 ; i < _grammar.Size() ; i++)
            {
                if(_grammar.GetRule(i).Left() == NonTerminalsToCheck[j])
                {
                    Rule R = _grammar.GetRule(i);
                    if(_grammar.GetTerminals().contains(R.Right()[0]) && !(res.contains(R.Right()[0])))
                    {
                        res.push_back(R.Right()[0]);
                    }else
                    {
                        if(R.Right()[0] == T[0])
                        {
                            continue;
                        }else if(R.Right().isEmpty())
                        {
                            continue;
                        }else
                        {
                            NonTerminalsToCheck.push_back(R.Right()[0]);
                        }
                    }
                }
            }
        }

    return res;
    }

}

QVector<RuleNo> LRParser::GetRulesUsed()
{
    return _rulesUsed;
}

void LRParser::SetProgText(QVector<Token> s)
{
    _progText = s;
}

void LRParser::SetProgramAST(Node *n)
{
    _programAST.push_back(n);
}

QVector<Node *> LRParser::GetValidASTs()
{
    return _validASTs;
}

Node *LRParser::GetMostRightenNodewNonTerm(Node* n,Token t)
{
    Node* res = nullptr;
    if(n->ChildNumber() == 0 && n->GetToken() == t && n->GetIsmeta() == false)
    {
        return n;
    }else
    {
        for(int i = n->ChildNumber() ; i > 0  ; i--)
        {
            res = GetMostRightenNodewNonTerm(n->GetChild(i-1) , t);
            if(res != nullptr)
            {
                return res;
            }
        }
    }
    return  nullptr;
}

QVector<Node*> LRParser::GetPatternForest()
{
    return _patternForest;
}

void LRParser::printCST(Node* node)
{
    for(int i = 0 ; i < node->ChildNumber() ; i++)
    {
        printCST(node->GetChild(i));
    }
}

void LRParser::CalValidMatches()
{
    for(int j = 0 ; j < _programAST.size() ; j++)
    {
        for(int i = 0 ; i < _patternForest.size() ; i++)
        {
            Node *n = new Node(*_patternForest[i]);
            bool valid = ProcessCSTs(n,_programAST[j]);
            if(valid)
            {
                bool same = false;
                for(int k = 0 ; k < _validASTs.size() ;k++)
                {
                    if(_validASTs[k]->isSame(n))
                    {
                        same = true;
                        break;
                    }
                    same = false;
                }
                if(!same)
                {
                    _validASTs.push_back(n);
                    ResetProgCST(_programAST[j]);
                }
            }
        }
    }

}

bool LRParser::ProcessCSTs(Node *patternNode, Node *programNode)
{
    if(patternNode->GetToken() == programNode->GetToken())
    {
        if(patternNode->GetIsmeta())
        {
            bool res = true;
            for(int i = 0 ; i < programNode->ChildNumber() ; i++)
            {
                patternNode->AddChild(new Node(*programNode->GetChild(i)));
                if(_grammar.IsNonTerminal(programNode->GetChild(i)->GetToken()))
                {
                    res *= ProcessCSTs(patternNode->GetChild(i),programNode->GetChild(i));
                }
            }
            return res;
        }else
        {
            if(patternNode->ChildNumber() == programNode->ChildNumber())
            {
                if(patternNode->ChildNumber() != 0)
                {
                    bool res = true;
                    for(int i = 0 ; i < patternNode->ChildNumber() ; i++)
                    {
                        res *= ProcessCSTs(patternNode->GetChild(i),programNode->GetChild(i));
                    }
                    return res;
                }else
                {
                    return true;
                }

            }
        }
    }
    return false;
}

QVector<Token> LRParser::GetText()
{
    return _text;
}

QVector<Token> LRParser::GetProgText()
{
    return _progText;
}

void LRParser::ResetProgCST(Node *n)
{
    n->SetIsMeta(false);
    n->SetMetaVar(Token(""));
    for(int i = 0 ; i < n->ChildNumber() ; i++)
    {
        ResetProgCST(n->GetChild(i));
    }
}

Node* LRParser::BuildCST()
{
    Node* node;
    if(_grammar.GetRule(_rulesUsed.last()._ruleNo).Left() == _grammar.StartToken)
    {
        node = new Node(_grammar.GetRule(_rulesUsed.last()._ruleNo).Right()[0]);
        node->SetIsMeta(_rulesUsed.last()._isMeta);
    }else
    {
         node = new Node(_grammar.GetRule(_rulesUsed.last()._ruleNo).Left());
         node->SetIsMeta(false);
    }

    Node* ASTRoot = node;


    for(int i = 0 ; i < _rulesUsed.size() ; i++)
    {
        Rule r = _grammar.GetRule(_rulesUsed[_rulesUsed.size()-1-i]._ruleNo);
        node = GetMostRightenNodewNonTerm(ASTRoot,r.Left());
        if(node == nullptr)
        {
            continue;
        }
        if(r.Right().size() == 0)//epsilon
        {
            node->AddChild(new Node(Token(""),false));
        }
        for(int j = 0 ; j < r.Right().size() ; j++)
        {
            if(_rulesUsed[_rulesUsed.size()-1-i]._metaind.contains(j))
            {
                int ind = _rulesUsed[_rulesUsed.size()-1-i]._metaind.indexOf(j);
                node->AddChild(new Node(r.Right()[j],true,_rulesUsed[_rulesUsed.size()-1-i]._metaVar[ind]));

            }else
            {
                node->AddChild(new Node(r.Right()[j],false));
            }
        }
    }
    return ASTRoot;
}
