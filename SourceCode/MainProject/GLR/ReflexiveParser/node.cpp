#include "node.h"

Node::Node()
{

}

Node::~Node()
{
    if(_children.size() != 0)
    {
        qDeleteAll(_children);
    }

}

Node::Node(Token t)
{
    _token = t;
}

Node::Node(Token t, bool b,Token m)
{
    _token = t;
    _isMeta = b;
    _metaVar = m;
}

Node::Node(Token t, bool b)
{
    _token = t;
    _isMeta = b;
}

Node::Node(const Node &n)
{
    _token = n._token;
    _isMeta = n._isMeta;
   _metaVar = n._metaVar;
   for(int i = 0 ; i < n._children.size() ; i++)
   {
       _children.push_back(new Node(*n._children[i]));
   }
}

void Node::SetToken(Token t)
{
    _token = t;
}

Token Node::GetToken()
{
    return _token;
}

void Node::AddChild(Node* n)
{
    _children.push_back(n);
}

int Node::ChildNumber()
{
    if(_children.isEmpty())
    {
        return 0;
    }
    else
    {
        return _children.size();
    }
}

Node* Node::GetChildwToken(Token t)
{
    Node* res = nullptr;

    for(int i = 0 ; i < _children.size() ; i++)
    {
        if(_children[i]->_token == t)
        {
            res = _children[i];
            break;
        }
    }
    return res;
}

Node *Node::GetChild(int i)
{
    return  _children[i];
}

bool Node::operator==(Node r)
{
    if(!(_token == r._token))
    {
        return false;
    }
    if(_children.isEmpty() && r._children.isEmpty() && _token == r._token && _isMeta == r._isMeta)
    {
        return true;
    }
    int childs = 0;
    if(_token == r._token && _children.size() == r._children.size())
    {
        for(int i = 0 ; i < _children.size() ; i++)
        {
            if(_children[i] == r._children[i])
            {
                childs++;
            }
        }
        return  childs ==_children.size() ;
    }
    return false;
}

bool Node::operator==(const Node r) const
{
    if(!(_token == r._token))
    {
        return false;
    }
    if(_children.isEmpty() && r._children.isEmpty() && _token == r._token && _isMeta == r._isMeta)
    {
        return true;
    }
    int childs = 0;
    if(_token == r._token && _children.size() == r._children.size())
    {
        for(int i = 0 ; i < _children.size() ; i++)
        {
            if(_children[i] == r._children[i])
            {
                childs++;
            }
        }
        return  childs ==_children.size() ;
    }
    return false;
}

void Node::SetIsMeta(bool b)
{
    _isMeta = b;
}

bool Node::GetIsmeta()
{
    return _isMeta;
}

Token Node::GetMetaVar()
{
    return _metaVar;
}

void Node::SetMetaVar(Token t)
{
    _metaVar = t;
}

bool Node::isSame(Node *r)
{
    if(!(_token == r->_token))
    {
        return false;
    }
    if(_children.isEmpty() && r->_children.isEmpty() && _token == r->_token && _isMeta == r->_isMeta)
    {
        return true;
    }
    int childs = 0;
    if(_token == r->_token && _children.size() == r->_children.size())
    {
        for(int i = 0 ; i < _children.size() ; i++)
        {
            if(_children[i]->isSame(r->_children[i]))
            {
                childs++;
            }
        }
        return  childs ==_children.size() ;
    }
    return false;
}
