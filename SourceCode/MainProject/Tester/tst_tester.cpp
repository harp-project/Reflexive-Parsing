#include <QtTest>
#include "lrparser.h"

class Tester : public QObject
{
    Q_OBJECT

private slots:
    void Grammarfunctions();
    void FirstSet();
    void Closure_Read();
    void TableGen();
    void Parser_LR1Grammar();
    void Parser_fail();
    void Parser_GrammarWithEpsilon();
    void Parser_GrammarGLR();
    void Parser_Input_With_Metavariable();
    void UsedRules();
    void CSTEquiv();
    void ValidMatches();
    void StarterProblem();
    void LexerTest();
    void TestRun();

};

void Tester::Grammarfunctions()
{
    Grammar G;
    G.SetNonTerminals({Token("Q")});
    G.SetTerminals({Token("#")});

    Token t1("Q");
    Token t2("S");
    QVector<Token> v1;
    v1.push_back(t2);
    Rule r1(t1,v1);

    G.AddRule(r1);
    G.SetMetaToken(Token("@"));
    G.UniqueStart_End();
    G.InsertUniqueStartRule();

    QVERIFY(!(G.StartToken == Token("Q")));
    QVERIFY(!(G.EndOfText == Token("#")));
    QVERIFY(G.MetaToken == Token("@"));
    QVERIFY(G.Size() == 2);
    QVERIFY(G.GetRule(0).Left() == G.StartToken);
}

void Tester::FirstSet()
{
    Grammar G;

    G.SetTerminals({Token("a"),Token("b"),Token("c"),Token("d")});
    G.SetNonTerminals({Token("S"),Token("A"),Token("Q")});

    Token t1("Q");

    Token t2("S");
    QVector<Token> v1;
    v1.push_back(t2);
    Rule r1(t1,v1);

    Token t01("S");
    Token t02("a");
    Token t02_1("S");
    Token t02_2("A");
    QVector<Token> v2;
    v2.push_back(t02);
    v2.push_back(t02_1);
    v2.push_back(t02_2);
    Rule r2(t01,v2);

    Token t3("S");
    Token t4("A");
    QVector<Token> v3;
    v3.push_back(t4);
    Rule r3(t3,v3);

    Token t5("A");
    Token t6("b");
    Token t6_1("A");
    Token t6_2("c");
    QVector<Token> v4;
    v4.push_back(t6);
    v4.push_back(t6_1);
    v4.push_back(t6_2);
    Rule r4(t5,v4);

    Token t7("A");
    Token t8("d");
    QVector<Token> v5;
    v5.push_back(t8);
    Rule r5(t7,v5);

    G.AddRule(r1);
    G.AddRule(r2);
    G.AddRule(r3);
    G.AddRule(r4);
    G.AddRule(r5);
    G.UniqueStart_End();
    G.InsertUniqueStartRule();

    QVector<Token> text = {Token("a"),Token("b"),Token("c")};

    LRParser E(G,text);
    E.SetProgText(text);

    QVector<Token>res = E.First(r2.Right());
    QVERIFY(res == QVector<Token>{Token("a")});

    res = E.First(r3.Right());
    QVERIFY(res == (QVector<Token>{Token("b"),Token("d")}));

    res = E.First(r4.Right());
    QVERIFY(res == (QVector<Token>{Token("b")}));
    res = E.First(r5.Right());
    QVERIFY(res == (QVector<Token>{Token("d")}));
}

