#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QObject* appmanager,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    _appManager = appmanager;

    connect(this,SIGNAL(StartSignal()),_appManager,SLOT(Start()));
    connect(this,SIGNAL(PattChanged(QString)),_appManager,SLOT(PattChanged(QString)));
    connect(this,SIGNAL(TextChanged(QString)),_appManager,SLOT(TextChanged(QString)));
    connect(this,SIGNAL(GrammChanged(QString)),_appManager,SLOT(GrammChanged(QString)));
    connect(this,SIGNAL(RegExpChanged(QString)),_appManager,SLOT(RegExpChanged(QString)));
    connect(this,SIGNAL(TerminalsChanged(QString)),_appManager,SLOT(TerminalsChanged(QString)));
    connect(this,SIGNAL(NonTerminalsChanged(QString)),_appManager,SLOT(NonTerminalsChanged(QString)));
    connect(this,SIGNAL(MetaVChanged(QString)),_appManager,SLOT(MetaVChanged(QString)));

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->plainTextEdit_patt->document()->isEmpty())
    {
        QMessageBox::information(this,"Error","Pattern field is empty!");
    }
    else if(ui->plainTextEdit_prog->document()->isEmpty())
    {
        QMessageBox::information(this,"Error","Program field is empty!");
    }else if(ui->plainTextEdit_gramm->document()->isEmpty())
    {
        QMessageBox::information(this,"Error","Grammar field is empty!");
    }else if(ui->plainTextEdit_regexp->document()->isEmpty())
    {
        QMessageBox::information(this,"Error","RegExps field is empty!");
    }else if(ui->plainTextEdit_temin->document()->isEmpty())
    {
        QMessageBox::information(this,"Error","Terminals field is empty!");
    }else if(ui->plainTextEdit_2_nonterm->document()->isEmpty())
    {
        QMessageBox::information(this,"Error","Nonterminals field is empty!");
    }else if(ui->lineEdit_metavar->text().isEmpty())
    {
        QMessageBox::information(this,"Error","Metavariable field is empty!");
    }
    else
    {
        emit StartSignal();
    }
}

void MainWindow::on_plainTextEdit_prog_textChanged()
{
    emit TextChanged(ui->plainTextEdit_prog->toPlainText());
}

void MainWindow::on_plainTextEdit_gramm_textChanged()
{
    emit GrammChanged(ui->plainTextEdit_gramm->toPlainText());
}

void MainWindow::on_plainTextEdit_patt_textChanged()
{
    emit PattChanged(ui->plainTextEdit_patt->toPlainText());
}

void MainWindow::on_plainTextEdit_regexp_textChanged()
{
    emit RegExpChanged(ui->plainTextEdit_regexp->toPlainText());
}

void MainWindow::on_plainTextEdit_temin_textChanged()
{
    emit TerminalsChanged(ui->plainTextEdit_temin->toPlainText());
}

void MainWindow::on_plainTextEdit_2_nonterm_textChanged()
{
    emit NonTerminalsChanged(ui->plainTextEdit_2_nonterm->toPlainText());
}

void MainWindow::on_lineEdit_metavar_textChanged(const QString &arg1)
{
    emit MetaVChanged(arg1);
}

void MainWindow::Error(QString s)
{
    if(s == "Reg")
    {
        QMessageBox::information(this,"Error","Error in Regular expressions field!");
    }else if(s == "Gram")
    {
        QMessageBox::information(this,"Error","Error in Grammar field!");
    }else if(s == "Lex")
    {
        QMessageBox::information(this,"Error","Regular expressions does not match to terminal tokens!");
    }
}
