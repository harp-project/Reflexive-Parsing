#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include "mainwindow.h"
#include "lrparser.h"
#include "lexer.h"
#include "reswindow.h"

class AppManager : public QObject
{
    Q_OBJECT
public:
    explicit AppManager(QObject *parent = nullptr);
    ~AppManager();

signals:
    void Error(QString);
public slots:
    void Start();
    void TextChanged(QString);
    void GrammChanged(QString);
    void PattChanged(QString);
    void RegExpChanged(QString);
    void TerminalsChanged(QString);
    void NonTerminalsChanged(QString);
    void MetaVChanged(QString);
    void ResClosed();

private:
    MainWindow* _mainWindow;
    ResWindow* _resWindow;

    QString _inpText;
    QString _inpGramm;
    QString _inpPatt;
    QString _inpRegExp;
    QString _terminals;
    QString _nonTerminals;
    QString _metaV;

    QVector<Token> _inpTextToken;
    QVector<Rule> _rules;
    QVector<Token> _inpPattToken;
    QVector<Token> _terminalsToken;
    QVector<Token> _nonTerminalsToken;

};

#endif // APPMANAGER_H