void Tester::Closure_Read()
{
    Grammar G;
    G.SetNonTerminals({Token("Q"),Token("S"),Token("U"),Token("E"),Token("V"),});
    G.SetTerminals({Token("a"),Token("=")});
    Token t1("Q");
    Token t2("S");
    QVector<Token> v1;
    v1.push_back(t2);
    Rule r1(t1,v1);

    Token t01("S");
    Token t02("U");
    QVector<Token> v2;
    v2.push_back(t02);
    Rule r2(t01,v2);

    Token t3("S");
    Token t4("E");
    QVector<Token> v3;
    v3.push_back(t4);
    Rule r3(t3,v3);

    Token t5("U");
    Token t6("a");
    QVector<Token> v4;
    v4.push_back(t6);
    Rule r4(t5,v4);

    Token t7("E");
    Token t8("V");
    Token t8_1("=");
    Token t8_2("V");
    QVector<Token> v5;
    v5.push_back(t8);
    v5.push_back(t8_1);
    v5.push_back(t8_2);
    Rule r5(t7,v5);

    Token t11("V");
    Token t12("a");
    QVector<Token> v7;
    v7.push_back(t12);
    Rule r6(t11,v7);

    G.AddRule(r1);
    G.AddRule(r2);
    G.AddRule(r3);
    G.AddRule(r4);
    G.AddRule(r5);
    G.AddRule(r6);
    G.UniqueStart_End();
    G.InsertUniqueStartRule();

    QVector<Token> text = {Token("a"),Token("b"),Token("c")};

    LRParser E(G,text);
    QVector<ElementLR1> T = E.Closure(ElementLR1(r1,{G.EndOfText}));
    QVector<ElementLR1> Exp = {ElementLR1(r1,{G.EndOfText}),ElementLR1(r2,{G.EndOfText}),ElementLR1(r3,{G.EndOfText}),ElementLR1(r4,{G.EndOfText}),ElementLR1(r5,{G.EndOfText}),ElementLR1(r6,{Token("=")})};
    QVERIFY(T == Exp);

    T = E.Closure(ElementLR1(Rule(Token("S"),{}),{G.EndOfText}));

    QVERIFY(T == QVector<ElementLR1>{ElementLR1(Rule(Token("S"),{}),{(G.EndOfText)})});
    QVector<ElementLR1> T2 = E.Read(T,Token("C"));

    Exp.clear();
    QVERIFY(T2 == Exp);
}

void Tester::TableGen()
{
    Grammar G;
    G.SetNonTerminals({Token("Q"),Token("S"),Token("U"),Token("E"),Token("V"),});
    G.SetTerminals({Token("a"),Token("=")});

    Token t1("S");
    Token t2("U");
    QVector<Token> v1;
    v1.push_back(t2);
    Rule r1(t1,v1);

    Token t01("S");
    Token t02("E");
    QVector<Token> v2;
    v2.push_back(t02);
    Rule r2(t01,v2);

    Token t3("U");
    Token t4("a");
    QVector<Token> v3;
    v3.push_back(t4);
    Rule r3(t3,v3);

    Token t5("E");
    Token t6("V");
    Token t6_1("=");
    Token t6_2("V");
    QVector<Token> v4;
    v4.push_back(t6);
    v4.push_back(t6_1);
    v4.push_back(t6_2);
    Rule r4(t5,v4);

    Token t7("V");
    Token t8("a");
    QVector<Token> v5;
    v5.push_back(t8);
    Rule r5(t7,v5);

    G.AddRule(r1);
    G.AddRule(r2);
    G.AddRule(r3);
    G.AddRule(r4);
    G.AddRule(r5);
    G.UniqueStart_End();
    G.InsertUniqueStartRule();

    QVector<Token> text = {Token("a")};

    LRParser E(G,text);

    E.Generate();

    ParserTable Table = E.GetTable();

    QVector<Token> Exp = {G.StartToken,Token("S"),Token("U"),Token("E"),Token("a"),Token("V"),Token("="),G.EndOfText};

    QVERIFY(Table.GetAllToken() == Exp);
    QVERIFY(Table.GetNoStates() == 9);
    QVERIFY(Table.GetState(0,Token("a"))[0]._indicator == Step);
    QVERIFY(Table.GetState(0,Token("S"))[0]._indicator == Step);
    QVERIFY(Table.GetState(0,Token("U"))[0]._indicator == Step);
    QVERIFY(Table.GetState(0,Token("E"))[0]._indicator == Step);
    QVERIFY(Table.GetState(0,Token("V"))[0]._indicator == Step);
    QVERIFY(Table.GetState(1,Token("#"))[0]._indicator == Ok);
    QVERIFY(Table.GetState(2,Token("#"))[0]._indicator == Reduce);
    QVERIFY(Table.GetState(3,Token("#"))[0]._indicator == Reduce);
    QVERIFY(Table.GetState(4,Token("="))[0]._indicator == Reduce);
    QVERIFY(Table.GetState(4,Token("#"))[0]._indicator == Reduce);
    QVERIFY(Table.GetState(5,Token("="))[0]._indicator == Step);
    QVERIFY(Table.GetState(6,Token("a"))[0]._indicator == Step);
    QVERIFY(Table.GetState(6,Token("V"))[0]._indicator == Step);
    QVERIFY(Table.GetState(7,Token("#"))[0]._indicator == Reduce);
    QVERIFY(Table.GetState(8,Token("#"))[0]._indicator == Reduce);

}

