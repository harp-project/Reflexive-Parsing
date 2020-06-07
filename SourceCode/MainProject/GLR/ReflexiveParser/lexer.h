#ifndef LEXER_H
#define LEXER_H

#include <QRegularExpression>
#include <QVector>
#include "token.h"

struct MatchElement{
    bool _hasMatch;
    bool _hasPartialMatch;
    bool operator==(const MatchElement m) const{
        return _hasMatch == m._hasMatch && _hasPartialMatch == m._hasPartialMatch;
    }
};
struct RegExpWName{
    QRegularExpression _regExp;
    QString _name;
};

class Lexer
{
public:
    Lexer();
    ~Lexer();
    void AddRegExp(QString,QString);
    void SetInput(QString);
    void LexInput();
    QVector<Token> GetResTokens();
    void SetMetaVariable(Token);
private:
    QVector<RegExpWName> _regExps;
    QString _input;
    QVector<Token> _resTokens;
    Token* _metaV = NULL;
    QRegularExpression _metaVNameRegExp = QRegularExpression(QRegularExpression::anchoredPattern("[_a-zA-Z][_a-zA-Z0-9]*"));
};

#endif // LEXER_H
