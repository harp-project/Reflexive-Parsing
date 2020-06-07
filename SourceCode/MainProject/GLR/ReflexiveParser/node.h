#ifndef NODE_H
#define NODE_H
#include "token.h"
#include "QVector"

class Node
{
public:
    Node();
    ~Node();
    Node(Token);
    Node(Token,bool,Token);
    Node(Token,bool);
    Node(const Node&);
    void SetToken(Token);
    Token GetToken();
    void AddChild(Node*);
    int ChildNumber();
    Node* GetChildwToken(Token);
    Node* GetChild(int i);
    bool operator==(Node);
    bool operator==(const Node) const;
    void SetIsMeta(bool);
    bool GetIsmeta();
    Token GetMetaVar();
    void SetMetaVar(Token);
    bool isSame(Node*);

private:
    Token _token;
    QVector<Node*> _children;
    bool _isMeta;
    Token _metaVar;

};




#endif // NODE_H