void Tester::Parser_LR1Grammar()
{
    Grammar G;
    G.SetNonTerminals({Token("Q"),Token("S"),Token("U"),Token("E"),Token("V"),});
    G.SetTerminals({Token("a"),Token("=")});
    Token t1("Q");
    Token t2("S");
    QVector<Token> v1;
    v1.push_back(t2);
    Rule r1(t1,v1);

    Token t01("S");
    Token t02("U");
    QVector<Token> v2;
    v2.push_back(t02);
    Rule r2(t01,v2);


    Token t3("S");
    Token t4("E");
    QVector<Token> v3;
    v3.push_back(t4);
    Rule r3(t3,v3);

    Token t5("U");
    Token t6("a");
    QVector<Token> v4;
    v4.push_back(t6);
    Rule r4(t5,v4);

    Token t7("E");
    Token t8("V");
    Token t8_1("=");
    Token t8_2("V");
    QVector<Token> v5;
    v5.push_back(t8);
    v5.push_back(t8_1);
    v5.push_back(t8_2);
    Rule r5(t7,v5);

    Token t11("V");
    Token t12("a");
    QVector<Token> v7;
    v7.push_back(t12);
    Rule r6(t11,v7);

    G.AddRule(r1);
    G.AddRule(r2);
    G.AddRule(r3);
    G.AddRule(r4);
    G.AddRule(r5);
    G.AddRule(r6);
    G.UniqueStart_End();
    G.InsertUniqueStartRule();

    QVector<Token> text = {Token("a"),Token("="),Token("a")};

    LRParser E(G,text);
    E.Generate();
    E.Parse();
    QVERIFY(E.GetResult());

    text = {Token("a")};

    LRParser E2(G,text);
    E2.Generate();
    E2.Parse();
    QVERIFY(E2.GetResult());
}

void Tester::Parser_fail()
{
    Grammar G;
    G.SetNonTerminals({Token("Q"),Token("S"),Token("U"),Token("E"),Token("V"),});
    G.SetTerminals({Token("a"),Token("=")});
    Token t1("Q");
    Token t2("S");
    QVector<Token> v1;
    v1.push_back(t2);
    Rule r1(t1,v1);

    Token t01("S");
    Token t02("U");
    QVector<Token> v2;
    v2.push_back(t02);
    Rule r2(t01,v2);


    Token t3("S");
    Token t4("E");
    QVector<Token> v3;
    v3.push_back(t4);
    Rule r3(t3,v3);

    Token t5("U");
    Token t6("a");
    QVector<Token> v4;
    v4.push_back(t6);
    Rule r4(t5,v4);

    Token t7("E");
    Token t8("V");
    Token t8_1("=");
    Token t8_2("V");
    QVector<Token> v5;
    v5.push_back(t8);
    v5.push_back(t8_1);
    v5.push_back(t8_2);
    Rule r5(t7,v5);

    Token t11("V");
    Token t12("a");
    QVector<Token> v7;
    v7.push_back(t12);
    Rule r6(t11,v7);

    G.AddRule(r1);
    G.AddRule(r2);
    G.AddRule(r3);
    G.AddRule(r4);
    G.AddRule(r5);
    G.AddRule(r6);
    G.UniqueStart_End();
    G.InsertUniqueStartRule();


    QVector<Token> text = {Token("a"),Token("m")};

    LRParser E(G,text);
    E.Generate();
    E.Parse();
    QVERIFY(!E.GetResult());
}

