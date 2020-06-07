#ifndef TOKEN_H
#define TOKEN_H

#include "QString"

class Token
{
public:
    Token();
    Token(QString);
    QString Get();
    void Set(QString);
    bool operator==(const Token) const;

private:
    QString _token;

};

#endif // TOKEN_H
