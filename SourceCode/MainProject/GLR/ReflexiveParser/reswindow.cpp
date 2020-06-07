#include "reswindow.h"
#include "ui_reswindow.h"

ResWindow::ResWindow(QObject* appmanager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResWindow)
{
    _appManager = appmanager;
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    connect(this,SIGNAL(Closed()),appmanager,SLOT(ResClosed()));
    _treeContainer = new QTreeWidget();
    _treeContainer->setColumnWidth(0,250);

    QVBoxLayout *mainlay = new QVBoxLayout();
    QHBoxLayout *reslay = new QHBoxLayout();
    _res = new QLabel("Fail");
    _res->textFormat();
    _res->setAlignment(Qt::AlignCenter);
    _resNo = new QLabel("0");
    _resNo->setAlignment(Qt::AlignCenter);
    _res->setMargin(0);
    _resNo->setMargin(0);

    reslay->addWidget(_res);
    reslay->addWidget(_resNo);
    mainlay->addItem(reslay);
    mainlay->addWidget(_treeContainer);
    QHBoxLayout *buttonsLay = new QHBoxLayout();
    _next = new QPushButton("Next");
    _prev = new QPushButton("Previous");
    buttonsLay->addWidget(_prev);
    _indLabel = new QLabel("0");
    _indLabel->setAlignment(Qt::AlignCenter);
    _indLabel->setMargin(5);
    buttonsLay->addWidget(_indLabel);
    buttonsLay->addWidget(_next);
    mainlay->addLayout(buttonsLay);

    setLayout(mainlay);

    _treeContainer->setColumnCount(2);
    _treeContainer->setHeaderLabels(QStringList()<<"Name"<<"Metavariable");

    connect(_next,SIGNAL(clicked()),this,SLOT(Next()));
    connect(_prev,SIGNAL(clicked()),this,SLOT(Prev()));


    ui->setupUi(this);
}

ResWindow::~ResWindow()
{
    delete _res;
    delete _resNo;
    delete _indLabel;
    delete _treeContainer;
    delete ui;
    delete _next;
    delete _prev;
}

QTreeWidgetItem* ResWindow::AddRoot(QString name, bool meta)
{
    QTreeWidgetItem *node = new QTreeWidgetItem(_treeContainer);
    node->setText(0,name);
    if(meta)
    {
        node->setBackground(0,Qt::lightGray);
        node->setBackground(1,Qt::lightGray);
    }
    _treeContainer->addTopLevelItem(node);
    return node;
}

QTreeWidgetItem* ResWindow::AddChild(QTreeWidgetItem *parent, QString name, bool ismeta, Token meta)
{
    QTreeWidgetItem *node = new QTreeWidgetItem();
    node->setText(0,name);
    if(name == "")
    {
        node->setHidden(true);
        parent->setHidden(true);
    }
    else if(ismeta)
    {
        node->setText(1,meta.Get());
        node->setBackground(0,Qt::lightGray);
        node->setBackground(1,Qt::lightGray);
    }

    parent->addChild(node);
    return  node;
}

void ResWindow::SetResTrees(QVector<Node *> r)
{
    _resTrees = r;
    _index = 0;
    if(_resTrees.size() > 0)
    {
        _res->setText("Success");
        _resNo->setText("Number of matches: " + QString::number(_resTrees.size()));
        _res->setStyleSheet("QLabel{background-color : lightgreen;font: 9pt;}");
        _resNo->setStyleSheet("QLabel{background-color : lightgreen;font: 9pt;}");

        BuildTree(r[0]);
        _treeContainer->expandAll();
        _indLabel->setText(QString::number(_index+1) + "/" + QString::number(_resTrees.size()));
        _prev->setEnabled(false);
        if(_resTrees.size() == 1)
        {
            _next->setEnabled(false);
        }
    }else
    {
        _res->setText("Fail");
        _res->setStyleSheet("QLabel{background-color : rgb(255, 102,102);font: 9pt;}");
        _resNo->setText("Number of matches: 0");
        _resNo->setStyleSheet("QLabel{background-color : rgb(255, 102,102);font: 9pt;}");
        _next->setEnabled(false);
        _prev->setEnabled(false);
        _treeContainer->hide();
    }

}

void ResWindow::AddAllChildren(QTreeWidgetItem* par, Node *child)
{
    QTreeWidgetItem *node = AddChild(par,child->GetToken().Get(),child->GetIsmeta(),child->GetMetaVar());
    for(int i = 0 ; i < child->ChildNumber() ; i++)
    {
        AddAllChildren(node,child->GetChild(i));
    }
}

void ResWindow::reject()
{
    emit Closed();
    QDialog::reject();
}

void ResWindow::Next()
{
    if(_index < _resTrees.size()-1)
    {
        _treeContainer->clear();
        _index++;
        BuildTree(_resTrees[_index]);
        _treeContainer->expandAll();
        _indLabel->setText(QString::number(_index+1) + "/" + QString::number(_resTrees.size()));
        if(_index == _resTrees.size()-1)
        {
            _next->setEnabled(false);
        }

        if(_index > 0)
        {
            _prev->setEnabled(true);
        }
    }
}

void ResWindow::Prev()
{
    if(_index > 0)
    {
        _treeContainer->clear();
        _index--;
        BuildTree(_resTrees[_index]);
        _treeContainer->expandAll();
        _indLabel->setText(QString::number(_index+1) + "/" + QString::number(_resTrees.size()));
        if(_index == 0)
        {
            _prev->setEnabled(false);
        }

        if(_index < _resTrees.size()-1)
        {
            _next->setEnabled(true);
        }
    }

}

void ResWindow::BuildTree(Node * root)
{
    QTreeWidgetItem *node = AddRoot(root->GetToken().Get(),root->GetIsmeta());
    for(int i = 0 ; i < root->ChildNumber() ; i++)
    {
        AddAllChildren(node,root->GetChild(i));
    }
}