void Tester::Parser_GrammarWithEpsilon()
{
    Grammar G;
    G.SetNonTerminals({Token("Q"),Token("S")});
    G.SetTerminals({Token("("),Token(")")});
    Token t1("Q");
    Token t2("S");
    QVector<Token> v1;
    v1.push_back(t2);
    Rule r1(t1,v1);

    Token t01("S");
    QVector<Token> v2 = {};
    Rule r2(t01,v2);

    Token t3("S");
    Token t4("(");
    Token t4_1("S");
    Token t4_2(")");
    Token t4_3("S");
    QVector<Token> v3;
    v3.push_back(t4);
    v3.push_back(t4_1);
    v3.push_back(t4_2);
    v3.push_back(t4_3);
    Rule r3(t3,v3);

    G.AddRule(r1);
    G.AddRule(r2);
    G.AddRule(r3);
    G.UniqueStart_End();
    G.InsertUniqueStartRule();

    QVector<Token> text = {Token("("),Token("("),Token("("),Token(")"),Token(")"),Token(")")};

    LRParser E(G,text);
    E.Generate();
    E.Parse();
    QVERIFY(E.GetResult());
}

void Tester::Parser_GrammarGLR()
{
    Grammar G;
    G.SetNonTerminals({Token("Q"),Token("S")});
    G.SetTerminals({Token("1"),Token("+")});
    Token t1("Q");
    Token t2("S");
    QVector<Token> v1;
    v1.push_back(t2);
    Rule r1(t1,v1);

    Token t01("S");
    Token t02("S");
    Token t02_1("+");
    Token t02_2("S");
    QVector<Token> v2;
    v2.push_back(t02);
    v2.push_back(t02_1);
    v2.push_back(t02_2);
    Rule r2(t01,v2);

    Token t3("S");
    Token t4("1");
    QVector<Token> v3;
    v3.push_back(t4);
    Rule r3(t3,v3);

    G.AddRule(r1);
    G.AddRule(r2);
    G.AddRule(r3);
    G.UniqueStart_End();
    G.InsertUniqueStartRule();

    QVector<Token> text = {Token("1"),Token("+"),Token("1"),Token("+"),Token("1")};

    LRParser E(G,text);
    E.Generate();
    E.Parse();
    QVERIFY(E.GetResult());
}

void Tester::Parser_Input_With_Metavariable()
{
    Grammar G;
    G.SetNonTerminals({Token("Q"),Token("S")});
    G.SetTerminals({Token("1"),Token("+")});
    Token t1("Q");
    Token t2("S");
    QVector<Token> v1;
    v1.push_back(t2);
    Rule r1(t1,v1);

    Token t01("S");
    Token t02("S");
    Token t02_1("+");
    Token t02_2("S");
    QVector<Token> v2;
    v2.push_back(t02);
    v2.push_back(t02_1);
    v2.push_back(t02_2);
    Rule r2(t01,v2);

    Token t3("S");
    Token t4("1");
    QVector<Token> v3;
    v3.push_back(t4);
    Rule r3(t3,v3);

    Token t5("S");
    Token t6("2");
    QVector<Token> v4;
    v4.push_back(t6);
    Rule r4(t3,v4);

    G.AddRule(r1);
    G.AddRule(r2);
    G.AddRule(r3);
    G.AddRule(r4);
    G.SetMetaToken(Token("@"));
    G.UniqueStart_End();
    G.InsertUniqueStartRule();

    QVector<Token> text = {Token("1"),Token("+"),Token("@"),Token("a")};

    LRParser E(G,text);
    E.Generate();
    E.Parse();
    QVERIFY(E.GetResult());
}

