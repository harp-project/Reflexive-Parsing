#include "token.h"


Token::Token()
{

}

Token::Token(QString s)
{
    _token = s;
}

QString Token::Get()
{
    return _token;
}

bool Token::operator==(const Token b) const
{
    return this->_token == b._token;
}
