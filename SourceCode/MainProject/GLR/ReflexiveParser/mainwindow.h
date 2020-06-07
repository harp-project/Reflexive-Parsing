#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QObject* appmanager,QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void StartSignal();
    void TextChanged(QString);
    void GrammChanged(QString);
    void PattChanged(QString);
    void RegExpChanged(QString);
    void TerminalsChanged(QString);
    void NonTerminalsChanged(QString);
    void MetaVChanged(QString);

private slots:
    void on_pushButton_clicked();
    void on_plainTextEdit_prog_textChanged();
    void on_plainTextEdit_gramm_textChanged();
    void on_plainTextEdit_patt_textChanged();
    void on_plainTextEdit_regexp_textChanged();
    void on_plainTextEdit_temin_textChanged();
    void on_plainTextEdit_2_nonterm_textChanged();
    void on_lineEdit_metavar_textChanged(const QString &arg1);
    void Error(QString);

private:
    Ui::MainWindow *ui;

    QObject* _appManager;
};
#endif // MAINWINDOW_H