void Tester::UsedRules()
{
    Grammar G;
    G.SetNonTerminals({Token("S"),Token("A")});
    G.SetTerminals({Token("a")});

    Token t01("S");
    Token t02("a");
    QVector<Token> v2;
    v2.push_back(t02);
    Rule r2(t01,v2);

    G.AddRule(r2);
    G.UniqueStart_End();
    G.InsertUniqueStartRule();

    QVector<Token> text = {Token("a")};

    LRParser E(G,text);
    E.Generate();
    E.Parse();
    QVERIFY(E.GetResult());
    QVector<RuleNo> exp{{1,false,{},{}}};
    QVERIFY(E.GetRulesUsed() == exp);
}

void Tester::CSTEquiv()
{
    Node* Root1 = new Node;

    Root1->SetToken(Token("Q"));
    Node* child = new Node(Token("A"));
    child->AddChild(new Node(Token("a")));
    Root1->AddChild(child);
    Root1->AddChild(new Node(Token("b")));

    Node* Root2 = new Node;
    Root2->SetToken(Token("Q"));
    Node* child2 = new Node(Token("A"));
    child2->AddChild(new Node(Token("a")));
    Root2->AddChild(child2);
    Root2->AddChild(new Node(Token("b")));

    Node* Root3 = new Node;
    Root3->SetToken(Token("Q"));
    Node* child3 = new Node(Token("A"));
    child3->AddChild(new Node(Token("a")));
    Root3->AddChild(child3);
    Root3->AddChild(new Node(Token("B")));

    Node* Root4 = new Node;
    Root4->SetToken(Token("Q"));
    Node* child4 = new Node(Token("A"));
    child4->AddChild(new Node(Token("a")));
    child4->AddChild(new Node(Token("c")));
    Root4->AddChild(child4);
    Root4->AddChild(new Node(Token("b")));


    QVERIFY(Root1->isSame(Root2));
    QVERIFY(!(Root1->isSame(Root3)));
    QVERIFY(!(Root1->isSame(Root4)));
}

void Tester::ValidMatches()
{
    Grammar G;
    G.SetNonTerminals({Token("Q"),Token("S")});
    G.SetTerminals({Token("1"),Token("+")});
    Token t1("Q");
    Token t2("S");
    QVector<Token> v1;
    v1.push_back(t2);
    Rule r1(t1,v1);

    Token t01("S");
    Token t02("S");
    Token t02_1("+");
    Token t02_2("S");
    QVector<Token> v2;
    v2.push_back(t02);
    v2.push_back(t02_1);
    v2.push_back(t02_2);
    Rule r2(t01,v2);

    Token t3("S");
    Token t4("1");
    QVector<Token> v3;
    v3.push_back(t4);
    Rule r3(t3,v3);

    Token t5("S");
    Token t6("2");
    QVector<Token> v4;
    v4.push_back(t6);
    Rule r4(t3,v4);

    G.AddRule(r1);
    G.AddRule(r2);
    G.AddRule(r3);
    G.AddRule(r4);
    G.UniqueStart_End();
    G.InsertUniqueStartRule();

    QVector<Token> text = {Token("1"),Token("+"),Token("1")};
    QVector<Token> prog = {Token("1"),Token("+"),Token("1")};
    LRParser E(G,text);
    E.SetProgText(prog);
    E.Generate();
    E.Parse();
    E.CalValidMatches();
    QVERIFY(E.GetResult());
    QVERIFY(E.GetValidASTs().size() == 1);

    prog= {Token("1"),Token("+"),Token("1"),Token("+"),Token("1")};
    text = {Token("1"),Token("+"),Token("@"),Token("Metaname")};
    LRParser E2(G,text);
    E2.SetProgText(prog);
    E2.Generate();
    E2.Parse();
    E2.CalValidMatches();
    QVERIFY(E2.GetResult());
    QVERIFY(E2.GetValidASTs().size() == 1);

}

void Tester::StarterProblem()
{
    Grammar G;
    G.SetNonTerminals({Token("Q"),Token("S"),Token("Clss"),Token("Classes")});
    G.SetTerminals({Token("Class"),Token("Pkg")});
    Token t1("Q");
    Token t2("S");
    QVector<Token> v1;
    v1.push_back(t2);
    Rule r1(t1,v1);

    Token t01("S");
    Token t02("Pkg");
    Token t02_1("Clss");
    QVector<Token> v2;
    v2.push_back(t02);
    v2.push_back(t02_1);
    Rule r2(t01,v2);

    Token t3("Clss");
    Token t4("Class");
    Token t4_1("Name");
    Token t4_2("Classes");
    QVector<Token> v3;
    v3.push_back(t4);
    v3.push_back(t4_1);
    v3.push_back(t4_2);
    Rule r3(t3,v3);

    Token t5("Classes");
    Token t6("Class");
    Token t6_1("Name");
    Token t6_2("Classes");
    QVector<Token> v4;
    v4.push_back(t6);
    v4.push_back(t6_1);
    v4.push_back(t6_2);
    Rule r4(t5,v4);

    Token t7("Classes"); //eps rule
    QVector<Token> v5;
    Rule r5(t7,v5);

    G.AddRule(r1);
    G.AddRule(r2);
    G.AddRule(r3);
    G.AddRule(r4);
    G.AddRule(r5);
    G.UniqueStart_End();
    G.InsertUniqueStartRule();

    QVector<Token> text = {Token("Class"),Token("Name")};

    LRParser E(G,text);
    E.SetProgText(text);
    E.Generate();
    E.Parse();
    QVERIFY(E.GetResult());

}

void Tester::LexerTest()
{
    Lexer L;
    L.SetInput("abcd");
    L.AddRegExp("abcd","var");
    L.AddRegExp("abcc","num");
    L.SetMetaVariable(Token("@"));

    L.LexInput();
    QVector<Token> exp = {Token("var")};

    QVERIFY(L.GetResTokens() == exp);

    Lexer L2;
    L2.SetInput("abcd abcd");
    L2.AddRegExp("abcd","num");
    L2.SetMetaVariable(Token("@"));

    L2.LexInput();
    QVector<Token> exp2 = {Token("num"),Token("num")};

    QVERIFY(L2.GetResTokens() == exp2);

    Lexer L3;
    L3.SetInput("abcd abcd d");
    L3.AddRegExp("a","name");
    L3.AddRegExp("bc","key");
    L3.AddRegExp("bcd","thing");
    L3.AddRegExp("d","foo");
    L3.SetMetaVariable(Token("@"));

    L3.LexInput();
    QVector<Token> exp3 = {Token("name"),Token("thing"),Token("name"),Token("thing"),Token("foo")};

    QVERIFY(L3.GetResTokens() == exp3);

    Lexer L4;
    L4.SetInput("aa aaa a");
    L4.AddRegExp("a+","name");
    L4.SetMetaVariable(Token("@"));
    L4.LexInput();
    L4.SetMetaVariable(Token("@"));
    QVector<Token> exp4 = {Token("name"),Token("name"),Token("name")};

    QVERIFY(L4.GetResTokens() == exp4);

    Lexer L5;
    L5.SetInput("b");
    L5.AddRegExp("a+","name");
    L5.SetMetaVariable(Token("@"));
    L5.LexInput();
    QVector<Token> exp5 = {};

    QVERIFY(L5.GetResTokens() == exp5);

    Lexer L6;
    L6.SetInput("abcabc");
    L6.AddRegExp("bcd","name");
    L6.SetMetaVariable(Token("@"));
    L6.LexInput();
    QVector<Token> exp6 = {};
    QVERIFY(L6.GetResTokens() == exp6);

    Lexer L7;
    L7.SetInput("abcabc \n 1234");
    L7.AddRegExp("bca","name");
    L7.AddRegExp("a","key");
    L7.AddRegExp("c","key3");
    L7.AddRegExp("n","key2");
    L7.AddRegExp("1234","num");
    L7.SetMetaVariable(Token("@"));
    L7.LexInput();
    QVector<Token> exp7 = {Token("key"),Token("name"),Token("key3"),Token("num")};
    QVERIFY(L7.GetResTokens() == exp7);

    Lexer L8;
    L8.SetInput("forax");
    L8.AddRegExp("for","key");
    L8.AddRegExp("all","key2");
    L8.SetMetaVariable(Token("@"));
    L8.LexInput();
    QVector<Token> exp8 = {Token("key")};
    QVERIFY(L8.GetResTokens() == exp8);

    Lexer L9;
    L9.SetInput("@ a name");
    L9.SetMetaVariable(Token("@"));
    L9.AddRegExp("@", "@");
    L9.AddRegExp("name","name");
    L9.LexInput();
    QVector<Token> exp9 = {Token("@"),Token("a"),Token("name")};
    QVERIFY(L9.GetResTokens() == exp9);
}

void Tester::TestRun()
{
    Grammar G;
    G.SetNonTerminals({Token("S"),Token("A"),Token("EXP")});
    G.SetTerminals({Token("pkg"),Token("name"),Token("coma"),Token("id"),Token("equ"),Token("num"),Token("add")});

    Token t1("S");
    Token t2("pkg");
    Token t2_1("name");
    Token t2_2("coma");
    Token t2_3("A");
    QVector<Token> v1;
    v1.push_back(t2);
    v1.push_back(t2_1);
    v1.push_back(t2_2);
    v1.push_back(t2_3);
    Rule r1(t1,v1);

    Token t01("A");
    Token t02("id");
    Token t02_1("equ");
    Token t02_2("EXP");
    Token t02_3("coma");
    Token t02_4("A");
    QVector<Token> v2;
    v2.push_back(t02);
    v2.push_back(t02_1);
    v2.push_back(t02_2);
    v2.push_back(t02_3);
    v2.push_back(t02_4);
    Rule r2(t01,v2);

    Token t3("A");
    Rule r3(t3,{});

    Token t5("EXP");
    Token t6("num");
    QVector<Token> v4;
    v4.push_back(t6);
    Rule r4(t5,v4);

    Token t7("EXP");
    Token t7_1("EXP");
    Token t7_2("add");
    Token t7_3("EXP");
    QVector<Token> v5;
    v5.push_back(t7_1);
    v5.push_back(t7_2);
    v5.push_back(t7_3);
    Rule r5(t7,v5);

    Token t8("EXP");
    Token t9("id");
    QVector<Token> v6;
    v6.push_back(t9);
    Rule r6(t8,v6);

    G.AddRule(r1);
    G.AddRule(r2);
    G.AddRule(r3);
    G.AddRule(r4);
    G.AddRule(r5);
    G.AddRule(r6);

    G.SetMetaToken(Token("@"));
    G.UniqueStart_End();
    G.InsertUniqueStartRule();

    Lexer a;
    a.SetMetaVariable(Token("@"));
    a.AddRegExp("@", "@");
    a.AddRegExp("package","pkg");
    a.AddRegExp("add","add");
    a.AddRegExp("[A-Za-z]+","name");
    a.AddRegExp("_[A-Za-z]+","id");
    a.AddRegExp(",","coma");
    a.AddRegExp("=","equ");
    a.AddRegExp("[0-9]","num");
    a.SetInput("package alma , _myres = 1 add 2 ,");
    a.LexInput();
    QVector<Token> prog = a.GetResTokens();
    a.SetInput("package alma , _myres = 1 add @ metav ,");
    a.LexInput();
    QVector<Token> text = a.GetResTokens();

    LRParser E(G,text);
    E.SetProgText(prog);
    E.Generate();
    E.Parse();
    E.CalValidMatches();
    QVERIFY(E.GetValidASTs().size() == 1);

}

QTEST_APPLESS_MAIN(Tester)

#include "tst_tester.moc"
